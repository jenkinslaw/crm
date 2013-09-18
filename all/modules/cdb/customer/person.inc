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

    $this->dependencies = array('Address','Phone','Barcode','Company');
    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/customer.php';
    $fields = array(
      'id' => 'Cutomer Record ID.',
      'barcode' => 'Barcode ID.',
      'status' => 'Essentially type of patron occupation (i.e. Attorney)',
      'area' => 'Missing Map: A location category (i.e. Remote, Local, etc.)',
      'foa' => 'Customer Form of Address.',
      'first' => 'Customer First Name.',
      'middle' => 'Customer Middle Initial.',
      'last' => 'Customer Last Name.',
      'email' => 'Customer email.',
      'name'  => "constructed field of Last name, First name",
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

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Person ID',
          'alias' => 'pid',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );


    $this->destination = new MigrateDestinationEntityAPI('person', 'person');

    $this->addFieldMapping('id', 'id')
      ->description('Mapping old_customer_id to entity id');
    $this->addFieldMapping('barcode_entity', 'barcode')
      ->description('Mapping barcode to barcode_entity')
      ->sourceMigration('Barcode');
    $this->addFieldMapping('field_status', 'status')
      ->callbacks(array($this, 'setStatusKey'))
      ->description('Mapping status to field_status');
    $this->addFieldMapping('field_person_category')
      ->defaultValue('c')
      ->description('Create all Person as customer type');
    $this->addFieldMapping('patron_type', 'patron_type')
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
    $this->addFieldMapping('esquire', 'esquire')
      ->description('Mapping title to esquire');
    $this->addFieldMapping('suffix', 'suffix')
      ->description('Mapping suffix to suffix');
    $this->addFieldMapping('name', 'name')
      ->description('The constructed name for presentation');
    $this->addFieldMapping('email', 'email')
      ->description('Mapping email to email');
    $this->addFieldMapping('suspended', 'suspended')
       ->description('Mapping suspended to suspended');
    // $this->addFieldMapping('dues', 'dues')
    // ->description('Mapping dues to dues');
    $this->addFieldMapping('exp_date', 'exp_date')
      ->description('Mapping exp_date to exp_date');
    $this->addFieldMapping('memb_notes', 'memb_notes')
      ->description('Mapping memb_notes to memb_notes');
    $this->addFieldMapping('cust_notes', 'cust_notes')
      ->description('Mapping cust_notes to cust_notes');
    // $this->addFieldMapping('last_update_date', 'last_update_date')
    // ->description('Mapping last_update to last_update');
    $this->addFieldMapping('phone_entity', 'phone')
      ->description('Phone to Phone Numbers entity')
      ->sourceMigration('Phone');
    $this->addFieldMapping('address_entity', 'address')
      ->description('Mapping address to Address entity')
      ->sourceMigration('Address');
  }

  protected function setStatusKey($status) {
    $status = ($status == "a" || $status == "c")? "m" : $status;
    return $status;
  }
}
