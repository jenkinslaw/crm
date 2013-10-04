<?php
/**
 * @file
 * person.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function person_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'person_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_person';
  $view->human_name = 'Person Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Person Search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['barcode_entity_target_id']['id'] = 'barcode_entity_target_id';
  $handler->display->display_options['relationships']['barcode_entity_target_id']['table'] = 'field_data_barcode_entity';
  $handler->display->display_options['relationships']['barcode_entity_target_id']['field'] = 'barcode_entity_target_id';
  $handler->display->display_options['relationships']['barcode_entity_target_id']['label'] = 'Barcode Entity';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_company_target_id']['id'] = 'field_company_target_id';
  $handler->display->display_options['relationships']['field_company_target_id']['table'] = 'field_data_field_company';
  $handler->display->display_options['relationships']['field_company_target_id']['field'] = 'field_company_target_id';
  $handler->display->display_options['relationships']['field_company_target_id']['label'] = 'Company Entity';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['id'] = 'phone_number_entity_target_id';
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['table'] = 'field_data_phone_number_entity';
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['field'] = 'phone_number_entity_target_id';
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['label'] = 'Phone Number Entity';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['address_entity_target_id']['id'] = 'address_entity_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['table'] = 'field_data_address_entity';
  $handler->display->display_options['relationships']['address_entity_target_id']['field'] = 'address_entity_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['label'] = 'Company Address Entity';
  /* Field: Person: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_person';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Member Number';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Filter criterion: Person: person type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_person';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'person' => 'person',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'person-search';
  $export['person_search'] = $view;

  return $export;
}
