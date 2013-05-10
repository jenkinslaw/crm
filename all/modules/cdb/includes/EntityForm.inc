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
   * Set the a value for a form element property.
   *
   * @param String $element
   *   Usually the field name.
   *
   * @param Mixed  $property_index
   *   If String, the form element property name (i.e. '#required').
   *   If Array, the keys define an index where the last element
   *   is assigend the $value (i.e. array('#default_value', 'name'))
   *
   * @param Mixed $value
   *   Can be any kind of value.
   *
   * @return void
   *   This function acts directly the referenced item.
   */
  public function setElementPropertyValue($element, $property_index, $value) {
    // Evaluates to $item =& $this->form[foo][bar][baz];
    $item =& $this->getEvaluatedItem($element, $property_index);
    $item = $value;
  }


  /**
   * Gets a reference to the form element associated to element_id.
   *
   * @param String $element
   *   The element name.
   *
   * @return ref
   *   A reference to the form element.
   */
  public function &getElement($element) {
    return $this->getElementPropertyValue($element, '');
  }

  /**
   * Gets the a value for a form element property.
   *
   * @param String $element
   *   Usually the field name.
   *
   * @param Mixed  $property_index
   *   If String, the form element property name (i.e. '#required').
   *   If Array, the keys define an index where the last element
   *   is assigend the $value (i.e. array('#default_value', 'name'))
   *
   * @return Reference
   *   Returns a reference to the element property.
   */
  public function &getElementPropertyValue($element, $property_index) {
    // Evaluates to $item =& $this->form[foo][bar][baz];
    return $this->getEvaluatedItem($element, $property_index);
  }

  /**
   * Evaluates a form item and returns it as a reference.
   *
   * @param String $element
   *   Usually the field name.
   *
   * @param Mixed  $property_index
   *   If String, the form element property name (i.e. '#required').
   *   If Array, the keys define an index where the last element
   *   is assigend the $value (i.e. array('#default_value', 'name'))
   *
   * @return void
   *   This function acts directly on its referenced item.
   */
  protected function &getEvaluatedItem($element, $property_index) {
    eval($this->buildItemEval($element, $property_index));
    return $item;
  }

  /**
   * Builds an evaluation to reference a specific form element.
   */
  protected function buildItemEval($element_id, $property = array()) {
    $index = $this->getArrayIndex($element_id);
    $property_index = $this->arrayToIndex($property);

    // Evaluates to $item =& $form[foo][bar][baz];
    $eval = '$item =& $this->form[' . $index . ']' . $property_index . ';';
    return $eval;
  }

  /**
   * Given an array returns a string representing and an array index.
   *
   * @param Mixed $array
   *   Any array that you want to mash into a string index.
   *   Or, a key value that you want to represent as an array index.
   *
   * @return String
   *   The string representation of the index. (i.e. '[foo][bar][baz]').
   */
  protected function arrayToIndex($array = array()) {
    $index = '';
    if (!empty($array)) {
      if (is_string($array)) {
        $index .= "['" . $array . "']";
      }
      elseif (is_array($array)) {
        foreach ($array as $key) {
          $index .= "['" . $key . "']";
        }
      }
    }
    return $index;
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

  /**
   * Returns a default element value.
   */
  public function getDefaultElementValue($element_id) {
    $type  = $this->entity->type;
    $value = variable_get("cdb_{$type}_{$element_id}_default_value", '');
    return $value;
  }
  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm() {
  }

}
