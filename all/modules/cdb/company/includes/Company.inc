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

  /**
   * Returns the number of attorneys for a company.
   */
  public function getNumberOfAttorneys() {
    $id = $this->id;
    if ($id) {
      $query = db_select('field_data_field_company', 'c');
      $query->join('field_data_field_status', 's', 'c.entity_id = s.entity_id');
      $query->condition('field_company_target_id', $id, '=');
      $query->condition('field_status_value', '1', '=');
      $query->fields('u', array('field_company_target_id'));

      return  $query->countQuery()->execute()->fetchField();
    }
    return 0;
  }
}
