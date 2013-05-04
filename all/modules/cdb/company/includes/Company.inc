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
  public function __construct(&$id = NULL) {
    $this->type = 'company';
    parent::__construct($id);
  }


}
