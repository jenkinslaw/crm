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
      $this->makeBillingAreaRequired();
    }
    elseif ($this->isCompanyViewsMultiSearchForm()) {
      $this->form['company_name']['#type'] = 'textarea';
    }
  }

  /**
   * Checks to see if this is ic a Company form.
   */
  protected function isCompanyForm() {
    return ($this->type == 'company_entity_form');
  }

  /**
   * Checks to see if this is a Company Related Views Form.
   */
  protected function isCompanyViewsMultiSearchForm() {
    $action = "/company/multi-search";
    return ($this->isViewsExposedForm() &&
      $this->form['#action'] == $action);
  }

  /**
   * Sets the default exp_date.
   */
  protected function setDefaultExpDate() {
    $user = new User();
    if ($user->hasRole('Company Administrator')) {
      $exp_date = $this->getDefaultElementValue('exp_date');
      $this->setElementPropertyValue('exp_date',
        array('#default_value', 'value'), $exp_date);
    }
  }

  /**
   * Makes billing_area a required field for Company Administrators.
   */
  protected function makeBillingAreaRequired() {
    $user = new User();
    if ($user->hasRole('Company Administrator')) {
      $this->setElementPropertyValue('billing_area', '#required', TRUE);
    }
  }

}
