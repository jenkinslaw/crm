<?php
/**
 * A Class to hold the business specif logic for our Company entity.
 */

namespace Cdb;

class Entity {

  private $entity;
  protected $type;

  function __construct($id = NULL) {
    $this->entity = $this->getWrapper($id);
  }

  // We can handle handle some crud via magic methods.
  public function __get($name) {
    if (isset($this->entity->{"field_$name"})) {
      return $this->entity->{"field_$name"}->value();
    }
    return $this->entity->$name->value();
  }

  public function __set($name, $value) {
    return $this->entity->{"field_$name"}->set($value);
  }

  public function save() {
    $this->entity->save();
  }

  public function delete() {
    $this->entity->delete();
  }

  public function fieldInfo($name) {
    $info = $this->entity->{"field_$name"}->info();
    return $info;
  }

  private function getWrapper($id = NULL) {
    $entity_type = $this->type;
    $bundle_type = $entity_type;

    if (is_numeric($id)) {
      $entity= entity_load_single($entity_type, $id);
    }
    else {
      $entity = entity_create($entity_type, array('type' => $bundle_type));
    }
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    return $wrapper;
  }

}

class Company extends Entity{

  function __construct($id = NULL) {
    $this->type = 'company';
    parent::__construct($id);
  }

}
