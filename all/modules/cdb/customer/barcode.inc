<?php
/**
 * @file
 * barcode.inc
 * 
 * Migrates barcode opbjects to D7 from Cdb.
 */

module_load_include('inc', 'migrate_extras', 'entity_api');

class BarcodeJSONReader extends MigrateJSONReader {
  /**
   * Implements MigrateJSONReader::next().
   */
  public function next() {

    // Overide here for barcode specific JSON parsor.
    parent::next();

  }
}

/**
 * Migration steps for Barcode entity.
 */
class BarcodeMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Barcode Migration');

    $fields = array(
      'id' => 'Barcode id',
      'barcode' => 'The Barcode',
      'status' => 'The barcode status: 1',
    );

    $limit = get_cdb_migrate_limit();

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/barcode.php?' . $limit;

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'BarcodeJSONReader'));

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Barcode ID',
          'alias' => 'b',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );

    $this->destination = new MigrateDestinationEntityAPI('barcode', 'barcode');

    $this->addFieldMapping('id', 'id')
      ->description('Mapping id to entity_id');
    $this->addFieldMapping('title', 'barcode')
      ->description('Mapping barcode to entity title');
    $this->addFieldMapping('barcode', 'barcode')
      ->description('Mapping barcode to barcode field');
    $this->addFieldMapping('status', 'status')
      ->description('Mapping satus to status field');
  }
}
