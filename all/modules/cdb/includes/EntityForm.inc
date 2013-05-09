<?php
/**
 * @file
 * EntityForm.inc
 *
 * This file defines the EntityForm class which is a wrapper for drupal forms.
 */

class EntityForm {

  protected $form;
  protected $entity;

  /**
   * Entity Form Contructor.
   */
  public function __construct(&$form) {
    $this->setForm($form);
  }

  /**
   * Returns the form def array for given operation.
   *
   * This is a nicer than having to remember all those weird
   * form names.
   */
  public function getForm() {
    return $this->form;
  }

  /**
   * Sets the enity form after building it.
   */
  protected function setForm(&$form) {
    if (is_array($form) && isset($form['#entity'])) {
      $this->form =& $form;
      $this->entity =& $form['#entity'];
      $this->type = "{$this->entity->type}_entity_form";
    }
    elseif (is_object($form) && $form instanceof Entity) {
      $entity =& $form;
      $type = $entity->type;
      $bundle = $type;
      $form_id = "eck__entity__form__add_{$type}_{$bundle}";

      $this->form = drupal_get_form($form_id, $entity);
      $this->entity =& $entity;
      $this->type = "{$type}_entity_form";
    }
    else {
      $this->form =& $form;
      $this->type = 'non_entity_form';
    }
  }

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm() {
    if ($this->isCompanyForm()) {
      $this->setDefaultExpDate();
    }
  }

  /**
   * Given a Company form sets the default exp_date.
   */
  protected function setDefaultExpDate() {
    $user = new User();
    if ($user->hasRole('Company Administrator')) {
      // Evaluates to $item =& $this->form[foo][bar][baz];
      eval($this->buildItemEval('exp_date'));
      $exp_date = $this->getDefaultElementValue('exp_date');
      $item['#default_value']['value'] = $exp_date;
    }
  }

  /**
   * Returns a default element value.
   */
  public function getDefaultElementValue($element_id) {
    $type  = $this->entity->type;
    $value = variable_get("cdb_{$type}_{$element_id}_default_value", '');
    return $value;
  }


  /**
   * Builds an evaluation to reference a specific form element.
   */
  protected function buildItemEval($element_id) {
    $index = $this->getArrayIndex($element_id);
    // Evaluates to $item =& $form[foo][bar][baz];
    $eval = '$item =& $this->form[' . $index . '];';
    return $eval;
  }

  /**
   * Returns the form element associated to element_id.
   */
  public function getElement($element_id, $index = 0) {
    $array_index = $this->getArrayIndex($element_id, $index);
    eval(' $item = $this->form[' . $array_index . '];');
    return $item;
  }

  /**
   * Given an elemen_id returns the index for that element.
   */
  protected function getArrayIndex($element_id, $index = 0) {
    $index_string = "'{$element_id}'";

    if ($this->form[$element_id]['#type'] != 'container') {
      return $index;
    }
    else {
      $index_string .= "]['und'";
    }

    if (isset($this->form[$element_id]['und']['#type'])) {
      return $index_string;
    }
    else {
      $index_string .= "][$index";
    }

    return $index_string;
  }
}
