<?php
/**
 * @file
 * company.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function company_user_default_roles() {
  $roles = array();

  // Exported role: Company Administrator.
  $roles['Company Administrator'] = array(
    'name' => 'Company Administrator',
    'weight' => '3',
  );

  return $roles;
}
