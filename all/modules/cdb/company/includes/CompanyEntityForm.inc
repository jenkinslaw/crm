<?php
/**
 * @file
 * CompanyEntityForm.inc
 *
 * Extends the EntityForm class to define methods specific to the CompanyEnitty
 * Form.
 */

class CompanyEntityForm extends EntityForm {

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm() {
    if ($this->isCompanyForm()) {
      $this->setDefaultExpDate();
    }
  }

  /**
   * Checks to see if this is ic a Company form.
   */
  protected function isCompanyForm() {
    return ($this->type == 'company_entity_form');
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

}
