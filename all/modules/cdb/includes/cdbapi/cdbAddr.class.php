<?php
require_once('cdb.class.php');
/**
 * Project: Jenkins Law Customer DB
 * File: cdbAddr.class.php
 *
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.0.20090814
 */


/**
 * CDB Address Object
 *
 * Provides methods to access and modify the ADDRESS
 * table and related data.
 *
 * @package JenkinsCustomerDB
 */
class cdbAddr extends customerDB
{
	protected $new 			= FALSE;
	protected $addr_id;
	protected $addr_type	= NULL;
	protected $type_mdesc;
	protected $type_ldesc;
	protected $addr_line1	= NULL;
	protected $addr_line2	= NULL;
	protected $addr_line3	= NULL;
	protected $city			= NULL;
	protected $state		= NULL;
	protected $country		= NULL;
	protected $postal_code	= NULL;
	protected $last_update;
	protected $update_by;
	protected $parent;
	protected $parent_id;

	const MASTER_QUERY = "SELECT ADDRESS.*, ADDR_TYPE.*
									FROM ADDRESS
									LEFT OUTER JOIN ADDR_TYPE
									ON ADDR_TYPE.ADDR_TYPE = ADDRESS.ADDR_TYPE";

	/**
	 * CONSTURCT!
	 * @param int $addr_id Address ID from ADDRESS
	 * @param string $parent Parent, ie: 'company', 'contact' or 'customer'
	 * @param int $parent_id ID of Parent
	 * @return unknown_type
	 */
	function __construct($addr_id = NULL, $parent, $parent_id)
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$this->currentUser = self::$cdb->getUser();
		if($addr_id != NULL)
		{
			$this->setAddress($addr_id);
			$this->new = FALSE;
		}
		else
		{
			$this->addr_id = self::$db->GenID('ADDR_ID_SEQ');
			$this->new = TRUE;
		}

		// I REALLY SHOULD CHECK IF THESE VALUES ARE KOSHER
		$this->parent = $parent;
		$this->parent_id = $parent_id;
	}

	/**
	 * Populates address object
	 * @param int $aid Address ID from ADDRESS
	 * @return bool
	 */
	protected function setAddress($aid)
	{
		$query = self::$db->Prepare(self::MASTER_QUERY . " WHERE trim(ADDR_ID)=:aid");
		$rs = self::$db->Execute($query, array('aid' => "$aid"));

		if($rs->RecordCount() == 1)
		{
			$addr_data = $rs->getRows();
			$addr_data = array_shift($addr_data);

			$this->addr_id 			= trim($addr_data['ADDR_ID']);
			$this->addr_type 		= trim($addr_data['ADDR_TYPE']);
			$this->type_mdesc		= trim($addr_data['MENU_DESCRIPTION']);
			$this->type_ldesc		= trim($addr_data['LONG_DESCRIPTION']);
			$this->addr_line1 		= trim($addr_data['ADDR_LINE1']);
			$this->addr_line2 		= trim($addr_data['ADDR_LINE2']);
			$this->addr_line3 		= trim($addr_data['ADDR_LINE3']);
			$this->city 			= trim($addr_data['CITY']);
			$this->state 			= trim($addr_data['STATE']);
			$this->country 			= trim($addr_data['COUNTRY']);
			$this->postal_code 		= trim($addr_data['POSTAL_CODE']);
			$this->last_update 	= trim($addr_data['LAST_UPDATE']);
			$this->update_by	= trim($addr_data['UPDATE_BY']);

			$this->new = FALSE;
			return true;
		}
		else
		{
			$this->setError('setAddr', '1', 'Addr Invalid');
			return false;
		}
	}

	/**
	 * Returns an array of addr_types
	 * @return array
	 */
	static function getAddrTypes()
	{
		$rs = self::$db->Execute("SELECT * FROM ADDR_TYPE");
		while($at = $rs->FetchRow())
		{
			$addr_types["{$at['ADDR_TYPE']}"] = $at;
		}
		return $addr_types;
	}

	/**
	 * Returns Address ID
	 * @return int
	 */
	public function getAddrID() { return $this->addr_id; }

	/**
	 * Returns Type ID
	 * @return int
	 */
	public function getType() { return $this->addr_type; }

	/**
	 * Returns Description of Addr_type
	 * @param string $lorm 'LONG' or 'MENU' for appropriate description
	 * @return string
	 */
	public function getTypeDesc($lorm = 'MENU')
	{
		if($lorm == 'LONG')	{ return $this->type_ldesc;	}
		else { return $this->type_mdesc;}
	}

	/**
	 * Sets Addr Type
	 * @param int $addr_type
	 * @return bool
	 */
	public function setType($addr_type)
	{
		if(in_array($addr_type, array_keys(cdbAddr::getAddrTypes())))
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"Addr Type Changed: '{$this->addr_type}' -> '$addr_type'.");
			$this->addr_type = $addr_type;
			return true;
		}
		else
		{
			$this->setError('setType', '1', 'Addr Type Invalid');
			return false;
		}
	}

	/**
	 * Gets first line of address
	 * @return string
	 */
	public function getAddrLine1() { return $this->addr_line1; }

	/**
	 * Sets first line of address
	 * @param string $line
	 * @return bool
	 */
	public function setAddrLine1($line)
	{
		if(strlen($line) <= 60)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"Addr Line 1 Changed: '{$this->addr_line1}' -> '$line'.");
			$this->addr_line1 = $line;
			return true;
		}
		else
		{
			$this->setError('setAddrLine1', '1', 'Addr Line 1 Too Long.');
			return false;
		}
	}

	/**
	 * Get Second line of address
	 * @return string
	 */
	public function getAddrLine2() { return $this->addr_line2; }

	/**
	 * Set second line of address.
	 * @param string $line
	 * @return bool
	 */
	public function setAddrLine2($line)
	{
		if(strlen($line) <= 60)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"Addr Line 2 Changed: '{$this->addr_line2}' -> '$line'.");
			$this->addr_line2 = $line;
			return true;
		}
		else
		{
			$this->setError('setAddrLine2', '2', 'Addr Line 2 Too Long.');
			return false;
		}
	}

	/**
	 * Get Third line of address
	 * @return string
	 */
	public function getAddrLine3() { return $this->addr_line3; }

	/**
	 * Set third line of address
	 * @param string $line
	 * @return bool
	 */
	public function setAddrLine3($line)
	{
		if(strlen($line) <= 60)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"Addr Line 3 Changed: '{$this->addr_line3}' -> '$line'.");
			$this->addr_line3 = $line;
			return true;
		}
		else
		{
			$this->setError('setAddrLine3', '1', 'Addr Line 3 Too Long.');
			return false;
		}
	}

	/**
	 * Returns City
	 * @return string
	 */
	public function getCity() { return $this->city; }

	/**
	 * Sets City
	 * @param string $city
	 * @return bool
	 */
	public function setCity($city)
	{
		if(strlen($city) <= 30)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"City Changed: '{$this->city}' -> '$city'.");
			$this->city = $city;
			return true;
		}
		else
		{
			$this->setError('setCity', '1', 'City Too Long.');
			return false;
		}
	}

	/**
	 * Returns state
	 * @return string
	 */
	public function getState() { return $this->state; }

	/**
	 * Sets State
	 * @param string $state
	 * @return bool
	 */
	public function setState($state)
	{
		if(strlen($state) <= 30)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"state Changed: '{$this->state}' -> '$state'.");
			$this->state = $state;
			return true;
			}
		else
		{
			$this->setError('setState', '1', 'State Too Long.');
			return false;
		}
	}

	/**
	 * Returns Zip Code
	 * @return string
	 */
	public function getPostalCode() { return $this->postal_code; }

	/**
	 * Sets zip code
	 * @param string $postal_code
	 * @return bool
	 */
	public function setPostalCode($postal_code)
	{
		if(strlen($postal_code) <= 30)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"Postal Code Changed: '{$this->postal_code}' -> '$postal_code'.");
			$this->postal_code = $postal_code;
			return true;
		}
		else
		{
			$this->setError('setPostalCode', '1', 'Zip Too Long.');
			return false;
		}
	}

	/**
	 * Returns Country
	 * @return string
	 */
	public function getCountry() { return $this->Country; }

	/**
	 * Sets country
	 * @param string $country
	 * @return bool
	 */
	public function setCountry($country)
	{
		if(strlen($country) <= 30)
		{
			$this->setEvent($this->parent, $this->parent_id, 'A',
				"Country Changed: '{$this->country}' -> '$country'.");
			$this->country = $country;
			return true;
		}
		else
		{
			$this->setError('setCountry', '1', 'Country Too Long.');
			return false;
		}
	}

	/**
	 * Returns Last Update
	 * @return string date
	 */
	public function getLastUpdate() { return $this->last_update; }

	/**
	 * Returns Last Update By
	 * @return string
	 */
	public function getUpdateBy() { return $this->update_by; }

	/**
	 * Returns match table for module
	 * @param $module
	 * @return string
	 */
	static function addrMatchTable($module)
	{
		$module = strtolower($module);
		$valid_modules = array(
						"company" => "COMPANY_ADDRESS",
						"contact" => "CONTACT_ADDRESS",
						"customer" => "CUSTOMER_ADDRESS",
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
	 * Used to determine the parent of a particular addr.
	 * I hate this function. Dirty!
	 * I mean, I could condense this with some simple recursion at least...
	 * @param $pid
	 * @return array A one row array which is keyed with the field name of the parent ID.
	 */
	static function getParentID($aid) 
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		
		$company_q = self::$db->Prepare("SELECT * FROM COMPANY_ADDRESS WHERE trim(ADDR_ID)=:aid"); 
		$rs = self::$db->Execute($company_q, array('aid' => "$aid"));	
		if($rs->RecordCount() == 1)
		{
			$getrows = $rs->getRows();
			$getrows = array_shift($getrows);
			$return['COMPANY_ID'] = trim($getrows['COMPANY_ID']);
		}
		else
		{
			$customer_q = self::$db->Prepare("SELECT * FROM CUSTOMER_ADDRESS WHERE trim(ADDR_ID)=:aid"); 
			$rs = self::$db->Execute($customer_q, array('aid' => "$aid"));
			if($rs->RecordCount() == 1)
			{
				$getrows = $rs->getRows();
				$getrows = array_shift($getrows);
				$return['CUST_ID'] = trim($getrows['CUST_ID']);
			}	
			else
			{
				$contact_q = self::$db->Prepare("SELECT * FROM CONTACT_ADDRESS WHERE trim(ADDR_ID)=:aid"); 
				$rs = self::$db->Execute($contact_q, array('aid' => "$aid"));
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
	 * Search Address Table and return Array of results
	 * @param array $arr_terms Array of search terms. i.e.: array(COLUMN_NAME => TERM);
	 * @param string $sort Column name to sort by
	 * @param string $sort_order Ascending: 'ASC' or descending: 'DESC'
	 * @param string $andor Bind the where terms by 'AND' or 'OR'
	 * @return array
	 */
	static function search($arr_terms, $sort = NULL, $sort_order = "ASC", $andor = 'AND')
	{
		$valid_columns = array(		'ADDR_ID'		=> 	array('int', 'ADDRESS'),
								    'ADDR_TYPE'		=> 	array('int', 'ADDRESS'),
								    'ADDR_LINE1'	=> 	array('str', 'ADDRESS'),
									'ADDR_LINE2'	=> 	array('str', 'ADDRESS'),
									'ADDR_LINE3'	=> 	array('str', 'ADDRESS'),
								    'CITY'			=> 	array('str', 'ADDRESS'),
								    'STATE'			=> 	array('str', 'COMPANY'),
								 	'COUNTRY' 		=> 	array('str', 'COMPANY'),
									'POSTAL_CODE'	=> 	array('str', 'COMPANY'),
									'LAST_UPDATE' 	=> 	array('date', 'ADDRESS)',
									'UPDATE_BY'		=>  array('str', 'ADDRESS'),
									));

		$results = self::genSearch(self::MASTER_QUERY, $valid_columns, 'ADDR_ID', $arr_terms, $sort, $sort_order, $andor);
		return $results;
	}

	/**
	 * Commits modified Address data to table and logs results
	 * @return bool
	 */
	public function commit()
	{
		$addr_vals = array(
							'aid'	=> $this->addr_id,
							'aty' 	=> $this->addr_type,
							'ln1' 	=> $this->addr_line1,
							'ln2' 	=> $this->addr_line2,
							'ln3' 	=> $this->addr_line3,
							'cty' 	=> $this->city,
							'sta' 	=> $this->state,
							'usa' 	=> $this->country,
							'zip' 	=> $this->postal_code,
							'usr'	=> $this->currentUser,
							);

		if(!$this->new)
		{
			$query = self::$db->Prepare("UPDATE ADDRESS
									SET ADDR_TYPE=:aty,
									ADDR_LINE1=:ln1,
									ADDR_LINE2=:ln2,
									ADDR_LINE3=:ln3,
									CITY=:cty,
									STATE=:sta,
									COUNTRY=:usa,
									POSTAL_CODE=:zip,
									LAST_UPDATE=TO_CHAR(sysdate, 'DD-MM-YY'),
									UPDATE_BY=:usr
									WHERE TRIM(ADDR_ID)=:aid");
		}
		else
		{
			//$addr_ids = array('aid' => self::$db->GenID('ADDR_ID_SEQ'));
			//$addr_vals = array_merge($addr_ids, $addr_vals);

			$query = self::$db->Prepare("INSERT INTO ADDRESS
									(ADDR_ID, ADDR_TYPE, ADDR_LINE1, ADDR_LINE2, ADDR_LINE3,
									CITY, STATE, COUNTRY, POSTAL_CODE,
									LAST_UPDATE, UPDATE_BY)
									VALUES
									(:aid, :aty, :ln1, :ln2, :ln3,
									:cty, :sta, :usa, :zip,
									TO_CHAR(sysdate, 'DD-MM-YY'), :usr)
								 	");
		}

		if(self::$db->Execute($query, $addr_vals))
		{
			if($this->new)
			{
				$mtable = cdbAddr::addrMatchTable($this->parent);
				$mcol = cdbAddr::matchCol($this->parent);

				$match = self::$db->Execute("INSERT INTO $mtable
										($mcol, ADDR_ID)
										values ('{$this->parent_id}', '{$this->addr_id}')");

			}
			$this->commitEvents($this->parent);
			$this->setAddress($this->addr_id, $this->parent, $this->parent_id);
			return true;
		}
		else
		{
			print_r(self::$db->errorMsg());
			return false;
		}

	}

}
