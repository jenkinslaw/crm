<?php
/**
 * @file
 * PhoneNumberEntityForm.inc
 *
 * Extends the EntityForm class to define methods specific to 
 * the PhoneNumberEnitty Form.
 */

class PhoneNumberEntityForm extends EntityForm {

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm() {
    if ($this->isPhoneNumberForm()) {
      $this->setDefaultExpDate();
      $this->makeBillingAreaRequired();
    }
  }

  /**
   * Checks to see if this is ic a PhoneNumber form.
   */
  protected function isPhoneNumberForm() {
    return ($this->type == 'phone_number_entity_form');
  }

}
