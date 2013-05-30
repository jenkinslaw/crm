<?php

/**
 * @file
 * person.inc
 *
 * Migration tasks for person entity.
 */

class PersonJSONReader extends MigrationJSONReader {
  /**
   * Implements MigrationJSONReader::next().
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
    $this->dependencies = array('CompanyMigration');

    $source_url = 'http://cnelson.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/person.json';

    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'CompanyJSONReader'));

    $this->destination = new MigrateDestinationEntityAPI('person', 'person');

    $this->addFieldMapping('title', 'name')
         ->description(t('Mapping beer name in source to node title'));
    $this->addFieldMapping('sticky')
         ->description(t('Should we default this to 0 or 1?'))
         ->issueGroup(t('Client questions'))
         ->issueNumber(765736)
         ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_LOW);
  }
}
