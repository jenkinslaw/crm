<?php
/**
 * @file
 * Define the PhoneNumber object.
 */

module_load_include('inc', 'cdb', 'includes/CdbEntity');
module_load_include('inc', 'cdb', 'includes/User');

/**
 * A Class to hold the business specific logic for our PhoneNumber entity.
 */
class PhoneNumber extends CdbEntity {

  /**
   * PhoneNumber constructor.
   */
  public function __construct(&$id = NULL) {
    $this->type = 'phone_number';
    parent::__construct($id);
  }


}
