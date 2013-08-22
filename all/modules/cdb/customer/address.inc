<?php

/**
 * @file
 * address.inc
 *
 * Migration tasks for address entity.
 */

class AddressJSONReader extends MigrateJSONReader {
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
class AddressMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Address Migration');
    $this->dependencies = array('Company');

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/address.php';

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'AddressJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('address', 'address');

    $this->addFieldMapping('id', 'entity_id')
      ->description('Mapping id to entity id');
    $this->addFieldMapping('address', 'address')
      ->description('Mapping address to address');
  }
}
