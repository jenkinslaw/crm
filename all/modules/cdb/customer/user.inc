<?php

/**
 * @file
 * user.inc
 *
 * Migration tasks for users of cdb, ie Jenkins Staff.
 */

class UserJSONReader extends MigrateJSONReader {
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
class UserMigration extends BasicMigration {
  /**
   * Implements BasicMigration::__construct().
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('User Migration');

    $source_url = 'http://staging.website.dev.jenkinslaw.org/sites/all/modules/jenkins/cdb_access/cdbapi/migration/user.php';
    $fields = array(
      'username' => 'The Username',
      'id'  => 'Numeric hash of username.',
      'mail' => 'Email address of the user',
      'active' => "Is the user allowed to login",
      'password' => "Teh passw0rd",
      'roles' => 'The roles the user should have',
   );
    
    $this->source = new MigrateSourceJSON($source_url, 'id', $fields,
      array('reader_class' => 'UserJSONReader'));

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'User name',
          'alias' => 'username',
        ),
      ),
      MigrateDestinationNode::getKeySchema(),
      'default',
      array('track_last_imported' => TRUE)
    );


    $options = array();
    $this->destination = new MigrateDestinationUser($options);

    $this->addFieldMapping('id', 'id')
      ->description('Mapping hash_id to id');
    $this->addFieldMapping('name', 'username')
      ->dedupe('users', 'name')
      ->description('Mapping username to name');
    $this->addFieldMapping('mail', 'mail')
      ->description('Mapping  email address to mail');
    $this->addFieldMapping('pass','password')
      ->description('Migrates users password to a sha512 encrypted password');
    $this->addFieldMapping('status','active')
      ->description('Map active to status');
    $this->addFieldMapping('created')
      ->description('Created time will be when imported into Drupal');
    $this->addFieldMapping('access')
      ->description('Created and set to time of creation');
    $this->addFieldMapping('login')
      ->description('Created and set to time of creation');
    $this->addFieldMapping('roles','roles')
      ->callbacks(array($this, 'roleMapping'))
      ->description('Role IDs to assign to the user');
  }

  public function roleMapping($role) {
    if ($role == '1') {
      $role = array(2, 4, 5, 6, 7, 8, 9);
    }
    else {
      $role = array(2, 8);
    }
    return $role;
  }

}
