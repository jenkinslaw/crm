<?php
/**
 * @file
 * EntityForm.inc
 *
 * This file defines the EntityForm class which is a wrapper for drupal forms.
 */

module_load_include('inc', 'eck', 'eck.entity');

class EntityForm {

  protected $form;
  protected $entity;

  /**
   * Entity Form Contructor.
   */
  public function __construct(&$form = NULL) {
    $this->setForm($form);
  }

  /**
   * Returns a refernce to our form.
   */
  public function &getForm() {
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
    $item =& $this->getElementPropertyValue($element, $property_index);
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
   * @return ref
   *   Returns a reference to the element property.
   */
  public function &getElementPropertyValue($element, $property_index = array()) {
    $item =&  $this->getElementItem($element);
    $item =& $this->getElementProperty($item, $property_index);
    return $item;
  }

  /**
   * Given an element_id returns a reference to that element.
   */
  protected function &getElementItem($element_id, $index = 0) {

    $item =& $this->form[$element_id];

    if ($item['#type'] != 'container') {
      return $item;
    }
    else {
      $item =& $item['und'];
    }

    if (isset($item['#type'])) {
      return $item;
    }
    else {
      $item =& $item[$index];
    }
    // References have a target.
    if (isset($item['target_id'])) {
      $item =& $item['target_id'];
    }

    return $item;
  }

  /**
   * Traverse an array to return a reference to an internal of the array.
   * 
   * @param Array $item
   *   A reference to the array being traversed.
   *
   * @param Mixed $index
   *   Any array that defines the index used to traverse the $item.
   *
   * @return ref
   *   A reference to the property of an item as detertimed by traversing
   *   the item using the index provided.
   */
  protected function &getElementProperty(&$item, $index = array()) {
    if (!empty($index)) {
      if (is_string($index) && isset($item[$index])) {
        $item =& $item[$index];
      }
      elseif (is_array($index)) {
        foreach ($index as $key) {
          if (isset($item[$key])) {
            $item =& $item[$key];
          }
        }
      }
    }
    return $item;
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

  /**
   * Checks whether the form is a views exposed form.
   */
  public function isViewsExposedForm() {
    return (isset($this->form['form_id']) &&
      $this->form['form_id']['#value'] == 'views_exposed_form');
  }

  /**
   * Duplicates the specied form field N times.
   *
   * @param String $field
   *   field name
   *
   * @param Int $n
   *   Number of times to duplicate the field. 
   *
   * @return ref
   *   Wheter or not the field duplciation occurs.
   */
  protected function duplicateField($field, $n = 2) {
    if (!isset($this->form[$field])) {
      return FALSE;
    }
    $item = $this->form[$field];
    for ($i = 1; $i <= $n; $i++) {
      $this->form["{$field}_$i"] = $item;
    }
    return TRUE;
  }
}
