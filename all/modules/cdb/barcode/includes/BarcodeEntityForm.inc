<?php
/**
 * @file
 * BarcodeEntityForm.inc
 *
 * Extends the EntityForm class to define methods specific to 
 * the BarcodeEnitty Form.
 */

class BarcodeEntityForm extends EntityForm {

  /**
   * Helper function for hooking into hook_form_alter.
   */
  public function hookForm() {
    if ($this->isBarcodeForm()) {
    }
  }

  /**
   * Checks to see if this is ic a Barcode form.
   */
  protected function isBarcodeForm() {
    return ($this->type == 'barcode_entity_form');
  }

}
