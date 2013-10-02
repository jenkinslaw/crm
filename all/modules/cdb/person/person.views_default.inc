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
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['barcode_entity_target_id']['id'] = 'barcode_entity_target_id';
  $handler->display->display_options['relationships']['barcode_entity_target_id']['table'] = 'field_data_barcode_entity';
  $handler->display->display_options['relationships']['barcode_entity_target_id']['field'] = 'barcode_entity_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_company_target_id']['id'] = 'field_company_target_id';
  $handler->display->display_options['relationships']['field_company_target_id']['table'] = 'field_data_field_company';
  $handler->display->display_options['relationships']['field_company_target_id']['field'] = 'field_company_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['id'] = 'phone_number_entity_target_id';
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['table'] = 'field_data_phone_number_entity';
  $handler->display->display_options['relationships']['phone_number_entity_target_id']['field'] = 'phone_number_entity_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['address_entity_target_id']['id'] = 'address_entity_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['table'] = 'field_data_address_entity';
  $handler->display->display_options['relationships']['address_entity_target_id']['field'] = 'address_entity_target_id';
  /* Relationship: Person: Last Updated By */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'eck_person';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Person: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_person';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Member Number';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: person: Person Category */
  $handler->display->display_options['fields']['field_person_category']['id'] = 'field_person_category';
  $handler->display->display_options['fields']['field_person_category']['table'] = 'field_data_field_person_category';
  $handler->display->display_options['fields']['field_person_category']['field'] = 'field_person_category';
  $handler->display->display_options['fields']['field_person_category']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_person_category']['multi_type'] = 'ul';
  /* Field: barcode: barcode */
  $handler->display->display_options['fields']['barcode']['id'] = 'barcode';
  $handler->display->display_options['fields']['barcode']['table'] = 'field_data_barcode';
  $handler->display->display_options['fields']['barcode']['field'] = 'barcode';
  $handler->display->display_options['fields']['barcode']['relationship'] = 'barcode_entity_target_id';
  /* Field: person: FOA */
  $handler->display->display_options['fields']['field_foa']['id'] = 'field_foa';
  $handler->display->display_options['fields']['field_foa']['table'] = 'field_data_field_foa';
  $handler->display->display_options['fields']['field_foa']['field'] = 'field_foa';
  $handler->display->display_options['fields']['field_foa']['delta_offset'] = '0';
  /* Field: person: Last Name */
  $handler->display->display_options['fields']['last']['id'] = 'last';
  $handler->display->display_options['fields']['last']['table'] = 'field_data_last';
  $handler->display->display_options['fields']['last']['field'] = 'last';
  /* Field: person: First Name */
  $handler->display->display_options['fields']['first']['id'] = 'first';
  $handler->display->display_options['fields']['first']['table'] = 'field_data_first';
  $handler->display->display_options['fields']['first']['field'] = 'first';
  /* Field: person: Middle Name */
  $handler->display->display_options['fields']['middle']['id'] = 'middle';
  $handler->display->display_options['fields']['middle']['table'] = 'field_data_middle';
  $handler->display->display_options['fields']['middle']['field'] = 'middle';
  /* Field: person: Status */
  $handler->display->display_options['fields']['field_status']['id'] = 'field_status';
  $handler->display->display_options['fields']['field_status']['table'] = 'field_data_field_status';
  $handler->display->display_options['fields']['field_status']['field'] = 'field_status';
  /* Field: person: Patron Type */
  $handler->display->display_options['fields']['patron_type']['id'] = 'patron_type';
  $handler->display->display_options['fields']['patron_type']['table'] = 'field_data_patron_type';
  $handler->display->display_options['fields']['patron_type']['field'] = 'patron_type';
  /* Field: Field: Expiration Date */
  $handler->display->display_options['fields']['exp_date']['id'] = 'exp_date';
  $handler->display->display_options['fields']['exp_date']['table'] = 'field_data_exp_date';
  $handler->display->display_options['fields']['exp_date']['field'] = 'exp_date';
  $handler->display->display_options['fields']['exp_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address']['id'] = 'address';
  $handler->display->display_options['fields']['address']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address']['field'] = 'address';
  $handler->display->display_options['fields']['address']['relationship'] = 'address_entity_target_id';
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
