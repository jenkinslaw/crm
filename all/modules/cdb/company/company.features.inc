<?php
/**
 * @file
 * company.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function company_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function company_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function company_eck_bundle_info() {
  $items = array(
  'company_company' => array(
  'machine_name' => 'company_company',
  'entity_type' => 'cdb',
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
    'company_name' => array(
      'label' => 'Company Name',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'account_number' => array(
      'label' => 'Account Number',
      'type' => 'text',
      'behavior' => '',
    ),
    'number_of_attorneys' => array(
      'label' => 'Number of Attorneys',
      'type' => 'integer',
      'behavior' => '',
    ),
    'last_updated' => array(
      'label' => 'Last Updated',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
    'updated_by' => array(
      'label' => 'Last Updated By',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'old_company_id' => array(
      'label' => 'Old Company Id',
      'type' => 'text',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}
