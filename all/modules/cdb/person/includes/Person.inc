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
    $result = _result_field_combine($result, $fields);
    $suspended_fields = array('field_suspended', 'field_suspended_1');
    cdb_is_suspended($result, $suspended_fields);
    return $result;
  }

}
