<?php
require_once('cdb.class.php');
/**
 * Project: Jenkins Law Customer DB
 * File: cdbPhone.class.php
 *
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.1.20100322
 */


/**
 * CDB Phone Object
 *
 * Provides methods to access and modify the PHONE
 * table and related data.
 *
 * @package JenkinsCustomerDB
 */
class cdbPhone extends customerDB
{
	protected $new 				= FALSE;
	protected $phone_id;
	protected $phone_type		= NULL;
	protected $mdesc;
	protected $ldesc;
	protected $phone_nbr		= NULL;
	protected $hours			= NULL;
	protected $last_update;
	protected $update_by;
	protected $parent;
	protected $parent_id;

	const MASTER_QUERY = "SELECT *
						FROM PHONE
						LEFT OUTER JOIN PHONE_TYPE
						ON PHONE.PHONE_TYPE = PHONE_TYPE.PHONE_TYPE";

	/**
	 * Construct!
	 * @param int $phone_id Phone_ID as found in the PHONE table
	 * @param string $parent Parent, ie: 'company', 'contact' or 'customer'
	 * @param int $parent_id ID of Parent
	 */
	function __construct($phone_id = NULL, $parent, $parent_id)
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$this->currentUser = self::$cdb->getUser();
		if($phone_id != NULL)
		{
			$this->setPhone($phone_id);
			$this->new = FALSE;
		}
		else
		{
			$this->phone_id = self::$db->GenID('PHONE_ID_SEQ');
			$this->new = TRUE;
		}
		$this->parent = $parent;
		$this->parent_id = $parent_id;
	}

	/**
	 * Populates phone object
	 * @param int $pid Phone_ID as found in the PHONE table
	 * @return bool
	 */
	protected function setPhone($pid)
	{
		$query = self::$db->Prepare(self::MASTER_QUERY . " WHERE trim(PHONE_ID)=:pid");
		$rs = self::$db->Execute($query, array('pid' => "$pid"));

		if($rs->RecordCount() == 1)
		{
			$phone_data = $rs->getRows();
			$phone_data = array_shift($phone_data);

			$this->phone_id 	= trim($phone_data['PHONE_ID']);
			$this->phone_type 	= trim($phone_data['PHONE_TYPE']);
			$this->mdesc 		= trim($phone_data['MENU_DESCRIPTION']);
			$this->ldesc 		= trim($phone_data['LONG_DESCRIPTION']);
			$this->phone_nbr 	= trim($phone_data['PHONE_NBR']);
			$this->hours 		= trim($phone_data['HOURS']);
			$this->last_update 	= trim($phone_data['LAST_UPDATE']);
			$this->update_by 	= trim($phone_data['UPDATE_BY']);
			$this->new = FALSE;
			return true;
		}
		else
		{
			$this->setError('setPhone', '1', 'Phone Invalid');
			return false;
		}

	}

	/**
	 * Returns and array of phone types as found in PHONE_TYPE table
	 * @return array
	 */
	static function getPhoneTypes()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM PHONE_TYPE");
		while($pt = $rs->FetchRow())
		{
			$phone_types["{$pt['PHONE_TYPE']}"] = $pt;
		}
		return $phone_types;

	}

	/**
	 * Returns phone_id
	 * @return int
	 */
	public function getPhoneId() { return $this->phone_id; }

	/**
	 * Returns phone_type
	 * @return int
	 */
	public function getType() { return $this->phone_type; }

	/**
	 * Returns Description of Phone_type
	 * @param string $lorm 'LONG' or 'MENU' for appropriate description
	 * @return string
	 */
	public function getTypeDesc($lorm = 'MENU')
	{
		if($lorm == 'LONG')	{ return $this->ldesc;	}
		else { return $this->mdesc;}
	}

	/**
	 * Sets phone type
	 * @param int $phone_type
	 * @return bool
	 */
	public function setType($phone_type)
	{
		if(in_array($phone_type, array_keys(cdbPhone::getPhoneTypes())))
		{
			$this->setEvent($this->parent, $this->parent_id, 'P',
				"Phone Type Changed: '{$this->phone_type}' -> '$phone_type'.");
			$this->phone_type = $phone_type;
			return true;
		}
		else
		{
			$this->setError('setType', '1', 'Phone Type Invalid');
			return false;
		}
	}

	/**
	 * Validates Phone Number
	 * @param string $number
	 * @return bool
	 */
	static function validatePhoneNbr($number)
	{
		$formats = array('###-###-####', '####-###-###',
                '(###) ###-###', '####-####-####',
                '##-###-####-####', '####-####', '###-###-###',
                '#####-###-###', '##########');
		$format = trim(preg_replace("/[0-9]/i", "#", $number));
		return (in_array($format, $formats)) ? true : false;
	}

	/**
	 * Returns Phone Number
	 * @return string
	 */
	public function getPhoneNbr() { return $this->phone_nbr; }

	/**
	 * Sets phone number
	 * @param string $phone_nbr
	 * @return bool
	 */
	public function setPhoneNbr($phone_nbr)
	{
		if(cdbPhone::validatePhoneNbr($phone_nbr))
		{
			$this->setEvent($this->parent, $this->parent_id, 'P',
				"Phone Nbr Changed: '{$this->phone_nbr}' -> '$phone_nbr'.");
			$this->phone_nbr = $phone_nbr;
			return true;
		}
		else
		{
			$this->setError('setPhoneNbr', '1', 'Phone Number Invalid');
			return false;
		}
	}

	/**
	 * Returns hours
	 * @return string
	 */
	public function getHours() { return $this->hours; }

	/**
	 * Sets hours
	 * @param string $hours
	 * @return bool
	 */
	public function setHours($hours)
	{
		if(strlen($hours) <= 60)
		{
			$this->setEvent($this->parent, $this->parent_id, 'P',
				"Hours Changed: '{$this->hours}' -> '$hours'.");
			$this->hours = $hours;
			return true;
		}
		else
		{
			$this->setError('setHours', '1', 'Hours Too Long.');
			return false;
		}
	}

	/**
	 * Gets last update
	 * @return string date
	 */
	public function getLastUpdate() { return $this->last_update; }

	/**
	 * Gets last update by
	 * @return string
	 */
	public function getUpdateBy() { return $this->update_by; }

	/**
	 * Returns match table for module
	 * @param $module
	 * @return string
	 */
	static function phoneMatchTable($module)
	{
		$module = strtolower($module);
		$valid_modules = array(
						"company" => "COMPANY_PHONE",
						"contact" => "CONTACT_PHONE",
						"customer" => "CUSTOMER_PHONE",
						);

		if(strlen($valid_modules["$module"]) > 0)
		{
			return $valid_modules["$module"];
		}
		else
		{
			return false;
		}
	}
	
	/**
	 * Used to determine the parent of a particular phone.
	 * I hate this function. Dirty!
	 * I mean, I could condense this with some simple recursion at least...
	 * @param $pid
	 * @return array A one row array which is keyed with the field name of the parent ID.
	 */
	static function getParentID($pid) 
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		
		$company_q = self::$db->Prepare("SELECT * FROM COMPANY_PHONE WHERE trim(PHONE_ID)=:pid"); 
		$rs = self::$db->Execute($company_q, array('pid' => "$pid"));	
		if($rs->RecordCount() == 1)
		{
			$getrows = $rs->getRows();
			$getrows = array_shift($getrows);
			$return['COMPANY_ID'] = trim($getrows['COMPANY_ID']);
		}
		else
		{
			$customer_q = self::$db->Prepare("SELECT * FROM CUSTOMER_PHONE WHERE trim(PHONE_ID)=:pid"); 
			$rs = self::$db->Execute($customer_q, array('pid' => "$pid"));
			if($rs->RecordCount() == 1)
			{
				$getrows = $rs->getRows();
				$getrows = array_shift($getrows);
				$return['CUST_ID'] = trim($getrows['CUST_ID']);
			}	
			else
			{
				$contact_q = self::$db->Prepare("SELECT * FROM CONTACT_PHONE WHERE trim(PHONE_ID)=:pid"); 
				$rs = self::$db->Execute($contact_q, array('pid' => "$pid"));
				if($rs->RecordCount() == 1)
				{
					$getrows = $rs->getRows();
					$getrows = array_shift($getrows);
					$return['CUST_ID'] = trim($getrows['CONTACT_ID']);
				}					
			}
		}

		return $return;
	}

	/**
	 * Search Phone Table and return Array of results
	 * @param array $arr_terms Array of search terms. i.e.: array(COLUMN_NAME => TERM);
	 * @param string $sort Column name to sort by
	 * @param string $sort_order Ascending: 'ASC' or descending: 'DESC'
	 * @param string $andor Bind the where terms by 'AND' or 'OR'
	 * @return array
	 */
	static function search($arr_terms, $sort = NULL, $sort_order = "ASC", $andor = 'AND')
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$valid_columns = array(		'PHONE_ID'		=> 	array('int', 'PHONE'),
								    'PHONE_TYPE'	=> 	array('int', 'PHONE'),
								    'PHONE_NBR'		=> 	array('str', 'PHONE'),
									'HOURS'			=> 	array('str', 'PHONE'),
									'LAST_UPDATE' 	=> 	array('date', 'PHONE)',
									'UPDATE_BY'		=>  array('str', 'PHONE'),
									));

		$results = self::genSearch(self::MASTER_QUERY, $valid_columns, 'PHONE_ID', $arr_terms, $sort, $sort_order, $andor);
		return $results;
	}

	/**
	 * Commits modified Phone data to table and logs results
	 * @return bool
	 */
	public function commit()
	{
		$phone_vals = array(
							'pid'	=> $this->phone_id,
							'pty' 	=> $this->phone_type,
							'nbr' 	=> $this->phone_nbr,
							'hrs' 	=> $this->hours,
							'usr'	=> $this->currentUser,
							);

		if(!$this->new)
		{
			$query = self::$db->Prepare("UPDATE PHONE
									SET PHONE_TYPE=:pty,
									PHONE_NBR=:nbr,
									HOURS=:hrs,
									LAST_UPDATE=TO_CHAR(sysdate, 'DD-MM-YY'),
									UPDATE_BY=:usr
									WHERE TRIM(PHONE_ID)=:pid");
		}
		else
		{
			$query = self::$db->Prepare("INSERT INTO PHONE
									(PHONE_ID, PHONE_TYPE, PHONE_NBR, HOURS,
									LAST_UPDATE, UPDATE_BY)
									VALUES
									(:pid, :pty, :nbr, :hrs,
									TO_CHAR(sysdate, 'DD-MM-YY'), :usr)
								 	");
		}

		if(self::$db->Execute($query, $phone_vals))
		{
			if($this->new)
			{
				$mtable = cdbPhone::phoneMatchTable($this->parent);
				$mcol = $this->matchCol($this->parent);
				$match = self::$db->Execute("INSERT INTO $mtable
										($mcol, PHONE_ID)
										values ('{$this->parent_id}', '{$this->phone_id}')");
				$this->setEvent($this->parent, $this->parent_id, 'P', "New Phone Number Added");
			}
			$this->commitEvents($this->parent);
			$this->setPhone($this->phone_id);
			return true;
		}
		else
		{
			print_r(self::$db->errorMsg());
			return false;
		}


	}

}
