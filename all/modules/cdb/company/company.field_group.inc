<?php
/**
 * @file
 * company.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function company_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_phone|company|company|form';
  $field_group->group_name = 'group_phone';
  $field_group->entity_type = 'company';
  $field_group->bundle = 'company';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Phone',
    'weight' => '6',
    'children' => array(
      0 => 'phone_type',
      1 => 'phone_number',
    ),
    'format_type' => 'field_group_multiple_container',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'parent_format_type' => 'div',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_phone|company|company|form'] = $field_group;

  return $export;
}
