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
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'field_person_category' => 'field_person_category',
    'barcode_entity' => 'barcode_entity',
    'field_foa' => 'field_foa',
    'last' => 'last',
    'first' => 'first',
    'middle' => 'middle',
    'field_status' => 'field_status',
    'patron_type' => 'patron_type',
    'exp_date' => 'exp_date',
    'company_name' => 'company_name',
    'mas90_name' => 'mas90_name',
    'exp_date_1' => 'exp_date_1',
    'suffix' => 'suffix',
    'esquire' => 'esquire',
    'phone_number_entity' => 'phone_number_entity',
    'phone_entity' => 'phone_entity',
    'email' => 'email',
    'cle_special' => 'cle_special',
    'address' => 'address',
    'address_1' => 'address_1',
    'address_2' => 'address_2',
    'address_3' => 'address_3',
    'address_4' => 'address_4',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_person_category' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'barcode_entity' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_foa' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'first' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'middle' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'patron_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'exp_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'company_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mas90_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'exp_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'suffix' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'esquire' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'phone_number_entity' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'phone_entity' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'cle_special' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_2' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_3' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_4' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
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
  /* Relationship: Person: Last Updated By */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'eck_person';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Comapny address entity */
  $handler->display->display_options['relationships']['address_entity_target_id']['id'] = 'address_entity_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['table'] = 'field_data_address_entity';
  $handler->display->display_options['relationships']['address_entity_target_id']['field'] = 'address_entity_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['ui_name'] = 'Comapny address entity';
  /* Field: person: Person Category */
  $handler->display->display_options['fields']['field_person_category']['id'] = 'field_person_category';
  $handler->display->display_options['fields']['field_person_category']['table'] = 'field_data_field_person_category';
  $handler->display->display_options['fields']['field_person_category']['field'] = 'field_person_category';
  $handler->display->display_options['fields']['field_person_category']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_person_category']['multi_type'] = 'ul';
  /* Field: Person: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_person';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Member Number';
  $handler->display->display_options['fields']['id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['path'] = '/person/[id]';
  $handler->display->display_options['fields']['id']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['alt'] = 'Full Record for this person';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: person: Barcode */
  $handler->display->display_options['fields']['barcode_entity']['id'] = 'barcode_entity';
  $handler->display->display_options['fields']['barcode_entity']['table'] = 'field_data_barcode_entity';
  $handler->display->display_options['fields']['barcode_entity']['field'] = 'barcode_entity';
  $handler->display->display_options['fields']['barcode_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['barcode_entity']['delta_offset'] = '0';
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
  /* Field: company: Mas90 Name */
  $handler->display->display_options['fields']['mas90_name']['id'] = 'mas90_name';
  $handler->display->display_options['fields']['mas90_name']['table'] = 'field_data_mas90_name';
  $handler->display->display_options['fields']['mas90_name']['field'] = 'mas90_name';
  $handler->display->display_options['fields']['mas90_name']['relationship'] = 'field_company_target_id';
  /* Field: Company: Company Name */
  $handler->display->display_options['fields']['company_name']['id'] = 'company_name';
  $handler->display->display_options['fields']['company_name']['table'] = 'eck_company';
  $handler->display->display_options['fields']['company_name']['field'] = 'company_name';
  $handler->display->display_options['fields']['company_name']['relationship'] = 'field_company_target_id';
  /* Field: Field: Expiration Date */
  $handler->display->display_options['fields']['exp_date_1']['id'] = 'exp_date_1';
  $handler->display->display_options['fields']['exp_date_1']['table'] = 'field_data_exp_date';
  $handler->display->display_options['fields']['exp_date_1']['field'] = 'exp_date';
  $handler->display->display_options['fields']['exp_date_1']['settings'] = array(
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
  $handler->display->display_options['fields']['address']['label'] = 'Address Line 1';
  $handler->display->display_options['fields']['address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address']['alter']['text'] = '[address-thoroughfare]';
  $handler->display->display_options['fields']['address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_1']['id'] = 'address_1';
  $handler->display->display_options['fields']['address_1']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_1']['field'] = 'address';
  $handler->display->display_options['fields']['address_1']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_1']['label'] = 'Address Line 2';
  $handler->display->display_options['fields']['address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_1']['alter']['text'] = '[address_1-premise]';
  $handler->display->display_options['fields']['address_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_2']['id'] = 'address_2';
  $handler->display->display_options['fields']['address_2']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_2']['field'] = 'address';
  $handler->display->display_options['fields']['address_2']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_2']['label'] = 'City';
  $handler->display->display_options['fields']['address_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_2']['alter']['text'] = '[address_2-locality]';
  $handler->display->display_options['fields']['address_2']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_2']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_3']['id'] = 'address_3';
  $handler->display->display_options['fields']['address_3']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_3']['field'] = 'address';
  $handler->display->display_options['fields']['address_3']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_3']['label'] = 'State';
  $handler->display->display_options['fields']['address_3']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_3']['alter']['text'] = '[address_3-administrative_area]';
  $handler->display->display_options['fields']['address_3']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_3']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_4']['id'] = 'address_4';
  $handler->display->display_options['fields']['address_4']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_4']['field'] = 'address';
  $handler->display->display_options['fields']['address_4']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_4']['label'] = 'Zip';
  $handler->display->display_options['fields']['address_4']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_4']['alter']['text'] = '[address_4-postal_code]';
  $handler->display->display_options['fields']['address_4']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_4']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: person: suffix */
  $handler->display->display_options['fields']['suffix']['id'] = 'suffix';
  $handler->display->display_options['fields']['suffix']['table'] = 'field_data_suffix';
  $handler->display->display_options['fields']['suffix']['field'] = 'suffix';
  $handler->display->display_options['fields']['suffix']['label'] = 'Suffix';
  /* Field: person: Esquire */
  $handler->display->display_options['fields']['esquire']['id'] = 'esquire';
  $handler->display->display_options['fields']['esquire']['table'] = 'field_data_esquire';
  $handler->display->display_options['fields']['esquire']['field'] = 'esquire';
  /* Field: person: Phone Number */
  $handler->display->display_options['fields']['phone_number_entity']['id'] = 'phone_number_entity';
  $handler->display->display_options['fields']['phone_number_entity']['table'] = 'field_data_phone_number_entity';
  $handler->display->display_options['fields']['phone_number_entity']['field'] = 'phone_number_entity';
  $handler->display->display_options['fields']['phone_number_entity']['label'] = 'Phone';
  $handler->display->display_options['fields']['phone_number_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['phone_number_entity']['delta_offset'] = '0';
  $handler->display->display_options['fields']['phone_number_entity']['multi_type'] = 'ul';
  /* Field: company: Phone Number */
  $handler->display->display_options['fields']['phone_entity']['id'] = 'phone_entity';
  $handler->display->display_options['fields']['phone_entity']['table'] = 'field_data_phone_entity';
  $handler->display->display_options['fields']['phone_entity']['field'] = 'phone_entity';
  $handler->display->display_options['fields']['phone_entity']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['fields']['phone_entity']['label'] = 'Company Phone';
  $handler->display->display_options['fields']['phone_entity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['phone_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['phone_entity']['delta_offset'] = '0';
  /* Field: person: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'field_data_email';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  /* Field: person: cle_special */
  $handler->display->display_options['fields']['cle_special']['id'] = 'cle_special';
  $handler->display->display_options['fields']['cle_special']['table'] = 'field_data_cle_special';
  $handler->display->display_options['fields']['cle_special']['field'] = 'cle_special';
  $handler->display->display_options['fields']['cle_special']['label'] = 'CLE Special';
  /* Field: Bulk operations: Person */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_person';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  /* Sort criterion: Person: Id */
  $handler->display->display_options['sorts']['id']['id'] = 'id';
  $handler->display->display_options['sorts']['id']['table'] = 'eck_person';
  $handler->display->display_options['sorts']['id']['field'] = 'id';
  $handler->display->display_options['sorts']['id']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['id']['expose']['label'] = 'Member Number';
  /* Sort criterion: person: Barcode (barcode_entity) */
  $handler->display->display_options['sorts']['barcode_entity_target_id']['id'] = 'barcode_entity_target_id';
  $handler->display->display_options['sorts']['barcode_entity_target_id']['table'] = 'field_data_barcode_entity';
  $handler->display->display_options['sorts']['barcode_entity_target_id']['field'] = 'barcode_entity_target_id';
  $handler->display->display_options['sorts']['barcode_entity_target_id']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['barcode_entity_target_id']['expose']['label'] = 'Barcode';
  /* Sort criterion: person: Status (field_status) */
  $handler->display->display_options['sorts']['field_status_value']['id'] = 'field_status_value';
  $handler->display->display_options['sorts']['field_status_value']['table'] = 'field_data_field_status';
  $handler->display->display_options['sorts']['field_status_value']['field'] = 'field_status_value';
  $handler->display->display_options['sorts']['field_status_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_status_value']['expose']['label'] = 'Status';
  /* Sort criterion: person: Patron Type (patron_type) */
  $handler->display->display_options['sorts']['patron_type_value']['id'] = 'patron_type_value';
  $handler->display->display_options['sorts']['patron_type_value']['table'] = 'field_data_patron_type';
  $handler->display->display_options['sorts']['patron_type_value']['field'] = 'patron_type_value';
  $handler->display->display_options['sorts']['patron_type_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['patron_type_value']['expose']['label'] = 'Patron Type';
  /* Sort criterion: person: FOA (field_foa) */
  $handler->display->display_options['sorts']['field_foa_value']['id'] = 'field_foa_value';
  $handler->display->display_options['sorts']['field_foa_value']['table'] = 'field_data_field_foa';
  $handler->display->display_options['sorts']['field_foa_value']['field'] = 'field_foa_value';
  $handler->display->display_options['sorts']['field_foa_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_foa_value']['expose']['label'] = 'FOA';
  /* Sort criterion: person: Last Name (last) */
  $handler->display->display_options['sorts']['last_value']['id'] = 'last_value';
  $handler->display->display_options['sorts']['last_value']['table'] = 'field_data_last';
  $handler->display->display_options['sorts']['last_value']['field'] = 'last_value';
  $handler->display->display_options['sorts']['last_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['last_value']['expose']['label'] = 'Last Name';
  /* Sort criterion: person: First Name (first) */
  $handler->display->display_options['sorts']['first_value']['id'] = 'first_value';
  $handler->display->display_options['sorts']['first_value']['table'] = 'field_data_first';
  $handler->display->display_options['sorts']['first_value']['field'] = 'first_value';
  $handler->display->display_options['sorts']['first_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['first_value']['expose']['label'] = 'First Name';
  /* Sort criterion: Company: Company Name */
  $handler->display->display_options['sorts']['company_name']['id'] = 'company_name';
  $handler->display->display_options['sorts']['company_name']['table'] = 'eck_company';
  $handler->display->display_options['sorts']['company_name']['field'] = 'company_name';
  $handler->display->display_options['sorts']['company_name']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['sorts']['company_name']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['company_name']['expose']['label'] = 'Company';
  /* Sort criterion: address: address (address:premise) */
  $handler->display->display_options['sorts']['address_premise']['id'] = 'address_premise';
  $handler->display->display_options['sorts']['address_premise']['table'] = 'field_data_address';
  $handler->display->display_options['sorts']['address_premise']['field'] = 'address_premise';
  $handler->display->display_options['sorts']['address_premise']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['sorts']['address_premise']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['address_premise']['expose']['label'] = 'Address Line 1';
  /* Sort criterion: address: address (address:thoroughfare) */
  $handler->display->display_options['sorts']['address_thoroughfare']['id'] = 'address_thoroughfare';
  $handler->display->display_options['sorts']['address_thoroughfare']['table'] = 'field_data_address';
  $handler->display->display_options['sorts']['address_thoroughfare']['field'] = 'address_thoroughfare';
  $handler->display->display_options['sorts']['address_thoroughfare']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['sorts']['address_thoroughfare']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['address_thoroughfare']['expose']['label'] = 'Address Line 2';
  /* Sort criterion: address: address (address:locality) */
  $handler->display->display_options['sorts']['address_locality']['id'] = 'address_locality';
  $handler->display->display_options['sorts']['address_locality']['table'] = 'field_data_address';
  $handler->display->display_options['sorts']['address_locality']['field'] = 'address_locality';
  $handler->display->display_options['sorts']['address_locality']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['sorts']['address_locality']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['address_locality']['expose']['label'] = 'City';
  /* Sort criterion: address: address (address:administrative_area) */
  $handler->display->display_options['sorts']['address_administrative_area']['id'] = 'address_administrative_area';
  $handler->display->display_options['sorts']['address_administrative_area']['table'] = 'field_data_address';
  $handler->display->display_options['sorts']['address_administrative_area']['field'] = 'address_administrative_area';
  $handler->display->display_options['sorts']['address_administrative_area']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['sorts']['address_administrative_area']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['address_administrative_area']['expose']['label'] = 'State';
  /* Sort criterion: address: address (address:postal_code) */
  $handler->display->display_options['sorts']['address_postal_code']['id'] = 'address_postal_code';
  $handler->display->display_options['sorts']['address_postal_code']['table'] = 'field_data_address';
  $handler->display->display_options['sorts']['address_postal_code']['field'] = 'address_postal_code';
  $handler->display->display_options['sorts']['address_postal_code']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['sorts']['address_postal_code']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['address_postal_code']['expose']['label'] = 'Zip';
  /* Filter criterion: person: Person Category (field_person_category) */
  $handler->display->display_options['filters']['field_person_category_value']['id'] = 'field_person_category_value';
  $handler->display->display_options['filters']['field_person_category_value']['table'] = 'field_data_field_person_category';
  $handler->display->display_options['filters']['field_person_category_value']['field'] = 'field_person_category_value';
  $handler->display->display_options['filters']['field_person_category_value']['group'] = 1;
  $handler->display->display_options['filters']['field_person_category_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_person_category_value']['expose']['operator_id'] = 'field_person_category_value_op';
  $handler->display->display_options['filters']['field_person_category_value']['expose']['label'] = 'Person Category';
  $handler->display->display_options['filters']['field_person_category_value']['expose']['operator'] = 'field_person_category_value_op';
  $handler->display->display_options['filters']['field_person_category_value']['expose']['identifier'] = 'field_person_category_value';
  $handler->display->display_options['filters']['field_person_category_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_person_category_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: Person: Id */
  $handler->display->display_options['filters']['id']['id'] = 'id';
  $handler->display->display_options['filters']['id']['table'] = 'eck_person';
  $handler->display->display_options['filters']['id']['field'] = 'id';
  $handler->display->display_options['filters']['id']['group'] = 1;
  $handler->display->display_options['filters']['id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['id']['expose']['operator_id'] = 'id_op';
  $handler->display->display_options['filters']['id']['expose']['label'] = 'Id';
  $handler->display->display_options['filters']['id']['expose']['operator'] = 'id_op';
  $handler->display->display_options['filters']['id']['expose']['identifier'] = 'id';
  $handler->display->display_options['filters']['id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Barcode (barcode_entity) */
  $handler->display->display_options['filters']['barcode_entity_target_id']['id'] = 'barcode_entity_target_id';
  $handler->display->display_options['filters']['barcode_entity_target_id']['table'] = 'field_data_barcode_entity';
  $handler->display->display_options['filters']['barcode_entity_target_id']['field'] = 'barcode_entity_target_id';
  $handler->display->display_options['filters']['barcode_entity_target_id']['group'] = 1;
  $handler->display->display_options['filters']['barcode_entity_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['barcode_entity_target_id']['expose']['operator_id'] = 'barcode_entity_target_id_op';
  $handler->display->display_options['filters']['barcode_entity_target_id']['expose']['label'] = 'Barcode';
  $handler->display->display_options['filters']['barcode_entity_target_id']['expose']['operator'] = 'barcode_entity_target_id_op';
  $handler->display->display_options['filters']['barcode_entity_target_id']['expose']['identifier'] = 'barcode_entity_target_id';
  $handler->display->display_options['filters']['barcode_entity_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: FOA (field_foa) */
  $handler->display->display_options['filters']['field_foa_value']['id'] = 'field_foa_value';
  $handler->display->display_options['filters']['field_foa_value']['table'] = 'field_data_field_foa';
  $handler->display->display_options['filters']['field_foa_value']['field'] = 'field_foa_value';
  $handler->display->display_options['filters']['field_foa_value']['group'] = 1;
  $handler->display->display_options['filters']['field_foa_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_foa_value']['expose']['operator_id'] = 'field_foa_value_op';
  $handler->display->display_options['filters']['field_foa_value']['expose']['label'] = 'FOA';
  $handler->display->display_options['filters']['field_foa_value']['expose']['operator'] = 'field_foa_value_op';
  $handler->display->display_options['filters']['field_foa_value']['expose']['identifier'] = 'field_foa_value';
  $handler->display->display_options['filters']['field_foa_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Last Name (last) */
  $handler->display->display_options['filters']['last_value']['id'] = 'last_value';
  $handler->display->display_options['filters']['last_value']['table'] = 'field_data_last';
  $handler->display->display_options['filters']['last_value']['field'] = 'last_value';
  $handler->display->display_options['filters']['last_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['last_value']['group'] = 1;
  $handler->display->display_options['filters']['last_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['last_value']['expose']['operator_id'] = 'last_value_op';
  $handler->display->display_options['filters']['last_value']['expose']['label'] = 'Last Name';
  $handler->display->display_options['filters']['last_value']['expose']['operator'] = 'last_value_op';
  $handler->display->display_options['filters']['last_value']['expose']['identifier'] = 'last_value';
  $handler->display->display_options['filters']['last_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: First Name (first) */
  $handler->display->display_options['filters']['first_value']['id'] = 'first_value';
  $handler->display->display_options['filters']['first_value']['table'] = 'field_data_first';
  $handler->display->display_options['filters']['first_value']['field'] = 'first_value';
  $handler->display->display_options['filters']['first_value']['group'] = 1;
  $handler->display->display_options['filters']['first_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['first_value']['expose']['operator_id'] = 'first_value_op';
  $handler->display->display_options['filters']['first_value']['expose']['label'] = 'First Name';
  $handler->display->display_options['filters']['first_value']['expose']['operator'] = 'first_value_op';
  $handler->display->display_options['filters']['first_value']['expose']['identifier'] = 'first_value';
  $handler->display->display_options['filters']['first_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Middle Name (middle) */
  $handler->display->display_options['filters']['middle_value']['id'] = 'middle_value';
  $handler->display->display_options['filters']['middle_value']['table'] = 'field_data_middle';
  $handler->display->display_options['filters']['middle_value']['field'] = 'middle_value';
  $handler->display->display_options['filters']['middle_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['middle_value']['group'] = 1;
  $handler->display->display_options['filters']['middle_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['middle_value']['expose']['operator_id'] = 'middle_value_op';
  $handler->display->display_options['filters']['middle_value']['expose']['label'] = 'Middle Name';
  $handler->display->display_options['filters']['middle_value']['expose']['operator'] = 'middle_value_op';
  $handler->display->display_options['filters']['middle_value']['expose']['identifier'] = 'middle_value';
  $handler->display->display_options['filters']['middle_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Status (field_status) */
  $handler->display->display_options['filters']['field_status_value']['id'] = 'field_status_value';
  $handler->display->display_options['filters']['field_status_value']['table'] = 'field_data_field_status';
  $handler->display->display_options['filters']['field_status_value']['field'] = 'field_status_value';
  $handler->display->display_options['filters']['field_status_value']['group'] = 1;
  $handler->display->display_options['filters']['field_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_status_value']['expose']['operator_id'] = 'field_status_value_op';
  $handler->display->display_options['filters']['field_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_status_value']['expose']['operator'] = 'field_status_value_op';
  $handler->display->display_options['filters']['field_status_value']['expose']['identifier'] = 'field_status_value';
  $handler->display->display_options['filters']['field_status_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_status_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Patron Type (patron_type) */
  $handler->display->display_options['filters']['patron_type_value']['id'] = 'patron_type_value';
  $handler->display->display_options['filters']['patron_type_value']['table'] = 'field_data_patron_type';
  $handler->display->display_options['filters']['patron_type_value']['field'] = 'patron_type_value';
  $handler->display->display_options['filters']['patron_type_value']['group'] = 1;
  $handler->display->display_options['filters']['patron_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['patron_type_value']['expose']['operator_id'] = 'patron_type_value_op';
  $handler->display->display_options['filters']['patron_type_value']['expose']['label'] = 'Patron Type';
  $handler->display->display_options['filters']['patron_type_value']['expose']['operator'] = 'patron_type_value_op';
  $handler->display->display_options['filters']['patron_type_value']['expose']['identifier'] = 'patron_type_value';
  $handler->display->display_options['filters']['patron_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: Company: Company Name */
  $handler->display->display_options['filters']['company_name']['id'] = 'company_name';
  $handler->display->display_options['filters']['company_name']['table'] = 'eck_company';
  $handler->display->display_options['filters']['company_name']['field'] = 'company_name';
  $handler->display->display_options['filters']['company_name']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['filters']['company_name']['operator'] = 'contains';
  $handler->display->display_options['filters']['company_name']['group'] = 1;
  $handler->display->display_options['filters']['company_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['company_name']['expose']['operator_id'] = 'company_name_op';
  $handler->display->display_options['filters']['company_name']['expose']['label'] = 'Company Name';
  $handler->display->display_options['filters']['company_name']['expose']['operator'] = 'company_name_op';
  $handler->display->display_options['filters']['company_name']['expose']['identifier'] = 'company_name';
  $handler->display->display_options['filters']['company_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: Field: Expiration Date (exp_date) */
  $handler->display->display_options['filters']['exp_date_value']['id'] = 'exp_date_value';
  $handler->display->display_options['filters']['exp_date_value']['table'] = 'field_data_exp_date';
  $handler->display->display_options['filters']['exp_date_value']['field'] = 'exp_date_value';
  $handler->display->display_options['filters']['exp_date_value']['group'] = 1;
  $handler->display->display_options['filters']['exp_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['exp_date_value']['expose']['operator_id'] = 'exp_date_value_op';
  $handler->display->display_options['filters']['exp_date_value']['expose']['label'] = 'Expiration Date';
  $handler->display->display_options['filters']['exp_date_value']['expose']['operator'] = 'exp_date_value_op';
  $handler->display->display_options['filters']['exp_date_value']['expose']['identifier'] = 'exp_date_value';
  $handler->display->display_options['filters']['exp_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  $handler->display->display_options['filters']['exp_date_value']['form_type'] = 'date_popup';
  /* Filter criterion: address: address (address:premise) */
  $handler->display->display_options['filters']['address_premise']['id'] = 'address_premise';
  $handler->display->display_options['filters']['address_premise']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_premise']['field'] = 'address_premise';
  $handler->display->display_options['filters']['address_premise']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_premise']['group'] = 1;
  $handler->display->display_options['filters']['address_premise']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_premise']['expose']['operator_id'] = 'address_premise_op';
  $handler->display->display_options['filters']['address_premise']['expose']['label'] = 'Address Line 1';
  $handler->display->display_options['filters']['address_premise']['expose']['operator'] = 'address_premise_op';
  $handler->display->display_options['filters']['address_premise']['expose']['identifier'] = 'address_premise';
  $handler->display->display_options['filters']['address_premise']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: address: address (address:thoroughfare) */
  $handler->display->display_options['filters']['address_thoroughfare']['id'] = 'address_thoroughfare';
  $handler->display->display_options['filters']['address_thoroughfare']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_thoroughfare']['field'] = 'address_thoroughfare';
  $handler->display->display_options['filters']['address_thoroughfare']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_thoroughfare']['group'] = 1;
  $handler->display->display_options['filters']['address_thoroughfare']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['operator_id'] = 'address_thoroughfare_op';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['label'] = 'Address Line 2';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['operator'] = 'address_thoroughfare_op';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['identifier'] = 'address_thoroughfare';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: address: address (address:locality) */
  $handler->display->display_options['filters']['address_locality']['id'] = 'address_locality';
  $handler->display->display_options['filters']['address_locality']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_locality']['field'] = 'address_locality';
  $handler->display->display_options['filters']['address_locality']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_locality']['group'] = 1;
  $handler->display->display_options['filters']['address_locality']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_locality']['expose']['operator_id'] = 'address_locality_op';
  $handler->display->display_options['filters']['address_locality']['expose']['label'] = 'City';
  $handler->display->display_options['filters']['address_locality']['expose']['operator'] = 'address_locality_op';
  $handler->display->display_options['filters']['address_locality']['expose']['identifier'] = 'address_locality';
  $handler->display->display_options['filters']['address_locality']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  $handler->display->display_options['filters']['address_locality']['group_info']['label'] = 'address (address:locality)';
  $handler->display->display_options['filters']['address_locality']['group_info']['identifier'] = 'address_locality';
  $handler->display->display_options['filters']['address_locality']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['address_locality']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: address: address (address:administrative_area) */
  $handler->display->display_options['filters']['address_administrative_area']['id'] = 'address_administrative_area';
  $handler->display->display_options['filters']['address_administrative_area']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_administrative_area']['field'] = 'address_administrative_area';
  $handler->display->display_options['filters']['address_administrative_area']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_administrative_area']['operator'] = 'contains';
  $handler->display->display_options['filters']['address_administrative_area']['group'] = 1;
  $handler->display->display_options['filters']['address_administrative_area']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_administrative_area']['expose']['operator_id'] = 'address_administrative_area_op';
  $handler->display->display_options['filters']['address_administrative_area']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['address_administrative_area']['expose']['operator'] = 'address_administrative_area_op';
  $handler->display->display_options['filters']['address_administrative_area']['expose']['identifier'] = 'address_administrative_area';
  $handler->display->display_options['filters']['address_administrative_area']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: address: address (address:postal_code) */
  $handler->display->display_options['filters']['address_postal_code']['id'] = 'address_postal_code';
  $handler->display->display_options['filters']['address_postal_code']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_postal_code']['field'] = 'address_postal_code';
  $handler->display->display_options['filters']['address_postal_code']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_postal_code']['group'] = 1;
  $handler->display->display_options['filters']['address_postal_code']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_postal_code']['expose']['operator_id'] = 'address_postal_code_op';
  $handler->display->display_options['filters']['address_postal_code']['expose']['label'] = 'Zip';
  $handler->display->display_options['filters']['address_postal_code']['expose']['operator'] = 'address_postal_code_op';
  $handler->display->display_options['filters']['address_postal_code']['expose']['identifier'] = 'address_postal_code';
  $handler->display->display_options['filters']['address_postal_code']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: suffix (suffix) */
  $handler->display->display_options['filters']['suffix_value']['id'] = 'suffix_value';
  $handler->display->display_options['filters']['suffix_value']['table'] = 'field_data_suffix';
  $handler->display->display_options['filters']['suffix_value']['field'] = 'suffix_value';
  $handler->display->display_options['filters']['suffix_value']['group'] = 1;
  $handler->display->display_options['filters']['suffix_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['suffix_value']['expose']['operator_id'] = 'suffix_value_op';
  $handler->display->display_options['filters']['suffix_value']['expose']['label'] = 'Suffix';
  $handler->display->display_options['filters']['suffix_value']['expose']['operator'] = 'suffix_value_op';
  $handler->display->display_options['filters']['suffix_value']['expose']['identifier'] = 'suffix_value';
  $handler->display->display_options['filters']['suffix_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Esquire (esquire) */
  $handler->display->display_options['filters']['esquire_value']['id'] = 'esquire_value';
  $handler->display->display_options['filters']['esquire_value']['table'] = 'field_data_esquire';
  $handler->display->display_options['filters']['esquire_value']['field'] = 'esquire_value';
  $handler->display->display_options['filters']['esquire_value']['group'] = 1;
  $handler->display->display_options['filters']['esquire_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['esquire_value']['expose']['operator_id'] = 'esquire_value_op';
  $handler->display->display_options['filters']['esquire_value']['expose']['label'] = 'Esquire';
  $handler->display->display_options['filters']['esquire_value']['expose']['operator'] = 'esquire_value_op';
  $handler->display->display_options['filters']['esquire_value']['expose']['identifier'] = 'esquire_value';
  $handler->display->display_options['filters']['esquire_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: Field: Customer Service Notes (cust_notes) */
  $handler->display->display_options['filters']['cust_notes_value']['id'] = 'cust_notes_value';
  $handler->display->display_options['filters']['cust_notes_value']['table'] = 'field_data_cust_notes';
  $handler->display->display_options['filters']['cust_notes_value']['field'] = 'cust_notes_value';
  $handler->display->display_options['filters']['cust_notes_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['cust_notes_value']['group'] = 1;
  $handler->display->display_options['filters']['cust_notes_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cust_notes_value']['expose']['operator_id'] = 'cust_notes_value_op';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['label'] = 'Customer Service Notes';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['operator'] = 'cust_notes_value_op';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['identifier'] = 'cust_notes_value';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Email (email) */
  $handler->display->display_options['filters']['email_value']['id'] = 'email_value';
  $handler->display->display_options['filters']['email_value']['table'] = 'field_data_email';
  $handler->display->display_options['filters']['email_value']['field'] = 'email_value';
  $handler->display->display_options['filters']['email_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['email_value']['group'] = 1;
  $handler->display->display_options['filters']['email_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['email_value']['expose']['operator_id'] = 'email_value_op';
  $handler->display->display_options['filters']['email_value']['expose']['label'] = 'Email';
  $handler->display->display_options['filters']['email_value']['expose']['operator'] = 'email_value_op';
  $handler->display->display_options['filters']['email_value']['expose']['identifier'] = 'email_value';
  $handler->display->display_options['filters']['email_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: cle_special (cle_special) */
  $handler->display->display_options['filters']['cle_special_value']['id'] = 'cle_special_value';
  $handler->display->display_options['filters']['cle_special_value']['table'] = 'field_data_cle_special';
  $handler->display->display_options['filters']['cle_special_value']['field'] = 'cle_special_value';
  $handler->display->display_options['filters']['cle_special_value']['group'] = 1;
  $handler->display->display_options['filters']['cle_special_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cle_special_value']['expose']['operator_id'] = 'cle_special_value_op';
  $handler->display->display_options['filters']['cle_special_value']['expose']['label'] = 'cle_special';
  $handler->display->display_options['filters']['cle_special_value']['expose']['operator'] = 'cle_special_value_op';
  $handler->display->display_options['filters']['cle_special_value']['expose']['identifier'] = 'cle_special_value';
  $handler->display->display_options['filters']['cle_special_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: Field: Suspended (suspended) */
  $handler->display->display_options['filters']['suspended_value']['id'] = 'suspended_value';
  $handler->display->display_options['filters']['suspended_value']['table'] = 'field_data_suspended';
  $handler->display->display_options['filters']['suspended_value']['field'] = 'suspended_value';
  $handler->display->display_options['filters']['suspended_value']['group'] = 1;
  $handler->display->display_options['filters']['suspended_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['suspended_value']['expose']['operator_id'] = 'suspended_value_op';
  $handler->display->display_options['filters']['suspended_value']['expose']['label'] = 'Suspended';
  $handler->display->display_options['filters']['suspended_value']['expose']['operator'] = 'suspended_value_op';
  $handler->display->display_options['filters']['suspended_value']['expose']['identifier'] = 'suspended_value';
  $handler->display->display_options['filters']['suspended_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: Membership Notes (memb_notes) */
  $handler->display->display_options['filters']['memb_notes_value']['id'] = 'memb_notes_value';
  $handler->display->display_options['filters']['memb_notes_value']['table'] = 'field_data_memb_notes';
  $handler->display->display_options['filters']['memb_notes_value']['field'] = 'memb_notes_value';
  $handler->display->display_options['filters']['memb_notes_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['memb_notes_value']['group'] = 1;
  $handler->display->display_options['filters']['memb_notes_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['memb_notes_value']['expose']['operator_id'] = 'memb_notes_value_op';
  $handler->display->display_options['filters']['memb_notes_value']['expose']['label'] = 'Membership Notes';
  $handler->display->display_options['filters']['memb_notes_value']['expose']['operator'] = 'memb_notes_value_op';
  $handler->display->display_options['filters']['memb_notes_value']['expose']['identifier'] = 'memb_notes_value';
  $handler->display->display_options['filters']['memb_notes_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );
  /* Filter criterion: person: PA Attorney ID (pa_attorney_id) */
  $handler->display->display_options['filters']['pa_attorney_id_value']['id'] = 'pa_attorney_id_value';
  $handler->display->display_options['filters']['pa_attorney_id_value']['table'] = 'field_data_pa_attorney_id';
  $handler->display->display_options['filters']['pa_attorney_id_value']['field'] = 'pa_attorney_id_value';
  $handler->display->display_options['filters']['pa_attorney_id_value']['group'] = 1;
  $handler->display->display_options['filters']['pa_attorney_id_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['pa_attorney_id_value']['expose']['operator_id'] = 'pa_attorney_id_value_op';
  $handler->display->display_options['filters']['pa_attorney_id_value']['expose']['label'] = 'PA Attorney ID';
  $handler->display->display_options['filters']['pa_attorney_id_value']['expose']['operator'] = 'pa_attorney_id_value_op';
  $handler->display->display_options['filters']['pa_attorney_id_value']['expose']['identifier'] = 'pa_attorney_id_value';
  $handler->display->display_options['filters']['pa_attorney_id_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    8 => 0,
    5 => 0,
    7 => 0,
    6 => 0,
    9 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Person */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_person';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Export to Excel',
      'settings' => array(
        'url' => 'person/search/export',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: person: Person Category */
  $handler->display->display_options['fields']['field_person_category']['id'] = 'field_person_category';
  $handler->display->display_options['fields']['field_person_category']['table'] = 'field_data_field_person_category';
  $handler->display->display_options['fields']['field_person_category']['field'] = 'field_person_category';
  $handler->display->display_options['fields']['field_person_category']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_person_category']['multi_type'] = 'ul';
  /* Field: Person: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_person';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = 'Member Number';
  $handler->display->display_options['fields']['id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['path'] = '/person/[id]';
  $handler->display->display_options['fields']['id']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['alt'] = 'Full Record for this person';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: person: Barcode */
  $handler->display->display_options['fields']['barcode_entity']['id'] = 'barcode_entity';
  $handler->display->display_options['fields']['barcode_entity']['table'] = 'field_data_barcode_entity';
  $handler->display->display_options['fields']['barcode_entity']['field'] = 'barcode_entity';
  $handler->display->display_options['fields']['barcode_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['barcode_entity']['delta_offset'] = '0';
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
  /* Field: company: Mas90 Name */
  $handler->display->display_options['fields']['mas90_name']['id'] = 'mas90_name';
  $handler->display->display_options['fields']['mas90_name']['table'] = 'field_data_mas90_name';
  $handler->display->display_options['fields']['mas90_name']['field'] = 'mas90_name';
  $handler->display->display_options['fields']['mas90_name']['relationship'] = 'field_company_target_id';
  /* Field: Company: Company Name */
  $handler->display->display_options['fields']['company_name']['id'] = 'company_name';
  $handler->display->display_options['fields']['company_name']['table'] = 'eck_company';
  $handler->display->display_options['fields']['company_name']['field'] = 'company_name';
  $handler->display->display_options['fields']['company_name']['relationship'] = 'field_company_target_id';
  /* Field: Field: Expiration Date */
  $handler->display->display_options['fields']['exp_date_1']['id'] = 'exp_date_1';
  $handler->display->display_options['fields']['exp_date_1']['table'] = 'field_data_exp_date';
  $handler->display->display_options['fields']['exp_date_1']['field'] = 'exp_date';
  $handler->display->display_options['fields']['exp_date_1']['settings'] = array(
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
  $handler->display->display_options['fields']['address']['label'] = 'Address Line 1';
  $handler->display->display_options['fields']['address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address']['alter']['text'] = '[address-thoroughfare]';
  $handler->display->display_options['fields']['address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_1']['id'] = 'address_1';
  $handler->display->display_options['fields']['address_1']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_1']['field'] = 'address';
  $handler->display->display_options['fields']['address_1']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_1']['label'] = 'Address Line 2';
  $handler->display->display_options['fields']['address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_1']['alter']['text'] = '[address_1-premise]';
  $handler->display->display_options['fields']['address_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_2']['id'] = 'address_2';
  $handler->display->display_options['fields']['address_2']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_2']['field'] = 'address';
  $handler->display->display_options['fields']['address_2']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_2']['label'] = 'City';
  $handler->display->display_options['fields']['address_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_2']['alter']['text'] = '[address_2-locality]';
  $handler->display->display_options['fields']['address_2']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_2']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_3']['id'] = 'address_3';
  $handler->display->display_options['fields']['address_3']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_3']['field'] = 'address';
  $handler->display->display_options['fields']['address_3']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_3']['label'] = 'State';
  $handler->display->display_options['fields']['address_3']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_3']['alter']['text'] = '[address_3-administrative_area]';
  $handler->display->display_options['fields']['address_3']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_3']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: address: address */
  $handler->display->display_options['fields']['address_4']['id'] = 'address_4';
  $handler->display->display_options['fields']['address_4']['table'] = 'field_data_address';
  $handler->display->display_options['fields']['address_4']['field'] = 'address';
  $handler->display->display_options['fields']['address_4']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['fields']['address_4']['label'] = 'Zip';
  $handler->display->display_options['fields']['address_4']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['address_4']['alter']['text'] = '[address_4-postal_code]';
  $handler->display->display_options['fields']['address_4']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['address_4']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: person: suffix */
  $handler->display->display_options['fields']['suffix']['id'] = 'suffix';
  $handler->display->display_options['fields']['suffix']['table'] = 'field_data_suffix';
  $handler->display->display_options['fields']['suffix']['field'] = 'suffix';
  $handler->display->display_options['fields']['suffix']['label'] = 'Suffix';
  /* Field: person: Esquire */
  $handler->display->display_options['fields']['esquire']['id'] = 'esquire';
  $handler->display->display_options['fields']['esquire']['table'] = 'field_data_esquire';
  $handler->display->display_options['fields']['esquire']['field'] = 'esquire';
  /* Field: person: Phone Number */
  $handler->display->display_options['fields']['phone_number_entity']['id'] = 'phone_number_entity';
  $handler->display->display_options['fields']['phone_number_entity']['table'] = 'field_data_phone_number_entity';
  $handler->display->display_options['fields']['phone_number_entity']['field'] = 'phone_number_entity';
  $handler->display->display_options['fields']['phone_number_entity']['label'] = 'Phone';
  $handler->display->display_options['fields']['phone_number_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['phone_number_entity']['delta_offset'] = '0';
  $handler->display->display_options['fields']['phone_number_entity']['multi_type'] = 'ul';
  /* Field: company: Phone Number */
  $handler->display->display_options['fields']['phone_entity']['id'] = 'phone_entity';
  $handler->display->display_options['fields']['phone_entity']['table'] = 'field_data_phone_entity';
  $handler->display->display_options['fields']['phone_entity']['field'] = 'phone_entity';
  $handler->display->display_options['fields']['phone_entity']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['fields']['phone_entity']['label'] = 'Company Phone';
  $handler->display->display_options['fields']['phone_entity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['phone_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['phone_entity']['delta_offset'] = '0';
  /* Field: person: Email */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'field_data_email';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  /* Field: person: cle_special */
  $handler->display->display_options['fields']['cle_special']['id'] = 'cle_special';
  $handler->display->display_options['fields']['cle_special']['table'] = 'field_data_cle_special';
  $handler->display->display_options['fields']['cle_special']['field'] = 'cle_special';
  $handler->display->display_options['fields']['cle_special']['label'] = 'CLE Special';
  /* Field: Field: Suspended */
  $handler->display->display_options['fields']['suspended']['id'] = 'suspended';
  $handler->display->display_options['fields']['suspended']['table'] = 'field_data_suspended';
  $handler->display->display_options['fields']['suspended']['field'] = 'suspended';
  $handler->display->display_options['fields']['suspended']['relationship'] = 'field_company_target_id';
  $handler->display->display_options['fields']['suspended']['exclude'] = TRUE;
  /* Field: Field: Suspended */
  $handler->display->display_options['fields']['suspended_1']['id'] = 'suspended_1';
  $handler->display->display_options['fields']['suspended_1']['table'] = 'field_data_suspended';
  $handler->display->display_options['fields']['suspended_1']['field'] = 'suspended';
  $handler->display->display_options['fields']['suspended_1']['exclude'] = TRUE;
  $handler->display->display_options['path'] = 'person/search';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Search';
  $handler->display->display_options['menu']['description'] = 'Person Search';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Search';
  $handler->display->display_options['tab_options']['description'] = 'Person Search';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Export Person Search Results */
  $handler = $view->new_display('views_data_export', 'Export Person Search Results', 'views_data_export_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Person Search Export';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'persons.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Person: Id */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eck_person';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['path'] = 'person/search/export';
  $handler->display->display_options['displays'] = array(
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['sitename_title'] = 0;
  $export['person_search'] = $view;

  return $export;
}
