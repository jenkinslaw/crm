<?php
require_once('cdb.class.php');
require_once('cdbAddr.class.php');
require_once('cdbPhone.class.php');
require_once('cdbContact.class.php');
require_once('cdbCustomer.class.php');
/**
 * Project: Jenkins Law Customer DB
 * File: cdbCompany.class.php
 *
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.1.20100318
 *
 */


/**
 * CDB Company Object
 *
 * Provides methods to access and modify the COMPANY
 * table and related data.
 *
 * @package JenkinsCustomerDB
 */
class cdbCompany extends customerDB
{
	// From company table
	protected $new 				= FALSE;
	protected $company_id;
	protected $account_nbr		= NULL;
	protected $billing_name		= NULL;
	protected $category_id		= NULL;
	protected $category_desc;
	protected $area_id			= NULL;
	protected $area_mdesc;
	protected $area_ldesc;
	protected $exp_date			= NULL;
	protected $suspended		= 'N';
	protected $mbs				= NULL;
	protected $email			= NULL;
	protected $website			= NULL;
	protected $probation		= 'N';
	protected $last_update;
	protected $update_by;
	protected $cust_comment;
	protected $memb_comment;
	protected $mail_label_name;
	protected $addr_id;

	protected $address;
	protected $phones 			= array();
	protected $contacts 		= array();
	protected $customers 		= array();

	const MASTER_QUERY = "SELECT COMPANY.*,
								COMPANY_ADDRESS.ADDR_ID,
								CATEGORY.MENU_DESCRIPTION as CATEGORY_DESC,
								AREA.MENU_DESCRIPTION as AREA_MDESC,
								AREA.LONG_DESCRIPTION as AREA_LDESC
								FROM COMPANY
								LEFT OUTER JOIN COMPANY_ADDRESS ON COMPANY_ADDRESS.COMPANY_ID = COMPANY.COMPANY_ID
								LEFT OUTER JOIN CATEGORY ON COMPANY.CATEGORY_ID = CATEGORY.CATEGORY_ID
								LEFT OUTER JOIN AREA ON COMPANY.AREA_ID = AREA.AREA_ID";

	/**
	 * Construct!
	 * @param int $an Account Number
	 * @param $key_on
	 * @return unknown_type
	 */
	function __construct($an = NULL, $key_on = 'ACCOUNT_NBR')
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$this->currentUser = self::$cdb->getUser();

		if($an != NULL)
		{
			$this->setCompany($an, $key_on);
			$this->new = FALSE;
		}
		else
		{
			$this->company_id = self::$db->GenID('COMPANY_ID_SEQ');
			$this->address = new cdbAddr(NULL, 'company', $this->company_id);
			$this->addr_id = $this->address->getAddrID();
			$this->new = TRUE;
		}
	}

	/**
	 * Populates the class with company data
	 * @param string $cid The actuall ACCOUNT_NUMBER or COMPANY_ID
	 * @param string $key_on What table column to key on. ie. 'ACCOUNT_NUMBER' or 'COMPANY_ID'
	 * @return bool
	 */
	protected function setCompany($cid, $key_on = 'ACCOUNT_NBR')
	{
		switch($key_on)
		{
			case 'ACCOUNT_NBR':
				$key = 'ACCOUNT_NBR';
			break;
			case 'COMPANY_ID':
				$key = 'COMPANY_ID';
			break;

		}

		$query = self::$db->Prepare(self::MASTER_QUERY . " WHERE trim(COMPANY.$key)=:cid");
		$rs = self::$db->Execute($query, array('cid' => "$cid"));

		if($rs->RecordCount() == 1)
		{
			$comp_data = $rs->getRows();
			$comp_data = array_shift($comp_data);

			$this->company_id 			= trim($comp_data['COMPANY_ID']);
			$this->account_nbr 			= trim($comp_data['ACCOUNT_NBR']);
			$this->billing_name			= trim($comp_data['NAME']);
			$this->category_id 			= trim($comp_data['CATEGORY_ID']);
			$this->category_desc		= trim($comp_data['CATEGORY_DESC']);
			$this->area_id 				= trim($comp_data['AREA_ID']);
			$this->area_mdesc			= trim($comp_data['AREA_MDESC']);
			$this->area_ldesc			= trim($comp_data['AREA_LDESC']);
			$this->exp_date				= trim($comp_data['EXP_DATE']);
			$this->suspended			= trim($comp_data['SUSPENDED']);
			$this->mbs					= trim($comp_data['MBS']);
			$this->email				= trim($comp_data['EMAIL']);
			$this->website				= trim($comp_data['WEBSITE']);
			//$this->probation			= trim($comp_data['PROBATION']);
			$this->last_update			= trim($comp_data['LAST_UPDATE']);
			$this->update_by			= trim($comp_data['UPDATE_BY']);
			$this->cust_comment			= trim($comp_data['CUST_COMMENT']);
			$this->memb_comment			= trim($comp_data['MEMB_COMMENT']);
			$this->mail_label_name		= trim($comp_data['MAIL_LABEL_NAME']);
			$this->addr_id				= trim($comp_data['ADDR_ID']);
			$this->new = FALSE;
			return true;
		}
		else
		{
			$this->setError('setCompany', '1', 'Company Invalid');
			return false;
		}

	}

	/**
	 * Returns Company ID
	 * @return string
	 */
	public function getCompanyId() { return $this->company_id; }

	/**
	 * Returns Account Number
	 * @return string
	 */
	public function getAccountNbr() { return $this->account_nbr; }

	/**
	 * Returns Billing Name
	 * @return string
	 */
	public function getBillingName() { return $this->billing_name; }

	/**
	 * Returns Mail Label Name
	 * @return string
	 */
	public function getMailLabelName() { return $this->mail_label_name; }

	/**
	 * ALWAYS Returns Correct Company Name
	 * @return string
	 */
	public function getCompanyName()
	{
		if($this->mail_label_name)
		{
			return $this->mail_label_name;
		}
		else
		{
			return $this->billing_name;
		}
	}

	/**
	 * Sets Company Name and Mail Label Name if need be
	 * @param string $company_name
	 * @return bool
	 */
	public function setCompanyName($company_name)
	{
		$this->setEvent('company', $this->company_id, 'N',  "'{$this->billing_name}', '{$this->mail_label_name}' -> '$company_name'.");
		if(strlen($company_name) > 30)
		{
			$this->mail_label_name = $company_name;
			// DO FUN STUFF TO MAKE IT FIT IN THIRTY CHARACTERS!!!!
			// FOR NOW, I AM JUST CHOPPING THE SHIT DOWN...
			$this->billing_name = substr($company_name, 0, 30);
			return true;
		}
		else
		{
			$this->billing_name = $company_name;
			$this->mail_label_name = "";
			return true;
		}

	}

	/**
	 * Returns Category ID
	 * @return string
	 */
	public function getCategoryId() { return $this->category_id; }

	/**
	 * Gets Category Description
	 * @return string
	 */
	public function getCategoryDesc() { return $this->category_desc; }

	/**
	 * Returns and array of all possible categories
	 * @return array
	 */
	static function getCategories()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM CATEGORY");
		while($cat = $rs->FetchRow())
		{
			$cats["{$cat['CATEGORY_ID']}"] = $cat;
		}
		return $cats;
	}

	/**
	 * Sets category id
	 * @param int $cat_id Category ID Number as valid from table CATEGORY
	 * @return bool
	 */
	public function setCategory($cat_id)
	{
		if(in_array($cat_id, array_keys(cdbCompany::getCategories())))
		{
			$this->setEvent('company', $this->company_id, 'O',
				"Category Changed'{$this->category_id}', '{$this->category_desc}' -> '$cat_id'.");
			$this->category_id = $cat_id;
			return true;
		}
		else
		{
			$this->setError('setCategory', '1', 'Category Invalid.');
			return false;
		}
	}

	/**
	 * Returns an array of area types
	 * @return array
	 */
	static function getAreaTypes()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM AREA");
		while($at = $rs->FetchRow())
		{
			$area_types["{$at['AREA_ID']}"] = $at;
		}
		return $area_types;
	}

	/**
	 * Returns Area ID
	 * @return string
	 */
	public function getAreaId() { return $this->area_id; }

	/**
	 * Returns area Description
	 * @param string $lorm Either 'MENU' or 'LONG' for appropriate description
	 * @return string
	 */
	public function getAreaDesc($lorm = 'MENU')
	{
		if($lorm == 'LONG')	{ return $this->area_ldesc;	}
		else { return $this->area_mdesc;}
	}

	/**
	 * Sets Area ID
	 * @param int $area_id Valid area from AREA table
	 * @return bool
	 */
	public function setArea($area_id)
	{
		if(in_array($area_id, array_keys(cdbCompany::getAreaTypes())))
		{
			$this->setEvent('company', $this->company_id, 'O',
				"Area Changed'{$this->area_id}' -> '$area_id'.");
			$this->area_id = $area_id;
			return true;
		}
		else
		{
			$this->setError('setArea', '1', 'Area Id Invalid.');
			return false;
		}
	}

	/**
	 * Returns Expiration Date
	 * @return string date
	 */
	public function getExpDate() { return $this->exp_date; }

	/**
	 * Sets Expiration date
	 * @param $m month
	 * @param $d day
	 * @param $y year
	 * @return bool
	 */
	public function setExpDate($m, $d, $y)
	{
		if(checkdate($m, $d, $y))
		{
			$this->setEvent('company', $this->company_id, 'O',
				"Exp Date Changed '{$this->exp_date}' -> '$y-$m-$d'.");
			$this->exp_date = "$y-$m-$d";
			return true;
		}
		else
		{
			$this->setError('setExpDate', '1', 'Exp Date Invalid.');
			return false;
		}

	}

	/**
	 * Returns Y or N of MBS
	 * @return string
	 */
	public function getMBS() { return $this->mbs; }

	/**
	 * Sets MBS
	 * @param $yn Must be 'Y' or 'N'
	 * @return unknown_type
	 */
	public function setMBS($yn)
	{
		switch(strtolower($yn))
		{
			case 'y':
				$this->setEvent('company', $this->company_id, 'O',  "MBS '{$this->mbs}' -> 'Y'.");
				$this->mbs = 'Y';
				return true;
				break;
			case 'n':
				$this->setEvent('company', $this->company_id, 'O',  "MBS '{$this->mbs}' -> 'N'.");
				$this->mbs = 'N';
				return true;
				break;
			default:
				$this->setError('setMbs', '1', 'MBS Must be Y or N.');
				return false;
				break;
		}
	}

	/**
	 * Returns Y or N for Suspended
	 * @return string
	 */
	public function getSuspended() { return $this->suspended; }

	/**
	 * Sets Suspended
	 * @param $yn Must be 'Y' or 'N'
	 * @return bool
	 */
	public function setSuspended($yn)
	{
		switch(strtolower($yn))
		{
			case 'y':
				$this->setEvent('company', $this->company_id, 'O',  "Suspended '{$this->suspended}' -> 'Y'.");
				$this->suspended = 'Y';
				return true;
				break;
			case 'n':
				$this->setEvent('company', $this->company_id, 'O',  "Suspended '{$this->suspended}' -> 'N'.");
				$this->suspended = 'N';
				return true;
				break;
			default:
				$this->setError('setSuspended', '1', 'Suspended Must be Y or N.');
				return false;
				break;
		}
	}

	/**
	 * Gets Email Address
	 * @return string
	 */
	public function getEmail() { return $this->email; }

	/**
	 * Sets Email Address
	 * @param $email Email
	 * @return bool
	 */
	public function setEmail($email)
	{
		if(preg_match('/^[_A-z0-9-]+((\.|\+)[_A-z0-9-]+)*@[A-z0-9-]+(\.[A-z0-9-]+)*(\.[A-z]{2,4})$/',$email)
			&& strlen($email) <= 40)
		{
			$this->setEvent('company', $this->company_id, 'O',  "Email '{$this->email}' -> '$email'.");
			$this->email = $email;
			return true;
		}
		else
		{
			$this->setError('setEmail', '1', 'Email format invalid.');
			return false;
		}
	}

	/**
	 * Returns Website URL
	 * @return string
	 */
	public function getWebsite() { return $this->website; }

	/**
	 * Sets Website URL
	 * @param $url URL
	 * @return bool
	 */
	public function setWebsite($url)
	{
		if(strlen($url) <= 40)
		{
			$this->setEvent('company', $this->company_id, 'O',  "Website '{$this->website}' -> '$url'.");
			$this->website = $url;
			return true;
		}
		else
		{
			$this->setError('setWebsite', '1', 'Website string length too long.');
			return false;
		}
	}


	/**
	 * Returns Y or N for Probation
	 * @return string
	 */
	public function getProbation()
	{
		if(strlen($this->probation) == 0)
		{
			return 'N';
		}
		else
		{
			return $this->probation;
		}
	}

	/**
	 * Sets Probation
	 * @param $yn Must be 'Y' or 'N'
	 * @return bool
	 */
	public function setProbation($yn)
	{
		switch(strtolower($yn))
		{
			case 'y':
				$this->setEvent('company', $this->company_id, 'O',  "Probation '{$this->probation}' -> 'Y'.");
				$this->probation = 'Y';
				return true;
				break;
			case 'n':
				$this->setEvent('company', $this->company_id, 'O',  "Probation '{$this->probation}' -> 'N'.");
				$this->probation = 'N';
				return true;
				break;
			default:
				$this->setError('setProbation', '1', 'Probation Must be Y or N.');
				return false;
				break;
		}
	}


	/**
	 * Returns last updated
	 * @return string date
	 */
	public function getLastUpdate() { return $this->last_update; }

	/**
	 * Returns who last updated
	 * @return string date
	 */
	public function getUpdateBy() { return $this->update_by; }

	/**
	 * Returns Customer Comment
	 * @return string
	 */
	public function getCustComment() { return $this->cust_comment; }

	/**
	 * Sets Customer Comment
	 * @param $comment
	 * @return bool
	 */
	public function setCustComment($comment)
	{
		if(strlen($comment) <= 60)
		{
			$this->setEvent('company', $this->company_id, 'O',  "Cust Comment '{$this->cust_comment}' -> '$comment'.");
			$this->cust_comment = $comment;
			return true;
		}
		else
		{
			$this->setError('setCustComment', '1', 'Comment Too Long.');
			return false;
		}
	}

	/**
	 * Returns Member Comment
	 * @return string
	 */
	public function getMembComment() { return $this->memb_comment; }

	/**
	 * Sets Member Comment
	 * @param $comment
	 * @return bool
	 */
	public function setMembComment($comment)
	{
		if(strlen($comment) <= 60)
		{
			$this->setEvent('company', $this->company_id, 'O',  "Cust Comment '{$this->memb_comment}' -> '$comment'.");
			$this->memb_comment = $comment;
			return true;
		}
		else
		{
			$this->setError('setMembComment', '1', 'Comment Too Long.');
			return false;
		}
	}

	/**
	 * Gets matching company address from cdbAddr
	 * @return object
	 */
	public function getAddress()
	{
		if(!$this->address)
		{
			$this->address = new cdbAddr($this->addr_id, 'company', $this->company_id);
		}
		return $this->address;
	}

	/**
	 * Returns the ID of a NEW phone number to be added
	 * @return object
	 */
	public function newPhone()
	{
		$new_phone = new cdbPhone(NULL, 'company', $this->company_id);
		$new_phone_id = $new_phone->getPhoneId();
		$this->phones["$new_phone_id"] = $new_phone;
		return $this->phones["$new_phone_id"];
	}

	/**
	 * Sets Company phone numbers
	 */
	protected function setPhones()
	{
		$rs = self::$db->Execute("SELECT * FROM COMPANY_PHONE
									 WHERE trim(COMPANY_ID)='{$this->company_id}'");
		while ($p = $rs->FetchRow())
		{
			$this->phones["{$p['PHONE_ID']}"] =
				new cdbPhone($p['PHONE_ID'], 'company', $this->company_id);
		}
	}

	/**
	 * Get an Array of valid phone number ids
	 * @return array
	 */
	public function getPhones()
	{
		if(sizeof($this->phones) == 0)
		{
			$this->setPhones();
		}
		return array_keys($this->phones);
	}

	/**
	 * Returns an cdbPhone object of the matching Phone ID
	 * @param $phone_id Phone ID
	 * @return Object
	 */
	public function getPhone($phone_id)
	{
		if(sizeof($this->phones) == 0)
		{
			$this->setPhones();
		}

		if(is_object($this->phones["{$phone_id}"]))
		{
			return $this->phones["{$phone_id}"];
		}
		else
		{
			return false;
		}
	}

	/**
	 * Sets Company Contacts
	 * @return array Id's of matching contacts
	 */
	protected function setContacts()
	{
		$rs = self::$db->Execute("SELECT * FROM CONTACT
									 WHERE trim(COMPANY_ID)='{$this->company_id}'");
		while ($ct = $rs->FetchRow())
		{
			$this->contacts["{$ct['CONTACT_ID']}"] = new cdbContact($ct['CONTACT_ID']);
		}
	}

	/**
	 * Returns an array of ID's for Company Contacts
	 * @return array
	 */
	public function getContacts()
	{
		if(sizeof($this->contacts) == 0)
		{
			$this->setContacts();
		}
		return array_keys($this->contacts);
	}

	/**
	 * Get a cdbContact object for contact_id
	 * @param $contact_id
	 * @return object
	 */
	public function getContact($contact_id)
	{
		if(sizeof($this->contacts) == 0)
		{
			$this->setContacts();
		}

		if(is_object($this->contacts["{$contact_id}"]))
		{
			return $this->contacts["{$contact_id}"];
		}
		else
		{
			return false;
		}
	}

	/**
	 * Sets Company Customers
	 * @return array Id's of matching custiners
	 */
	protected function setCustomers()
	{
		$rs = self::$db->Execute("SELECT * FROM CUSTOMER
									 WHERE trim(COMPANY_ID)='{$this->company_id}' order by TITLE_ID, LNAME");
		while ($ct = $rs->FetchRow())
		{
			$this->customers["{$ct['CUST_ID']}"] = new cdbCustomer($ct['CUST_ID']);
		}
	}

	/**
	 * Returns an array of ID's for Company Customers
	 * @return array
	 */
	public function getCustomers()
	{
		if(sizeof($this->customers) == 0)
		{
			$this->setCustomers();
		}
		return array_keys($this->customers);
	}

	/**
	 * Get a cdbCustomer object for cust_id
	 * @param $cust_id
	 * @return object
	 */
	public function getCustomer($cust_id)
	{
		if(sizeof($this->customers) == 0)
		{
			$this->setCustomers();
		}

		if(is_object($this->customers["{$cust_id}"]))
		{
			return $this->customers["{$cust_id}"];
		}
		else
		{
			return false;
		}
	}

	/**
	 * Returns the number of attorney's for company
	 * @return int
	 */
	public function getNumOfAttys()
	{
		$rs = self::$db->Execute("SELECT * FROM CUSTOMER
									 WHERE trim(COMPANY_ID)='{$this->company_id}'
									 AND STATUS_ID = '1'");
		$num = $rs->RecordCount();
		return $num;
	}

	/**
	 * Returns an array of registered, but not yet commited, events
	 * @return array
	 */
	public function getEvents()
	{
		$events = $this->getEventsFor('company', $this->company_id);
		return $events;
	}

	/**
	 * Search Company Table and return Array of results
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
		$valid_columns = array('COMPANY_ID'		=> 	array('int', 'COMPANY'),
								    'ACCOUNT_NBR'	=> 	array('str', 'COMPANY'),
								    'NAME'			=> 	array('str', 'COMPANY'),
								    'CATEGORY_ID'	=> 	array('char', 'COMPANY'),
								    'AREA_ID'		=> 	array('char', 'COMPANY'),
		//The date here will be handled by function `strtodate`: This function expects to be given a string containing a US English date format
								 	'EXP_DATE' 		=> 	array('date', 'COMPANY'),
									'MBS'			=> 	array('bool', 'COMPANY'),
									'SUSPENDED'		=>	array('bool', 'COMPANY'),
									//'PROBATION'		=>	array('bool', 'COMPANY'),
									'EMAIL'			=> 	array('str', 'COMPANY'),
									'WEBSITE'		=> 	array('str', 'COMPANY'),
									'LAST_UPDATE' 	=> 	array('date', 'COMPANY)',
									'UPDATE_BY'		=>  array('str', 'COMPANY'),
									'CUST_COMMENT' 	=> 	array('str', 'COMPANY'),
									'MEMB_COMMENT' 	=> 	array('str', 'COMPANY'),
									'MAIL_LABEL_NAME'  	=> 	array('str', 'COMPANY'),
									));

		$results = self::genSearch(self::MASTER_QUERY, $valid_columns, 'COMPANY_ID', $arr_terms, $sort, $sort_order, $andor);
		return $results;
	}

	/**
	 * Commits modified company data to table and logs events
	 * @return bool
	 */
	public function commit()
	{
		$company_vals = array(
							'cid'	=> $this->company_id,
							'bn' 	=> $this->billing_name,
							'mln' 	=> $this->mail_label_name,
							'ctd'	=> $this->category_id,
							'aid'	=> $this->area_id,
							'exp'	=> $this->exp_date,
							'mbs'	=> $this->mbs,
							'sus'	=> $this->suspended,
							//'prb'	=> $this->probation,
							'eml'	=> $this->email,
							'web'	=> $this->website,
							'ccm'	=> $this->cust_comment,
							'mcm'	=> $this->memb_comment,
							'usr'	=> $this->currentUser,
							);

		if(!$this->new)
		{
			/*
			// PROBATION@!
			$query = self::$db->Prepare("UPDATE COMPANY
									SET NAME=:bn,
									MAIL_LABEL_NAME=:mln,
									CATEGORY_ID=:ctd,
									AREA_ID=:aid,
									EXP_DATE=:exp,
									MBS=:mbs,
									SUSPENDED=:sus,
									PROBATION=:prb,
									EMAIL=:eml,
									WEBSITE=:web,
									CUST_COMMENT=:ccm,
									MEMB_COMMENT=:mcm,
									LAST_UPDATE=TO_CHAR(sysdate, 'DD-MM-YY'),
									UPDATE_BY=:usr
									WHERE TRIM(COMPANY_ID)=:cid
								 	");
			*/
			
			$query = self::$db->Prepare("UPDATE COMPANY
									SET NAME=:bn,
									MAIL_LABEL_NAME=:mln,
									CATEGORY_ID=:ctd,
									AREA_ID=:aid,
									EXP_DATE=:exp,
									MBS=:mbs,
									SUSPENDED=:sus,
									EMAIL=:eml,
									WEBSITE=:web,
									CUST_COMMENT=:ccm,
									MEMB_COMMENT=:mcm,
									LAST_UPDATE=TO_CHAR(sysdate, 'DD-MM-YY'),
									UPDATE_BY=:usr
									WHERE TRIM(COMPANY_ID)=:cid
								 	");			
			
		}
		else
		{
			$acct_number = array('acn' => "10" . $this->company_id);
			$company_vals = array_merge($acct_number, $company_vals);

			/*
			// PROBATION!
			$query = self::$db->Prepare("INSERT INTO COMPANY
									(COMPANY_ID, ACCOUNT_NBR, NAME, MAIL_LABEL_NAME, CATEGORY_ID, AREA_ID,
									EXP_DATE, MBS, SUSPENDED, PROBATION, EMAIL, WEBSITE,
									CUST_COMMENT, MEMB_COMMENT,
									LAST_UPDATE, UPDATE_BY)
									VALUES
									(:cid, :acn, :bn, :mln, :ctd, :aid,
									:exp, :mbs, :sus, :prb, :eml, :web,
									:ccm, :mcm,
									TO_CHAR(sysdate, 'DD-MM-YY'), :usr)
								 	");
			*/
			
			$query = self::$db->Prepare("INSERT INTO COMPANY
									(COMPANY_ID, ACCOUNT_NBR, NAME, MAIL_LABEL_NAME, CATEGORY_ID, AREA_ID,
									EXP_DATE, MBS, SUSPENDED, EMAIL, WEBSITE,
									CUST_COMMENT, MEMB_COMMENT,
									LAST_UPDATE, UPDATE_BY)
									VALUES
									(:cid, :acn, :bn, :mln, :ctd, :aid,
									:exp, :mbs, :sus, :eml, :web,
									:ccm, :mcm,
									TO_CHAR(sysdate, 'DD-MM-YY'), :usr)
								 	");			
			
			
			$this->setEvent('company', $this->company_id, 'O',
				"New Company!.");
			$this->address->commit();
		}

		$ok = self::$db->Execute($query, $company_vals);
		if($ok)
		{
			$this->commitEvents('company');

			// Lets repopulate the class to be sure.
			$this->setCompany($this->company_id, 'COMPANY_ID');

			return true;
		}
		else
		{
			print_r(self::$db->errorMsg());
			return false;
		}


	}

}
