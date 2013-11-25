<?php
/**
 * @file
 * Define the Person object.
 */

module_load_include('inc', 'cdb', 'includes/CdbEntity');
/**
 * A Class to hold the business specif logic for our Company entity.
 */
class Person extends CdbEntity {

  /**
   * Person constructor.
   */
  public function __construct(&$id = NULL) {
    $this->type = 'person';
    parent::__construct($id);
  }

  /**
   * Overrides CdbEntity::forEachResult().
   */
  protected function foreEachResult(&$result) {
    $fields = array('field_phone_number_entity', 'field_phone_entity');
    return $result = _result_field_combine($result, $fields);
  }

}
