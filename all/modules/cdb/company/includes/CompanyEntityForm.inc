<?php
/**
 * @file
 * CompanyEntityForm.inc
 *
 * Extends the EntityForm class to define methods specific to the CompanyEnitty
 * Form.
 */

class CompanyEntityForm extends EntityForm {

  /**
   * Checks to see if this is ic a Company form.
   */
  protected function isCompanyForm() {
    return ($this->type == 'company_entity_form');
  }
}
