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
  protected function __construct(&$id = NULL) {
    $this->entity =& $this->getWrapper($id);
  }

  /**
   * Get the wrapped entity (it's so nice.).
   */
  public function getWrapper(&$id = NULL) {
    $entity_type = $this->type;
    $bundle_type = $entity_type;

    if (is_numeric($id)) {
      $entity = entity_load_single($entity_type, $id);
    }
    elseif (is_object($id)) {
      $entity =& $id;
    }
    else {
      $entity = entity_create($entity_type, array('type' => $bundle_type));
    }
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    return $wrapper;
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
    if (is_object($this->entity->$name)) {
      return $this->entity->$name->value();
    }
    return '';
  }

  /**
   * Gets the Entity field name.
   */
  protected function formatFieldName($name) {
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
    if (is_object($this->entity->$name)) {
      return $this->entity->$name->set($value);
    }
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
   * Bundles together field information using two techniques. 
   *
   * Sometimes you just need more information than what the basic
   * fieldInfo gives you.
   */
  public function getFieldInfo($name) {
    $name = $this->formatFieldName($name);
    $field_info_b = $this->entity->$name->info();
    unset($field_info_b['parent']);
    $info = $field_info_b;

    if ($field_info_a = field_info_field($name)) {
      // Unset some fields that kind of get in the way.
      unset($field_info_a['storage']);
      $info = $info + $field_info_a;
    }

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
   * Sets a default element value.
   */
  public function setDefaultElementValue($element_id, $value = '') {
    $type  = $this->type;
    return variable_set("cdb_{$type}_{$element_id}_default_value", $value);
  }

  /**
   * Wrapper for hook_views_pre_render().
   */
  public function viewsPreRender(&$view) {
    if ($view->name == "{$this->type}_search") {
      if (count($view->result) == 1) {
        $path = "{$this->type}/{$view->result[0]->id}";
        drupal_goto($path);
      }
      foreach ($view->result as &$result) {
        $this->forEeachResult($result);
      }
    }
  }

  /**
   * Stub for hook_views_query_alter().
   * 
   * @param Views $view
   *   A reference to a Drupal Views object.
   *
   * @return Boolean
   *   TRUE if a $view is a CDB related view, FALSE otherwise.
   */
  public function hookViewsQueryAlter(&$view) {
    if ($view->name == "{$this->type}_search") {
      $this->multiNameSearchQueryAlter($view);
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Alter query for multisearch forms.
   */
  public function multiNameSearchQueryAlter(&$view) {
    // Alter the view query to do multiple searches on company_name.
    if ($view->current_display == 'page_1') {
      unset ($view->query->where);
      $view->query->set_where_group('OR', 0);
      $field = $this->type == 'person' ? 'last_value' : 'company_name';

      $lines = explode("\n", $view->exposed_raw_input[$field]);
      foreach ($lines as $line) {
        $value = '%' . trim($line) . '%';
        $view->query->add_where(0, $field, $value, 'LIKE');
      }
    }
  }

  /**
   * Stub reference function to run code on each view result.
   */
  protected function foreEachResult(&$result) {
  }

}
