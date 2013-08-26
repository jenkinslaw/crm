<?php
/**
 * @file
 * phone_number.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function phone_number_eck_bundle_info() {
  $items = array(
  'phone_number_phone_number' => array(
  'machine_name' => 'phone_number_phone_number',
  'entity_type' => 'phone_number',
  'name' => 'phone_number',
  'label' => 'Phone Number',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function phone_number_eck_entity_type_info() {
$items = array(
       'phone_number' => array(
  'name' => 'phone_number',
  'label' => 'Phone Number',
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
    'number' => array(
      'label' => 'Number',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
