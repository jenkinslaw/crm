<?php
/**
 * @file
 * phone.inc
 *
 * Migration tasks for phone entity.
 */

class PhoneJSONReader extends MigrateJSONReader {
  /**
   * Implements MigrateJSONReader::next().
   */
  public function next() {
    // Overide here for company specific JSON parson.
    parent::next();
    // convert old cdb phone type Key to new phone_type key 
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

    $source_url = 'http://cnelson.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/phone.json';

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
