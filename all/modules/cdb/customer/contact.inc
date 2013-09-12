<?php

/**
 * @file
 * person.inc
 *
 * Migration tasks for contacts to the person entity.
 */

class ContactJSONReader extends MigrateJSONReader {
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
class ContactMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Contact Migration');

    $this->dependencies = array('Address');
    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/contact.php?increment=100000';
    $fields = array(
      'id' => 'Cutomer Record ID.',
      'patron_type' => 'Essentially type of patron occupation (i.e. Attorney)',
      'foa' => 'Customer Form of Address.',
      'first' => 'Customer First Name.',
      'middle' => 'Customer Middle Initial.',
      'last' => 'Customer Last Name.',
      'suffix' => 'Whatever Suffix they might have had',
      'esquire' => '1 for they are and Esquire, 0 for not',
      'name' => 'Last name, First Name',
      'email' => 'Customer email.',
      'address' => 'Address ID... Can be used ad Address entity ID Reference.',
      'phone' => 'Phone ID... Can be used as phone ID Reference.',
    );
    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'ContactJSONReader'));

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Contact ID',
          'alias' => 'contact_id',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );


    $this->destination = new MigrateDestinationEntityAPI('person', 'person');

    $this->addFieldMapping('id', 'id')
      ->description('Mapping old_contact_id to entity id');
    $this->addFieldMapping('barcode_entity')
      ->description('Mapping barcode to barcode_entity')
      ->defaultValue('');
    $this->addFieldMapping('field_person_category','patron_type')
      ->callbacks($this, 'contactType');
    $this->addFieldMapping('field_status')
      ->defaultValue('m')->description('All contacts get status m for Misc');
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
      ->description('Mapping constructed full name to name');
    $this->addFieldMapping('email', 'email')
      ->description('Mapping email to email');
    $this->addFieldMapping('suspended')
      ->defaultValue('y')->description('All contacts are by defaul suspended');
    $this->addFieldMapping('phone_number_entity', 'phone')
      ->description('Phone to Phone Numbers entity')
      ->sourceMigration('Phone');
    $this->addFieldMapping('address_entity', 'address')
      ->description('Mapping address to Address entity')
      ->sourceMigration('Address');
    $this->addUnmigratedDestinations(array('memb_notes', 'cust_notes','exp_date'));
  }

  protected function contactType($type){
    return ($type == "Billing")? 'b' : 'm';
  }

}
