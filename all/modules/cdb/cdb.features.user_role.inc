<?php
/**
 * @file
 * cdb.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cdb_user_default_roles() {
  $roles = array();

  $roles['Payment Administrator'] = array(
    'name' => 'Payment Administrator',
    'weight' => '3',
  );
  
  $roles['Search Exporter'] = array(
    'name' => 'Search Exporter',
    'weight' => '3',
  );

 $roles['Reference Invoicer'] = array(
    'name' => 'Reference Invoicer',
    'weight' => '3',
  );

  return $roles;
}
