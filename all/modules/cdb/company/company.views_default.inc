<?php
/**
 * @file
 * company.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function company_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'company_people';
  $view->description = 'A list of the names of people associated to a specific Company.';
  $view->tag = 'default';
  $view->base_table = 'eck_person';
  $view->human_name = 'Company People';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Person: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_person';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  /* Field: person: First Name */
  $handler->display->display_options['fields']['first']['id'] = 'first';
  $handler->display->display_options['fields']['first']['table'] = 'field_data_first';
  $handler->display->display_options['fields']['first']['field'] = 'first';
  $handler->display->display_options['fields']['first']['label'] = '';
  $handler->display->display_options['fields']['first']['element_label_colon'] = FALSE;
  /* Field: person: Middle Name */
  $handler->display->display_options['fields']['middle']['id'] = 'middle';
  $handler->display->display_options['fields']['middle']['table'] = 'field_data_middle';
  $handler->display->display_options['fields']['middle']['field'] = 'middle';
  $handler->display->display_options['fields']['middle']['label'] = '';
  $handler->display->display_options['fields']['middle']['element_label_colon'] = FALSE;
  /* Field: person: Last Name */
  $handler->display->display_options['fields']['last']['id'] = 'last';
  $handler->display->display_options['fields']['last']['table'] = 'field_data_last';
  $handler->display->display_options['fields']['last']['field'] = 'last';
  $handler->display->display_options['fields']['last']['label'] = '';
  $handler->display->display_options['fields']['last']['element_label_colon'] = FALSE;
  /* Contextual filter: person: Company (field_company) */
  $handler->display->display_options['arguments']['field_company_target_id']['id'] = 'field_company_target_id';
  $handler->display->display_options['arguments']['field_company_target_id']['table'] = 'field_data_field_company';
  $handler->display->display_options['arguments']['field_company_target_id']['field'] = 'field_company_target_id';
  $handler->display->display_options['arguments']['field_company_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_company_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_company_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_company_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_company_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Person: person type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_person';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'person' => 'person',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_company_persons');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'first' => 'first',
    'middle' => 'middle',
    'last' => 'last',
    'id' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['company_people'] = $view;

  $view = new view();
  $view->name = 'company_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_company';
  $view->human_name = 'Company Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Company Search';
  $handler->display->display_options['hide_attachment_summary'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'id' => 'id',
    'account_number' => 'account_number',
    'company_name' => 'company_name',
    'phone_entity' => 'phone_entity',
    'number_of_attorneys' => 'number_of_attorneys',
    'exp_date' => 'exp_date',
    'company_category' => 'company_category',
    'billing_area' => 'billing_area',
    'address_entity' => 'address_entity',
  );
  $handler->display->display_options['style_options']['default'] = 'company_name';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'account_number' => array(
      'sortable' => 1,
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
    'phone_entity' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'number_of_attorneys' => array(
      'sortable' => 0,
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
    'company_category' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'billing_area' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'address_entity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['phone_entity_target_id']['id'] = 'phone_entity_target_id';
  $handler->display->display_options['relationships']['phone_entity_target_id']['table'] = 'field_data_phone_entity';
  $handler->display->display_options['relationships']['phone_entity_target_id']['field'] = 'phone_entity_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['address_entity_target_id']['id'] = 'address_entity_target_id';
  $handler->display->display_options['relationships']['address_entity_target_id']['table'] = 'field_data_address_entity';
  $handler->display->display_options['relationships']['address_entity_target_id']['field'] = 'address_entity_target_id';
  /* Field: Bulk operations: Company */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_company';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  /* Field: Company: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_company';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['path'] = 'company/company/[id]';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Company: Account Number */
  $handler->display->display_options['fields']['account_number']['id'] = 'account_number';
  $handler->display->display_options['fields']['account_number']['table'] = 'eck_company';
  $handler->display->display_options['fields']['account_number']['field'] = 'account_number';
  $handler->display->display_options['fields']['account_number']['label'] = 'Account No.';
  $handler->display->display_options['fields']['account_number']['element_label_colon'] = FALSE;
  /* Field: Company: Company Name */
  $handler->display->display_options['fields']['company_name']['id'] = 'company_name';
  $handler->display->display_options['fields']['company_name']['table'] = 'eck_company';
  $handler->display->display_options['fields']['company_name']['field'] = 'company_name';
  $handler->display->display_options['fields']['company_name']['element_label_colon'] = FALSE;
  /* Field: company: Phone Number */
  $handler->display->display_options['fields']['phone_entity']['id'] = 'phone_entity';
  $handler->display->display_options['fields']['phone_entity']['table'] = 'field_data_phone_entity';
  $handler->display->display_options['fields']['phone_entity']['field'] = 'phone_entity';
  $handler->display->display_options['fields']['phone_entity']['label'] = 'Phone';
  $handler->display->display_options['fields']['phone_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['phone_entity']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['phone_entity']['delta_offset'] = '0';
  /* Field: Company: Number of Attorneys */
  $handler->display->display_options['fields']['number_of_attorneys']['id'] = 'number_of_attorneys';
  $handler->display->display_options['fields']['number_of_attorneys']['table'] = 'eck_company';
  $handler->display->display_options['fields']['number_of_attorneys']['field'] = 'number_of_attorneys';
  $handler->display->display_options['fields']['number_of_attorneys']['label'] = '# Attys';
  $handler->display->display_options['fields']['number_of_attorneys']['element_label_colon'] = FALSE;
  /* Field: Field: Expiration Date */
  $handler->display->display_options['fields']['exp_date']['id'] = 'exp_date';
  $handler->display->display_options['fields']['exp_date']['table'] = 'field_data_exp_date';
  $handler->display->display_options['fields']['exp_date']['field'] = 'exp_date';
  $handler->display->display_options['fields']['exp_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['exp_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: company: Company Category */
  $handler->display->display_options['fields']['company_category']['id'] = 'company_category';
  $handler->display->display_options['fields']['company_category']['table'] = 'field_data_company_category';
  $handler->display->display_options['fields']['company_category']['field'] = 'company_category';
  $handler->display->display_options['fields']['company_category']['label'] = 'Category';
  $handler->display->display_options['fields']['company_category']['element_label_colon'] = FALSE;
  /* Field: company: Billing Area */
  $handler->display->display_options['fields']['billing_area']['id'] = 'billing_area';
  $handler->display->display_options['fields']['billing_area']['table'] = 'field_data_billing_area';
  $handler->display->display_options['fields']['billing_area']['field'] = 'billing_area';
  $handler->display->display_options['fields']['billing_area']['label'] = 'Area';
  $handler->display->display_options['fields']['billing_area']['element_label_colon'] = FALSE;
  /* Field: Field: Address */
  $handler->display->display_options['fields']['address_entity']['id'] = 'address_entity';
  $handler->display->display_options['fields']['address_entity']['table'] = 'field_data_address_entity';
  $handler->display->display_options['fields']['address_entity']['field'] = 'address_entity';
  $handler->display->display_options['fields']['address_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['address_entity']['settings'] = array(
    'link' => 0,
  );
  /* Filter criterion: Company: company type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_company';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'company' => 'company',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Company: Account Number */
  $handler->display->display_options['filters']['account_number']['id'] = 'account_number';
  $handler->display->display_options['filters']['account_number']['table'] = 'eck_company';
  $handler->display->display_options['filters']['account_number']['field'] = 'account_number';
  $handler->display->display_options['filters']['account_number']['operator'] = 'contains';
  $handler->display->display_options['filters']['account_number']['group'] = 1;
  $handler->display->display_options['filters']['account_number']['exposed'] = TRUE;
  $handler->display->display_options['filters']['account_number']['expose']['operator_id'] = 'account_number_op';
  $handler->display->display_options['filters']['account_number']['expose']['label'] = 'Account Number';
  $handler->display->display_options['filters']['account_number']['expose']['operator'] = 'account_number_op';
  $handler->display->display_options['filters']['account_number']['expose']['identifier'] = 'account_number';
  $handler->display->display_options['filters']['account_number']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: company: Billing Area (billing_area) */
  $handler->display->display_options['filters']['billing_area_value']['id'] = 'billing_area_value';
  $handler->display->display_options['filters']['billing_area_value']['table'] = 'field_data_billing_area';
  $handler->display->display_options['filters']['billing_area_value']['field'] = 'billing_area_value';
  $handler->display->display_options['filters']['billing_area_value']['group'] = 1;
  $handler->display->display_options['filters']['billing_area_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['billing_area_value']['expose']['operator_id'] = 'billing_area_value_op';
  $handler->display->display_options['filters']['billing_area_value']['expose']['label'] = 'Billing Area (billing_area)';
  $handler->display->display_options['filters']['billing_area_value']['expose']['operator'] = 'billing_area_value_op';
  $handler->display->display_options['filters']['billing_area_value']['expose']['identifier'] = 'billing_area_value';
  $handler->display->display_options['filters']['billing_area_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: company: Company Category (company_category) */
  $handler->display->display_options['filters']['company_category_value']['id'] = 'company_category_value';
  $handler->display->display_options['filters']['company_category_value']['table'] = 'field_data_company_category';
  $handler->display->display_options['filters']['company_category_value']['field'] = 'company_category_value';
  $handler->display->display_options['filters']['company_category_value']['group'] = 1;
  $handler->display->display_options['filters']['company_category_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['company_category_value']['expose']['operator_id'] = 'company_category_value_op';
  $handler->display->display_options['filters']['company_category_value']['expose']['label'] = 'Company Category (company_category)';
  $handler->display->display_options['filters']['company_category_value']['expose']['operator'] = 'company_category_value_op';
  $handler->display->display_options['filters']['company_category_value']['expose']['identifier'] = 'company_category_value';
  $handler->display->display_options['filters']['company_category_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['company_category_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Company: Company Name */
  $handler->display->display_options['filters']['company_name']['id'] = 'company_name';
  $handler->display->display_options['filters']['company_name']['table'] = 'eck_company';
  $handler->display->display_options['filters']['company_name']['field'] = 'company_name';
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
    5 => 0,
  );
  /* Filter criterion: Company: Id */
  $handler->display->display_options['filters']['id']['id'] = 'id';
  $handler->display->display_options['filters']['id']['table'] = 'eck_company';
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
    5 => 0,
  );
  /* Filter criterion: company: Membership Notes (member_notes) */
  $handler->display->display_options['filters']['member_notes_value']['id'] = 'member_notes_value';
  $handler->display->display_options['filters']['member_notes_value']['table'] = 'field_data_member_notes';
  $handler->display->display_options['filters']['member_notes_value']['field'] = 'member_notes_value';
  $handler->display->display_options['filters']['member_notes_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['member_notes_value']['group'] = 1;
  $handler->display->display_options['filters']['member_notes_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['member_notes_value']['expose']['operator_id'] = 'member_notes_value_op';
  $handler->display->display_options['filters']['member_notes_value']['expose']['label'] = 'Membership Notes (member_notes)';
  $handler->display->display_options['filters']['member_notes_value']['expose']['operator'] = 'member_notes_value_op';
  $handler->display->display_options['filters']['member_notes_value']['expose']['identifier'] = 'member_notes_value';
  $handler->display->display_options['filters']['member_notes_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Phone number: Number */
  $handler->display->display_options['filters']['number']['id'] = 'number';
  $handler->display->display_options['filters']['number']['table'] = 'eck_phone_number';
  $handler->display->display_options['filters']['number']['field'] = 'number';
  $handler->display->display_options['filters']['number']['relationship'] = 'phone_entity_target_id';
  $handler->display->display_options['filters']['number']['operator'] = 'contains';
  $handler->display->display_options['filters']['number']['group'] = 1;
  $handler->display->display_options['filters']['number']['exposed'] = TRUE;
  $handler->display->display_options['filters']['number']['expose']['operator_id'] = 'number_op';
  $handler->display->display_options['filters']['number']['expose']['label'] = 'Number';
  $handler->display->display_options['filters']['number']['expose']['operator'] = 'number_op';
  $handler->display->display_options['filters']['number']['expose']['identifier'] = 'number';
  $handler->display->display_options['filters']['number']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: company: Website (website) */
  $handler->display->display_options['filters']['website_value']['id'] = 'website_value';
  $handler->display->display_options['filters']['website_value']['table'] = 'field_data_website';
  $handler->display->display_options['filters']['website_value']['field'] = 'website_value';
  $handler->display->display_options['filters']['website_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['website_value']['group'] = 1;
  $handler->display->display_options['filters']['website_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['website_value']['expose']['operator_id'] = 'website_value_op';
  $handler->display->display_options['filters']['website_value']['expose']['label'] = 'Website (website)';
  $handler->display->display_options['filters']['website_value']['expose']['operator'] = 'website_value_op';
  $handler->display->display_options['filters']['website_value']['expose']['identifier'] = 'website_value';
  $handler->display->display_options['filters']['website_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Field: Address (address_entity) */
  $handler->display->display_options['filters']['address_entity_target_id']['id'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_entity_target_id']['table'] = 'field_data_address_entity';
  $handler->display->display_options['filters']['address_entity_target_id']['field'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_entity_target_id']['group'] = 1;
  $handler->display->display_options['filters']['address_entity_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_entity_target_id']['expose']['operator_id'] = 'address_entity_target_id_op';
  $handler->display->display_options['filters']['address_entity_target_id']['expose']['label'] = 'Address (address_entity)';
  $handler->display->display_options['filters']['address_entity_target_id']['expose']['operator'] = 'address_entity_target_id_op';
  $handler->display->display_options['filters']['address_entity_target_id']['expose']['identifier'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_entity_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Field: Customer Service Notes (cust_notes) */
  $handler->display->display_options['filters']['cust_notes_value']['id'] = 'cust_notes_value';
  $handler->display->display_options['filters']['cust_notes_value']['table'] = 'field_data_cust_notes';
  $handler->display->display_options['filters']['cust_notes_value']['field'] = 'cust_notes_value';
  $handler->display->display_options['filters']['cust_notes_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['cust_notes_value']['group'] = 1;
  $handler->display->display_options['filters']['cust_notes_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cust_notes_value']['expose']['operator_id'] = 'cust_notes_value_op';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['label'] = 'Customer Service Notes (cust_notes)';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['operator'] = 'cust_notes_value_op';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['identifier'] = 'cust_notes_value';
  $handler->display->display_options['filters']['cust_notes_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Field: Expiration Date (exp_date) */
  $handler->display->display_options['filters']['exp_date_value']['id'] = 'exp_date_value';
  $handler->display->display_options['filters']['exp_date_value']['table'] = 'field_data_exp_date';
  $handler->display->display_options['filters']['exp_date_value']['field'] = 'exp_date_value';
  $handler->display->display_options['filters']['exp_date_value']['group'] = 1;
  $handler->display->display_options['filters']['exp_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['exp_date_value']['expose']['operator_id'] = 'exp_date_value_op';
  $handler->display->display_options['filters']['exp_date_value']['expose']['label'] = 'Expiration Date (exp_date)';
  $handler->display->display_options['filters']['exp_date_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['exp_date_value']['expose']['operator'] = 'exp_date_value_op';
  $handler->display->display_options['filters']['exp_date_value']['expose']['identifier'] = 'exp_date_value';
  $handler->display->display_options['filters']['exp_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['exp_date_value']['form_type'] = 'date_popup';
  /* Filter criterion: Field: Suspended (suspended) */
  $handler->display->display_options['filters']['suspended_value']['id'] = 'suspended_value';
  $handler->display->display_options['filters']['suspended_value']['table'] = 'field_data_suspended';
  $handler->display->display_options['filters']['suspended_value']['field'] = 'suspended_value';
  $handler->display->display_options['filters']['suspended_value']['group'] = 1;
  $handler->display->display_options['filters']['suspended_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['suspended_value']['expose']['operator_id'] = 'suspended_value_op';
  $handler->display->display_options['filters']['suspended_value']['expose']['label'] = 'Suspended (suspended)';
  $handler->display->display_options['filters']['suspended_value']['expose']['operator'] = 'suspended_value_op';
  $handler->display->display_options['filters']['suspended_value']['expose']['identifier'] = 'suspended_value';
  $handler->display->display_options['filters']['suspended_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: address: address (address:postal_code) */
  $handler->display->display_options['filters']['address_postal_code']['id'] = 'address_postal_code';
  $handler->display->display_options['filters']['address_postal_code']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_postal_code']['field'] = 'address_postal_code';
  $handler->display->display_options['filters']['address_postal_code']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_postal_code']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_postal_code']['expose']['operator_id'] = 'address_postal_code_op';
  $handler->display->display_options['filters']['address_postal_code']['expose']['label'] = 'Postal Code';
  $handler->display->display_options['filters']['address_postal_code']['expose']['operator'] = 'address_postal_code_op';
  $handler->display->display_options['filters']['address_postal_code']['expose']['identifier'] = 'address_postal_code';
  $handler->display->display_options['filters']['address_postal_code']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: address: address (address:thoroughfare) */
  $handler->display->display_options['filters']['address_thoroughfare']['id'] = 'address_thoroughfare';
  $handler->display->display_options['filters']['address_thoroughfare']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_thoroughfare']['field'] = 'address_thoroughfare';
  $handler->display->display_options['filters']['address_thoroughfare']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_thoroughfare']['operator'] = 'contains';
  $handler->display->display_options['filters']['address_thoroughfare']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['operator_id'] = 'address_thoroughfare_op';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['label'] = 'Address Line 1';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['operator'] = 'address_thoroughfare_op';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['identifier'] = 'address_thoroughfare';
  $handler->display->display_options['filters']['address_thoroughfare']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: address: address (address:premise) */
  $handler->display->display_options['filters']['address_premise']['id'] = 'address_premise';
  $handler->display->display_options['filters']['address_premise']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_premise']['field'] = 'address_premise';
  $handler->display->display_options['filters']['address_premise']['relationship'] = 'address_entity_target_id';
  $handler->display->display_options['filters']['address_premise']['operator'] = 'contains';
  $handler->display->display_options['filters']['address_premise']['exposed'] = TRUE;
  $handler->display->display_options['filters']['address_premise']['expose']['operator_id'] = 'address_premise_op';
  $handler->display->display_options['filters']['address_premise']['expose']['label'] = 'Address Line 2';
  $handler->display->display_options['filters']['address_premise']['expose']['operator'] = 'address_premise_op';
  $handler->display->display_options['filters']['address_premise']['expose']['identifier'] = 'address_premise';
  $handler->display->display_options['filters']['address_premise']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: address: address (address:locality) */
  $handler->display->display_options['filters']['address_locality']['id'] = 'address_locality';
  $handler->display->display_options['filters']['address_locality']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_locality']['field'] = 'address_locality';
  $handler->display->display_options['filters']['address_locality']['relationship'] = 'address_entity_target_id';
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
    5 => 0,
  );
  /* Filter criterion: address: address (address:administrative_area) */
  $handler->display->display_options['filters']['address_administrative_area']['id'] = 'address_administrative_area';
  $handler->display->display_options['filters']['address_administrative_area']['table'] = 'field_data_address';
  $handler->display->display_options['filters']['address_administrative_area']['field'] = 'address_administrative_area';
  $handler->display->display_options['filters']['address_administrative_area']['relationship'] = 'address_entity_target_id';
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
    5 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'company-search';
  $export['company_search'] = $view;

  return $export;
}
