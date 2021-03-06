<?php
/**
 * @file
 * company.inc
 * 
 * Migrates company opbjects to D7 from Cdb.
 */

module_load_include('inc', 'migrate_extras', 'entity_api');

class CompanyJSONReader extends MigrateJSONReader {
  /**
   * Implements MigrateJSONReader::next().
   */
  public function next() {

    // Overide here for company specific JSON parsor.
    parent::next();

  }
}

abstract class BasicMigration extends DynamicMigration {
  /**
   * Implements DynamicMigration::_construct().
   */
  public function __construct() {
    parent::__construct();

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default
    // the list in the shared class; it can be overridden for specific
    // migrations.
    $this->team = array(
      new MigrateTeamMember('David Kinzer', 'dkinzer@jenkinslaw.org', t('Dev')),
      new MigrateTeamMember('Chad Nelson', 'cnelson@jenkinslaw.org', t('Dev')),
    );

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    $this->issuePattern = 'https://github.com/jenkinslaw/cdb/issues/:id:';
  }
}


/**
 * Migration steps for Company entity.
 */
class CompanyMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Company Migration');
    
    $this->dependencies = array('Address', 'Phone', 'Contact');

    $fields = array(
      'id' => 'Company id',
      'company_name' => 'The Company name.',
      'suspended' => 'Whether or not company is suspended.',
      'address_id' => 'Reference ID to the Company addresses.',
      'exp_date' => 'Date the company membership ends.',
      'company_category' => 'Type of membership ID.',
      'billing_area' => 'One of L or S or R, the Area ID.',
      'website' => 'URL for the Company website.',
      'memb_notes' => 'Random misc. notes.',
      'cust_notes' => 'Random misc. customer notes',
      'account_number' => 'Company account number',
      'number_of_attorneys' => 'Total number of attorneys in Company.',
      'last_updated' => 'The last date/time the Company record was updated.',
      'updated_by' => 'The uid of the User who updated the Company Record.',
      'phone_numbers' => 'IDs of Company Phone Numbers (Multiples Possible).',
      'membership_contact' => 'Person ID for membership contact.',
      'billing_contact' => 'Person ID for billing contact.',
      'mas90_name' => 'Mas90 Name.',
    );
    $limit = get_cdb_migrate_limit();

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/company.php?' . $limit;

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'CompanyJSONReader'));

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Company ID',
          'alias' => 'cid',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );

    $this->destination = new MigrateDestinationEntityAPI('company', 'company');

    $this->addFieldMapping('id', 'id')
      ->description('Mapping company id to entity_id');
    $this->addFieldMapping('company_name', 'company_name')
      ->description('Mapping company_name to company_name');
    $this->addFieldMapping('suspended', 'suspended')
      ->description('Mapping suspended to suspended');
    $this->addFieldMapping('address_entity', 'address_id')
      ->description('Mapping address_id to address_entity')
      ->sourceMigration('Address');
    $this->addFieldMapping('exp_date', 'exp_date')
      ->description('Mapping exp_date to exp_date');
    $this->addFieldMapping('company_category', 'company_category')
      ->description('Mapping company_category to company_category');
    $this->addFieldMapping('billing_area', 'billing_area')
      ->description('Mapping billing_area to billing_area');
    $this->addFieldMapping('website', 'website')
      ->description('Mapping website to website');
    $this->addFieldMapping('memb_notes', 'memb_notes')
      ->description('Mapping member_notes to member_notes');
    $this->addFieldMapping('cust_notes', 'cust_notes')
      ->description('Mapping cust_notes to cust_notes');
    $this->addFieldMapping('account_number', 'account_number')
      ->description('Mapping account_number to account_number');
    $this->addFieldMapping('number_of_attorneys', 'number_of_attorneys')
      ->description('Mapping number_of_attorneys to number_of_attorneys');
    $this->addFieldMapping('changed', 'last_updated')
      ->description('Mapping last_updated to changed');
    $this->addFieldMapping('phone_entity', 'phone_numbers')
      ->description('Mapping phone_numbers to phone_entity')
      ->sourceMigration('Phone');
    $this->addFieldMapping('uid', 'updated_by')
      ->description('Mapping updated_by to uid')
      ->sourceMigration('User');
    $this->addFieldMapping('membership_contact', 'membership_contact')
      ->description('Mapping membership_contact to membership_contact')
      ->sourceMigration('Contact');
    $this->addFieldMapping('billing_contact', 'billing_contact')
      ->description('Mapping billing_contact to billng_contact')
      ->sourceMigration('Contact');
    $this->addFieldMapping('mas90_name', 'mas90_name')
      ->description('Mapping mas90_name to mas90_name');
  }
}
