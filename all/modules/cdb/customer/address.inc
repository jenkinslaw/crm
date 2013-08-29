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

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/address.php?limit=15';
    $fields = array(
      "id"     => "The Address id",
      "Line 1"      => "First line of the address",
      "Line 2"      => "Second Line of the address",
      "City"        => "The City",
      "State"       => "The State",
      "Postal Code" => "Zip Code",
      "Country"     => "Always empty, but set to US",
    );

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'AddressJSONReader'));
    
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Address ID',
          'alias' => 'a',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );


    $this->destination = new MigrateDestinationEntityAPI('address', 'address');

    $address_args = array(
      'thoroughfare'        => array('source_field' => 'Line 1'),
      'premise'             => array('source_field' => 'Line 2'),
      'locality'            => array('source_field' => 'City'),
      'administrative_area' => array('source_field' => 'State'),
      'postal_code'         => array('source_field' => 'Postal Code'),
    );

    $this->addFieldMapping('id', 'id')
      ->description('Mapping id to entity id');
    $this->addFieldMapping('address', 'Country')
      ->arguments($address_args)
      ->description('Mapping address fields to address');
  }
}
