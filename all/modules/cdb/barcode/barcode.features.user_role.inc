<?php
/**
 * @file
 * barcode.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function barcode_user_default_roles() {
  $roles = array();

  // Exported role: Barcode Administrator.
  $roles['Barcode Administrator'] = array(
    'name' => 'Barcode Administrator',
    'weight' => '3',
  );

  return $roles;
}
