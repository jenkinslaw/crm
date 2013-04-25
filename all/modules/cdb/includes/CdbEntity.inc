<?php
/**
 * @file
 * The Cdb\Entity class is a wrapper for the entity wrapper found in entity_api.
 *
 * This wrapper is a lot more intuitive than that one.
 * For instance, given a known field_name we can set and retrive values:
 *
 *     $entity->name = 'value';
 *     $name_value = $entity->name;
 *
 * But if we prefer we can still do:
 *
 *     $entiy->name()->set('value');
 *
 *     $entity->name()->value();
 *
 *
 * This is a marked improvement over the wrapper that comes with entity_api:
 *
 *     $entity->field_name->set('value');
 *     $name_value = $entity->field_name->value();
 */

class CdbEntity {

  protected $entity;
  protected $type;

  /**
   * Entity Contructor.
   */
  protected function __construct($id = NULL) {
    $this->entity = $this->getWrapper($id);
  }

  /**
   * Magic call method.
   */
  public function __call($name, $arguments) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name;
  }

  /**
   * We can handle handle some crud via magic methods.
   */
  public function __get($name) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->value();
  }

  /**
   * Gets the Entity field name.
   */
  private function formatFieldName($name) {
    if (isset($this->entity->{"field_$name"})) {
      return "field_$name";
    }
    return $name;
  }

  /**
   * Magic __set method.
   */
  public function __set($name, $value) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->set($value);
  }

  /**
   * Given a field name, returns it's value.
   *
   * This may is a redundency for magic __get.
   */
  public function value($name) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->value();
  }

  /**
   * Save the Entity to the database.
   */
  public function save() {
    $this->entity->save();
  }

  /**
   * Delete the Entity from the database.
   *
   * This may also delete multiple entities at once.
   */
  public function delete() {
    $this->entity->delete();
  }

  /**
   * Returns some basic field info.
   */
  public function fieldInfo($name) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->info();
  }

  /**
   * Get the wrapped entity (it's so nice.).
   */
  public function getWrapper($id = NULL) {
    $entity_type = $this->type;
    $bundle_type = $entity_type;

    if (is_numeric($id)) {
      $entity = entity_load_single($entity_type, $id);
    }
    elseif (is_object($id)) {
      $entity = $id;
    }
    else {
      $entity = entity_create($entity_type, array('type' => $bundle_type));
    }
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    return $wrapper;
  }

  /**
   * Bundles together field information using two techniques. 
   *
   * Sometimes you just need more information than what the basic
   * fieldInfo gives you.
   */
  public function getFieldInfo($name) {
    $name = $this->formatFieldName($name);
    $field_info_a = field_info_field($name);
    $field_info_b = $this->entity->$name->info();

    // Unset some fields that kind of get in the way.
    unset($field_info_b['parent']);
    unset($field_info_a['storage']);

    $info = $field_info_a + $field_info_b;
    return $info;
  }

  /**
   * Returns the wrapped entity that is part of the objec. 
   *
   * This is not like Entity::getWrapper() because we don't need
   * to pass the id in this case. We're simply accessing a value
   * that has already been instantiated.
   */
  public function getEntity() {
    $entity = $this->entity->value();
    return $entity;
  }

  /**
   * Returns the form def array for given operation.
   *
   * This is a nicer than having to remember all those weird
   * form names.
   */
  public function getForm($op = 'add') {
    $entity = $this->type;
    $bundle = $entity;
    $instance = $this->getEntity();
    $form_id = "eck__entity__form__{$op}_{$entity}_{$bundle}";

    return drupal_get_form($form_id, $instance);
  }

  /**
   * Returns the form element associated to element_id.
   */
  public function getElement($element_id, $index = 0) {
    $form = $this->getForm();
    return $form[$element_id]['und'][$index];
  }

  /**
   * Returns a default element value.
   */
  public function getDefaultElementValue($element_id) {
    $type  = $this->type;
    $value = variable_get("cdb_{$type}_{$element_id}_default_value", '');
    return $value;
  }

  /**
   * Sets a default element value.
   */
  public function setDefaultElementValue($element_id, $value = '') {
    $type  = $this->type;
    return variable_set("cdb_$type_$element_id_default_value", '');
  }

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm(&$form, &$form_state, &$form_id) {
  }

}
