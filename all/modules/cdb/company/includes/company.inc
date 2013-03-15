<?php
/**
 * A Class to hold the business specif logic for our Company entity.
 */

namespace Cdb;

class Company {

  private $company;

  function __construct($id = NULL) {
    $this->company = $this->getCompanyWrapper($id);
  }

  // We can handle handle some crud via magic methods.
  public function __get($name) {
    if (isset($this->company->{"field_$name"})) {
      return $this->company->{"field_$name"}->value();
    }
    return $this->company->$name->value();
  }

  public function __set($name, $value) {
    return $this->company->{"field_$name"}->set($value);
  }

  public function save() {
    $this->company->save();
  }

  public function delete() {
    $this->company->delete();
  }


  private function getCompanyWrapper($id = NULL) {
    if (is_numeric($id)) {
      $company = entity_load_single('company', $id);
    }
    else {
      $company = entity_create('company', array('type' => 'company'));
    }
    $wrapper = entity_metadata_wrapper('company', $company);
    return $wrapper;
  }

  public function fieldInfo($name) {
    $info = $this->company->{"field_$name"}->info();
    return $info;
  }


}
