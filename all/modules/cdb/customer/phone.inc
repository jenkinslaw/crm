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
 * Migration steps for Phone entity.
 */
class PhoneMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Phone Migration');

    $limit = get_cdb_migrate_limit();
    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/phone.php?' . $limit;

    $fields = array(
      'id'         => "The unique identifier for this phone number record",
      'number'     => "The phone number",
      'extension'  => "Any characters after the inital 10 digits. Maybe an extension, maybe not?!?",
      'phone_type' => "Key indicating the type of number",
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
    $this->addFieldMapping('extension', 'extension')
      ->description('Mapping extension to entension');
    $this->addFieldMapping('phone_type', 'phone_type')
      ->description('Mapping phone type key to phone type');
  }
}
