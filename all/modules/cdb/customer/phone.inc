<?php
/**
 * @file
 * phone.inc
 *
 * Migration tasks for phone entity.
 */

include_once DRUPAL_ROOT . "/sites/all/modules/cdb/phone_number/phone_number.module";

class PhoneJSONReader extends MigrateJSONReader {
  /**
   * Implements MigrateJSONReader::next().
   */
  public function next() {
    // Overide here for company specific JSON parson.
    parent::next();
    // Convert old cdb phone type Key to new phone_type key.
    $this->phone_type = ($this->phone_type != "F")? "Phone" : "Fax";
  }
}

/**
 * Migration steps for Phone entity.
 */
class PhoneMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Phone Migration');
    $this->dependencies = array('Company');

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/phone.php';
    $fields = array(
      'phone_id' => "The unique identifier for this phone number record",
      'number'   => "The phone number",
      'type'     => "Key indicating if it is a Phone or Fax number",
    );

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'PhoneJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('phone', 'phone');

    $this->addFieldMapping('phone_id', 'id')
      ->description('Mapping phone id to entity id');
    $this->addFieldMapping('number', 'number')
      ->description('Mapping number to number');
    $this->addFieldMapping('phone_type', 'phone_type')
      ->description('Mapping phone type key to phone type');
  }
}
