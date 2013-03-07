<?php
/**
 * @file
 * person.features.inc
 */

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
  ),
),
  );
  return $items;
}
