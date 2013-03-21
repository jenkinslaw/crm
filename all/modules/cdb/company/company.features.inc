<?php
/**
 * @file
 * company.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function company_eck_bundle_info() {
  $items = array(
  'company_company' => array(
  'machine_name' => 'company_company',
  'entity_type' => 'company',
  'name' => 'company',
  'label' => 'company',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function company_eck_entity_type_info() {
$items = array(
       'company' => array(
  'name' => 'company',
  'label' => 'company',
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
    'company_name' => array(
      'label' => 'Company Name',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
