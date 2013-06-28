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
  }
}

/**
 * Migration steps for Company entity.
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

    $this->addFieldMapping('id', 'entity_id')
      ->description('Mapping id to entity id');
    $this->addFieldMapping('phone', 'phone')
      ->description('Mapping phone to phone');
  }
}
