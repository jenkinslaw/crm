<?php

/**
 * @file
 * Because the name of this file is the module name plus '.migrate.inc', when
 * hook_migrate_api is invoked by the Migrate module this file is automatically
 * loaded - thus, you don't need to implement your hook in the .module file.
 */

/**
 * Implements hook_migrate_api().
 */
function customer_migrate_api() {
  $api = array(
    'api' => 2,
    'field handlers' => array('MigrateAddressFieldHandler'),
    'migrations' => array(
      'Company' => array('class_name' => 'CompanyMigration'),
      'Person'  => array('class_name' => 'PersonMigration'),
      'Contact' => array('class_name' => 'ContactMigration'),
      'Address' => array('class_name' => 'AddressMigration'),
      'Phone'   => array('class_name' => 'PhoneMigration'),
      'Barcode' => array('class_name' => 'BarcodeMigration'),
      'User'    => array('class_name' => 'UserMigration'),
    ),
  );
  return $api;
}
