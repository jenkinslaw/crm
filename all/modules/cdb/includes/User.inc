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
  protected $previousUser;

  /**
   * User Contructor.
   */
  public function __construct() {
    global $user;
    $this->user =& $user;
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
    $has_role = (in_array($role, $this->user->roles));
    return $has_role;
  }

  /**
   * Login as user with specified role.
   */
  public function loginAs($role = 'Administrator') {
    $role_user = $this->getUserFromRole($role);
    if ($role_user) {
      // TODO: throw exception if previousUser is present.
      $this->previousUser = $this->user;
      $this->user = $role_user;
    }
  }

  /**
   * Given a role returns a user object.
   */
  protected function getUserFromRole($role) {
    $name = $this->roleToName($role);
    $query = db_query("select uid from users where name = '$name' limit 1;");
    $uid   = $query->fetchField();
    if ($uid) {
      return user_load($uid);
    }
    return $this->user;
  }


  /**
   * Given a string returns user name formated string.
   */
  public function roleToName($role = '') {
    $name = strtolower($role);
    $name = trim($name);
    $name = preg_replace("/[^a-z0-9_\s-]/", "", $name);
    $name = preg_replace("/[\s-]+/", " ", $name);
    $name = preg_replace("/[\s_]/", "-", $name);

    return $name;
  }

  /**
   * If a previous user is availabe, resets the global user to that.
   */
  public function reset() {
    if (!empty($this->previousUser)) {
      $this->user = $this->previousUser;
    }
    unset($this->previousUser);
  }
}
