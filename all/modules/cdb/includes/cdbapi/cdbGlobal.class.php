<?php
/**
 * Project: Jenkins Law Customer DB
 * File: cdbGlobal.class.php
 *
 * Requires ADODB Package.
 *
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.0.20090814
 */

// ADODB needs to be in a global include path!
require_once('adodb5/adodb.inc.php');

/**
 * CDB Global Configuration Class
 *
 * This is a singleton-style class that provides a single
 * database connection to the CustomerDB. It also provides
 * methods to deal with users. It is used automatically
 * within subsequent classes and requires no action from
 * the class user.
 *
 * @package JenkinsCustomerDB
*/
class cdb
{

	/*
	 *  MODIFY THE BELOW CONSTANTS FOR APPROPRIATE DB
	 */
	const DB_SERVER 	= $_ENV['_CDB_DB_SERVER'];
	const DB_USER 		= $_ENV['_CDB_DB_USER'];
	const DB_PASSWORD	= $_ENV['_CDB_DB_PASSWORD'];
	const DB_TYPE		= $_ENV['_CDB_TYPE'];
	const DB_DEBUG		= (bool) $_ENV['_CDB_DEBUG'];

	/*
	 *  DO NOT CHANGE ANYTHING BELOW THIS!!!!
	 */

	protected $db;
	protected $user = 'www'; // Default user is 'www'

	private static $cdb_instance;

	private function __construct()
	{
		$this->db = ADONewConnection(self::DB_TYPE);
		$this->db->debug = self::DB_DEBUG;
		// Use $this->db->PConnect() ????
		$this->db->Connect(self::DB_SERVER, self::DB_USER, self::DB_PASSWORD);
	}

	/**
	 * Get the single instance of the cdbGlobal Class
	 * @return class
	 */
	public static function getCDB()
	{
	    if (!self::$cdb_instance)
	    {
	        self::$cdb_instance = new cdb();
	    }

	    return self::$cdb_instance;
	}

	/**
	 * Get the database connection class
	 * @return class
	 */
	public function getDB() { return $this->db;	}

	/**
	 * Returns current user for use in the event log
	 * @return string
	 */
	public function getUser() { return $this->user; }

	/**
	 * Sets the current user for use in the event log.
	 * @param string $user_name A valid user in the USERS table.
	 * @return bool
	 */
	public function setUser($user_name)
	{
		if(strlen($user_name) <= 12)
		{
			$query = $this->db->Prepare("SELECT USER_ID
									FROM USERS
									WHERE USER_ID=:u
									AND ACTIVE = 1");
			$rs = $this->db->Execute($query, array('u' => "$user_name"));
			$row = $rs->FetchRow();

			if($rs->RecordCount() == 1)
			{
				$this->user = trim($row['USER_ID']); // Maybe I should use the username from the sql?
				return true;
			}
			else
			{
				//$this->setError('setCurrentUser', '1', 'Username Invalid');
				return false;
			}
		}
		else
		{
			//$this->setError('setCurrentUser', '2', 'Username Too Long.');
			return false;
		}

	}

	/**
	 * Checks for a valid username/password combo
	 * @param string $user_name Username
	 * @param string $password Password
	 * @return bool
	 */
	static function authenticateUser($user_name, $password)
	{
			$query = $this->db->Prepare("SELECT USER_ID
									FROM USERS
									WHERE USER_ID=:u
									AND PASSWORD=:p
									AND ACTIVE = 1");
			$rs = $this->db->Execute($query, array('u' => $user_name, 'p' => $password));
			if($rs->RecordCount() == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
	}

}
