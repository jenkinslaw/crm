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

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/phone.php';

    $fields = array(
      'id' => "The unique identifier for this phone number record",
      'number'   => "The phone number",
      'phone_type'     => "Key indicating if it is a Phone or Fax number",
    );

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'PhoneJSONReader'));

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Phone ID',
          'alias' => 'p',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );

    $this->destination = new MigrateDestinationEntityAPI('phone_number', 'phone_number');

    $this->addFieldMapping('id', 'id')
      ->description('Mapping phone_id to entity id');
    $this->addFieldMapping('number', 'number')
      ->description('Mapping number to number');
    $this->addFieldMapping('title', 'number')
      ->description('Mapping number type to phone entity title');
    $this->addFieldMapping('phone_type', 'phone_type')
      ->description('Mapping phone type key to phone type');
  }
}
