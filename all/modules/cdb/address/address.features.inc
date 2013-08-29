<?php
/**
 * @file
 * address.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function address_eck_bundle_info() {
  $items = array(
  'address_address' => array(
  'machine_name' => 'address_address',
  'entity_type' => 'address',
  'name' => 'address',
  'label' => 'address',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function address_eck_entity_type_info() {
$items = array(
       'address' => array(
  'name' => 'address',
  'label' => 'address',
  'properties' => array(
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'changed' => array(
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
  ),
),
  );
  return $items;
}
