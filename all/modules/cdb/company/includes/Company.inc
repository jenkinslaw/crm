<?php
/**
 * A Class to hold the business specif logic for our Company entity.
 */
class Company extends CdbEntity{

  function __construct($id = NULL) {
    $this->type = 'company';
    parent::__construct($id);
  }

}
