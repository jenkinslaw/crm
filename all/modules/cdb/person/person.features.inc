<?php
/**
 * @file
 * person.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function person_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function person_eck_bundle_info() {
  $items = array(
  'person_person' => array(
  'machine_name' => 'person_person',
  'entity_type' => 'person',
  'name' => 'person',
  'label' => 'person',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function person_eck_entity_type_info() {
$items = array(
       'person' => array(
  'name' => 'person',
  'label' => 'person',
  'properties' => array(
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'changed' => array(
      'label' => 'Last Updated',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
    'name' => array(
      'label' => 'Name',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'uid' => array(
      'label' => 'Last Updated By',
      'type' => 'integer',
      'behavior' => 'author',
    ),
  ),
),
  );
  return $items;
}
