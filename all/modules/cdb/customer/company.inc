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
    // Overide here for company specific JSON parson.
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

    $fields = array(
      'id' => 'Company id',
      'company_name' => 'The Company name.',
      'suspended' => 'Whether or not company is suspended.',
      'address' => 'Reference id to the Company address.',
      'exp_date' => 'Date the company membership ends.',
      'company_category' => 'Type of membership.',
      'billing_area' => 'One of Local or State or Regional',
      'website' => 'URL for the Company website.',
      'memb_notes' => 'Random misc. noets.',
      'cust_notes' => '',
      'account_number' => 'Company account number',
      'number_of_attorneys' => 'Total number of attorneys in Company.',
      'last_updated' => 'The last date/time the Company record was updated.',
      'updated_by' => 'The uid of the User who updated the Company Record.',
    );

    // $source_url = 'http://dkinzer.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/company.php';
    $source_url = 'sites/all/modules/cdb/customer/company.json';

    $this->source = new MigrateSourceJSON($source_url, 'old_company_id', $fields,
      array('reader_class' => 'CompanyJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('company', 'company');

    $this->addFieldMapping('old_company_id', 'id')
      ->description('Mapping old_copany_id to entity_id');
    $this->addFieldMapping('company_name', 'company_name')
      ->description('Mapping company_name to company_name');
    $this->addFieldMapping('suspended', 'suspended')
      ->description('Mapping suspended to suspended');
    $this->addFieldMapping('address', 'address')
      ->description('Mapping address to address');
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
    $this->addFieldMapping('last_updated', 'last_updated')
      ->description('Mapping last_updated to last_updated');
    $this->addFieldMapping('updated_by', 'updated_by')
      ->description('Mapping updated_by to updated_by');
  }
}
