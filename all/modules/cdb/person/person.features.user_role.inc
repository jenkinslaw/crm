<?php
/**
 * @file
 * person.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function person_user_default_roles() {
  $roles = array();

  // Exported role: Person Administrator.
  $roles['Person Administrator'] = array(
    'name' => 'Person Administrator',
    'weight' => '4',
  );

  return $roles;
}
