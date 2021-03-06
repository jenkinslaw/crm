<?php
/**
 * @file
 * barcode.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function barcode_eck_bundle_info() {
  $items = array(
  'barcode_barcode' => array(
  'machine_name' => 'barcode_barcode',
  'entity_type' => 'barcode',
  'name' => 'barcode',
  'label' => 'barcode',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function barcode_eck_entity_type_info() {
$items = array(
       'barcode' => array(
  'name' => 'barcode',
  'label' => 'barcode',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
