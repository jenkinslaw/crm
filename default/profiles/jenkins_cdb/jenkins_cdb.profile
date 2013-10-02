<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function jenkins_cdb_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#value'] = "Jenkins Law Library Customer Database";
}
