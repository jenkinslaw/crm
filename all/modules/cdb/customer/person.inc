<?php

/**
 * @file
 * person.inc
 *
 * Migration tasks for person entity.
 */

class PersonJSONReader extends MigrateJSONReader {
  /**
   * Implements MigrateJSONReader::next().
   */
  public function next() {
    // Overide here for company specific JSON parson.
    parent::next();

    $address = $this->currentElement->address->addr_id;
    unset($this->currentElement->address);
    $this->currentElement->address = $address;

  }
}

/**
 * Migration steps for Company entity.
 */
class PersonMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Person Migration');
    $this->dependencies = array('Company');

    $source_url = 'http://cnelson.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/person.json';

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'PersonJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('person', 'person');

    $this->addFieldMapping('old_customer_id', 'old_customer_id')
      ->description('Mapping old_customer_id to entity id');
    $this->addFieldMapping('barcode', 'barcode')
      ->description('Mapping barcode to barcode');
    $this->addFieldMapping('status', 'status')
      ->description('Mapping status to status');
    $this->addFieldMapping('patron_type', 'patron_type')
      ->description('Mapping patron_type to patron_type');
    $this->addFieldMapping('area', 'area')
      ->description('Mapping area to area');
    $this->addFieldMapping('foa', 'foa')
      ->description('Mapping foa to foa');
    $this->addFieldMapping('first', 'first')
      ->description('Mapping first to first');
    $this->addFieldMapping('middle', 'middle')
      ->description('Mapping middle to middle');
    $this->addFieldMapping('last', 'last')
      ->description('Mapping last to last');
    $this->addFieldMapping('title', 'title')
      ->description('Mapping title to title');
    $this->addFieldMapping('email', 'email')
      ->description('Mapping email to email');
    $this->addFieldMapping('CM', 'CM')
      ->description('Mapping CM to CM');
    $this->addFieldMapping('suspended', 'suspended')
      ->description('Mapping suspended to suspended');
    $this->addFieldMapping('dues', 'dues')
      ->description('Mapping dues to dues');
    $this->addFieldMapping('exp_date', 'exp_date')
      ->description('Mapping exp_date to expt_date');
    $this->addFieldMapping('memb_notes', 'memb_notes')
      ->description('Mapping memb_notes to memb_notes');
    $this->addFieldMapping('cust_notes', 'cust_notes')
      ->description('Mapping cust_notes to cust_notes');
    $this->addFieldMapping('last_update', 'last_update')
      ->description('Mapping last_update to last_update');
    $this->addFieldMapping('address', 'address')
      ->description('Mapping address to address');
  }
}
