<?php
/**
 * @file
 * Define the Company object.
 */

module_load_include('inc', 'cdb', 'includes/CdbEntity');

/**
 * A Class to hold the business specif logic for our Company entity.
 */
class Company extends CdbEntity {

  /**
   * Company constructor.
   */
  public function __construct($id = NULL) {
    $this->type = 'company';
    parent::__construct($id);
  }

}
