<?php

/**
 * @file
 * company.inc
 * 
 * Migrates company opbjects to D7 from Cdb.
 */

class CompanyJSONReader extends MigrationJSONReader {
  /**
   * Implements MigrationJSONReader::next().
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

    $source_url = 'http://cnelson.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/company.json';
    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'CompanyJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('company', 'company');

    $this->addFieldMapping('title', 'name')
         ->description(t('Mapping beer name in source to node title'));
    $this->addFieldMapping('sticky')
         ->description(t('Should we default this to 0 or 1?'))
         ->issueGroup(t('Client questions'))
         ->issueNumber(765736)
         ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_LOW);
  }
}
