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

  return $export;
}
