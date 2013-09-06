<?php
/**
 * @file
 * Definition of the company plugin.
 */

$plugin = array(
  'handler' => 'PanelizerEntityCompany',
  'entity path' => 'company/company/%company',
  'uses page manager' => TRUE,
  'hooks' => array(
    'menu' => TRUE,
    'admin_paths' => TRUE,
    'permission' => FALSE,
    'panelizer_defaults' => TRUE,
    'default_page_manager_handlers' => TRUE,
    'form_alter' => TRUE,
    'page_alter' => TRUE,
    'views_data_alter' => TRUE,
    'views_plugins_alter' => TRUE,
  ),
);
