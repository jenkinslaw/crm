<?php
/**
 * @file
 * Define the Barcode object.
 */

module_load_include('inc', 'cdb', 'includes/CdbEntity');
module_load_include('inc', 'cdb', 'includes/User');

/**
 * A Class to hold the business specific logic for our Address entity.
 */
class Barcode extends CdbEntity {

  /**
   * Barcode constructor.
   */
  public function __construct(&$id = NULL) {
    $this->type = 'barcode';
    parent::__construct($id);
  }


}
