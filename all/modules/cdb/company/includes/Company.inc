<?php
/**
 * @file
 * Define the Company object.
 */

module_load_include('inc', 'cdb', 'includes/CdbEntity');
module_load_include('inc', 'cdb', 'includes/User');

/**
 * A Class to hold the business specific logic for our Company entity.
 */
class Company extends CdbEntity {

  /**
   * Company constructor.
   */
  public function __construct($id = NULL) {
    $this->type = 'company';
    parent::__construct($id);
  }

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm(&$form, &$form_state, $form_id) {
    if ($this->isCompanyForm($form)) {
      $this->setDefaultExpDate($form);
    }
  }

  /**
   * Checks to see if this is ic a Company form.
   */
  protected function isCompanyForm(&$form) {
    return (isset($form['#entity_type']) && $form['#entity_type'] == 'company');
  }

  /**
   * Given a Company form sets the default exp_date.
   */
  protected function setDefaultExpDate(&$form) {
    if (User::isCompanyAdmin()) {
      // Evaluates to $item =& $form[foo][bar][baz];
      eval($this->buildItemEval('exp_date'));
      $exp_date = $this->getDefaultElementValue('exp_date');
      $item['#default_value']['value'] = $exp_date;
    }
  }

  /**
   * Builds an evaluation to reference a specific form element.
   */
  protected function buildItemEval($element_id) {
    $index = $this->getArrayIndex($element_id);
    // Evaluates to $item =& $form[foo][bar][baz];
    $eval = '$item =& $form[' . $index . '];';
    return $eval;
  }

}
