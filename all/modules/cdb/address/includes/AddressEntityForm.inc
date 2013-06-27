<?php
/**
 * @file
 * AddressEntityForm.inc
 *
 * Extends the EntityForm class to define methods specific to 
 * the AddressEnitty Form.
 */

class AddressEntityForm extends EntityForm {

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm() {
    if ($this->isAddressForm()) {
    }
  }

  /**
   * Checks to see if this is ic a Address form.
   */
  protected function isAddressForm() {
    return ($this->type == 'address_entity_form');
  }

}
