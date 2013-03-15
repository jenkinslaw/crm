<?php

namespace Cdb;

/**
 * The Cdb\Entity class is a wrapper for the entity wrapper found in entity_api.
 *
 * This wrapper is a lot more intuitive than that one.
 * For instance, given a known field_name we can set and retrive values:
 *
 *     $entity->name = 'value';
 *     $name_value = $entity->name;
 *
 * But if we prefer we can still do:
 *
 *     $entiy->name()->set('value');
 *
 *     $entity->name()->value();
 *
 *
 * This is a marked improvement over the wrapper that comes with entity_api:
 *
 *     $entity->field_name->set('value');
 *     $name_value = $entity->field_name->value();
 */
class Entity {

  private $entity;
  protected $type;

  function __construct($id = NULL) {
    $this->entity = $this->getWrapper($id);
  }

  function __call($name, $arguments) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name;
  }

  // We can handle handle some crud via magic methods.
  public function __get($name) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->value();
  }

  private function formatFieldName($name) {
    if (isset($this->entity->{"field_$name"})) {
      return "field_$name";
    }
    return $name;
  }

  public function __set($name, $value) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->set($value);
  }

  public function value() {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->value();
  }

  public function save() {
    $this->entity->save();
  }

  public function delete() {
    $this->entity->delete();
  }

  public function fieldInfo($name) {
    $name = $this->formatFieldName($name);
    return $this->entity->$name->info();
  }

  public function getWrapper($id = NULL) {
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

/**
 * A Class to hold the business specif logic for our Company entity.
 */
class Company extends Entity{

  function __construct($id = NULL) {
    $this->type = 'company';
    parent::__construct($id);
  }

}
