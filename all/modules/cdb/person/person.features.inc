<?php
/**
 * @file
 * person.features.inc
 */

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
      'label' => 'Changed',
      'type' => 'integer',
      'behavior' => 'changed',
    ),
    'another_property' => array(
      'label' => 'Another property',
      'type' => 'text',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}
