<?php
/**
 * @file
 * The User class is a wrapper for drupals global $user.
 *
 * By wrapping the global $user inside a class we can bundle
 * user level functionality here in order to write cleaner and 
 * more maintable code.
 */

class User {

  protected $user;

  /**
   * User Contructor.
   */
  public function __construct($id = NULL) {
    global $user;
    $this->user = $user;
  }

  /**
   * Returns the globa User object.
   */
  public function getSelf() {
    return $this->user;
  }

  /**
   * Checks that the user has a specific role.
   */
  public function hasRole($role) {
    if (isset($this->user)) {
      $user = $this->user;
    }
    else {
      global $user;
    }
    return (in_array($role, $user->roles));
  }

}
