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

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/customer.php';

    $fields = array(
      'old_customer_id' => 'Cutomer Record ID.',
      'barcode' => 'Barcode ID.',
      'status' => 'Essentially type of patron occupation (i.e. Attorney)',
      'area' => 'Missing Map: A location category (i.e. Remote, Local, etc.)',
      'foa' => 'Customer Form of Address.',
      'first' => 'Customer First Name.',
      'middle' => 'Customer Middle Initial.',
      'last' => 'Customer Last Name.',
      'email' => 'Customer email.',
      'CM' => '? Not to be imported.',
      'charging' => '? Not to be imported',
      'suspended' => 'Whether the individual is suspended or not.',
      'dues' => '? No Mapping. Not to be imported.',
      'exp_date' => 'Customer expiration date.',
      'memb_notes' => 'Membership Notes.',
      'cust_notes' => 'Customer Notes.',
      'last_udate' => 'The Last Udpated date and by',
      'address' => 'Address ID... Can be used ad Address entity ID Reference.',
      'phone' => 'Phone ID... Can be used as phone ID Reference.',
    );
    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'PersonJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('person', 'person');

    $this->addFieldMapping('id', 'old_customer_id')
      ->description('Mapping old_customer_id to entity id');
    // $this->addFieldMapping('barcode_entity', 'barcode')
    // ->description('Mapping barcode to barcode_entity');
    $this->addFieldMapping('field_status', 'status')
      ->description('Mapping status to field_status');
    $this->addFieldMapping('type', 'patron_type')
      ->description('Mapping patron_type to type');
    // $this->addFieldMapping('area', 'area')
    // ->description('Mapping area to area');
    $this->addFieldMapping('field_foa', 'foa')
      ->description('Mapping foa to field_foa');
    $this->addFieldMapping('first', 'first')
      ->description('Mapping first to first');
    $this->addFieldMapping('middle', 'middle')
      ->description('Mapping middle to middle');
    $this->addFieldMapping('last', 'last')
      ->description('Mapping last to last');
    $this->addFieldMapping('esquire', 'title')
      ->description('Mapping title to esquire');
    $this->addFieldMapping('email', 'email')
      ->description('Mapping email to email');
    // $this->addFieldMapping('CM', 'CM')
    // ->description('Mapping CM to CM');
    $this->addFieldMapping('suspended', 'suspended')
       ->description('Mapping suspended to suspended');
    // $this->addFieldMapping('dues', 'dues')
    // ->description('Mapping dues to dues');
    $this->addFieldMapping('exp_date', 'exp_date')
      ->description('Mapping exp_date to expt_date');
    $this->addFieldMapping('memb_notes', 'memb_notes')
      ->description('Mapping memb_notes to memb_notes');
    $this->addFieldMapping('cust_notes', 'cust_notes')
      ->description('Mapping cust_notes to cust_notes');
    // $this->addFieldMapping('last_update', 'last_update')
    // ->description('Mapping last_update to last_update');
    $this->addFieldMapping('phone_entity', 'phone')
      ->description('Phone to Phone Numbers entity');
    $this->addFieldMapping('address_entity', 'address')
      ->description('Mapping address to Address entity');
  }
}
