<?php
/**
 * @file
 * Define the Address object.
 */

module_load_include('inc', 'cdb', 'includes/CdbEntity');
module_load_include('inc', 'cdb', 'includes/User');

/**
 * A Class to hold the business specific logic for our Address entity.
 */
class Address extends CdbEntity {

  /**
   * Address constructor.
   */
  public function __construct(&$id = NULL) {
    $this->type = 'address';
    parent::__construct($id);
  }


}
