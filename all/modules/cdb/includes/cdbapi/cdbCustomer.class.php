<?php
require_once('cdb.class.php');
require_once('cdbPerson.class.php');
/**
 * Project: Jenkins Law Customer DB
 * File: cdbContact.class.php
 *
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.0.20100830
 */



/**
 * CDB Contact Object
 *
 * Provides methods to access and modify the CUSTOMER
 * table and related data.
 *
 * @package JenkinsCustomerDB
 */
class cdbCustomer extends cdbPerson
{
	protected $new = FALSE;
	protected $cust_id;
	protected $barcode;
	protected $title_id			= NULL;
	protected $title_desc;
	protected $status_id		= NULL;
	protected $status_desc;
	protected $patron_type_id	= NULL;
	protected $patron_type_desc;
	protected $cm				= NULL;
	protected $cc_last4			= NULL;
	protected $charging			= NULL;
	protected $area_id			= NULL;
	protected $area_mdesc;
	protected $area_ldesc;
	protected $suspended		= 'N';
	protected $dues				= NULL;
	protected $exp_date			= NULL;
	protected $cc_exp_date		= NULL;
	protected $cm_coded_date	= NULL;
	protected $cm_copier_can_date	= NULL;
	protected $cm_card_can_date		= NULL;
	protected $cust_comment			= NULL;
	protected $memb_comment			= NULL;
	protected $cle_id				= 1;

	const MASTER_QUERY = "SELECT CUSTOMER.*,  COMPANY.NAME, COMPANY.ACCOUNT_NBR,
								TITLE.MENU_DESCRIPTION AS TITLE_DESC,
								STATUS.MENU_DESCRIPTION AS STATUS_DESC,
								PATRON_TYPE.MENU_DESCRIPTION AS PATRON_TYPE_DESC,
								AREA.MENU_DESCRIPTION as AREA_MDESC,
								AREA.LONG_DESCRIPTION as AREA_LDESC
								FROM CUSTOMER
								LEFT OUTER JOIN TITLE ON CUSTOMER.TITLE_ID = TITLE.TITLE_ID
								LEFT OUTER JOIN STATUS ON CUSTOMER.STATUS_ID = STATUS.STATUS_ID
								LEFT OUTER JOIN PATRON_TYPE ON CUSTOMER.PATRON_TYPE_ID = PATRON_TYPE.PATRON_TYPE_ID
								LEFT OUTER JOIN AREA ON CUSTOMER.AREA_ID = AREA.AREA_ID
								LEFT OUTER JOIN COMPANY
										ON CUSTOMER.COMPANY_ID = COMPANY.COMPANY_ID";

	/**
	 * CONSTRUCT!
	 * @param $cust_id CUSTOMER ID
	 * @param $company_id	COMPANY ID
	 */
	function __construct($cust_id = NULL, $company_id = NULL)
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$this->currentUser = self::$cdb->getUser();
		$this->parent = "CUSTOMER";
		if($cust_id != NULL)
		{
			$this->setCustomer($cust_id);
			$this->parent_id = $this->cust_id;
			$this->new = FALSE;
		}
		else
		{
			$this->company_id = $company_id;
			$this->cust_id = self::$db->GenID('CUST_ID_SEQ');
			$this->parent_id = $this->cust_id;
			$this->setNewBarcode();
			$this->address = new cdbAddr(NULL, 'customer', $this->cust_id);
			$this->new = TRUE;
		}
	}

	/**
	 * Populates the customer object
	 * @param $cust_id Customer ID
	 * @return bool
	 */
	protected function setCustomer($cust_id)
	{
		$query = self::$db->Prepare(self::MASTER_QUERY . " WHERE trim(CUST_ID)=:cud");

		$rs = self::$db->Execute($query, array('cud' => "$cust_id"));

		if($rs->RecordCount() == 1)
		{
			$customer = $rs->getRows();
			$customer  = array_shift($customer);

			$this->cust_id			= trim($customer['CUST_ID']);
			$this->barcode			= trim($customer['BARCODE']);
			$this->company_id 		= trim($customer['COMPANY_ID']);
			$this->foa		 		= trim($customer['FOA']);
			$this->lname	 		= trim($customer['LNAME']);
			$this->fname	 		= trim($customer['FNAME']);
			$this->mname 			= trim($customer['MNAME']);
			$this->email 			= trim($customer['EMAIL']);
			$this->title_id 		= trim($customer['TITLE_ID']);
			$this->title_desc 		= trim($customer['TITLE_DESC']);
			$this->status_id		= trim($customer['STATUS_ID']);
			$this->status_desc		= trim($customer['STATUS_DESC']);
			$this->patron_type_id	= trim($customer['PATRON_TYPE_ID']);
			$this->patron_type_desc	= trim($customer['PATRON_TYPE_DESC']);
			$this->cm				= trim($customer['CM']);
			$this->cc_last4			= trim($customer['CC_LAST4']);
			$this->charging			= trim($customer['CHARGING']);
			$this->area_id			= trim($customer['AREA_ID']);
			$this->area_mdesc		= trim($customer['AREA_MDESC']);
			$this->area_ldesc		= trim($customer['AREA_LDESC']);
			$this->suspended		= trim($customer['SUSPENDED']);
			$this->dues				= trim($customer['DUES']);
			$this->exp_date			= trim($customer['EXP_DATE']);
			$this->cc_exp_date		= trim($customer['CC_EXP_DATE']);
			$this->cm_coded_date	= trim($customer['CM_CODED_DATE']);
			$this->cm_copier_can_date	= trim($customer['CM_COPIER_CAN_DATE']);
			$this->cust_comment			= trim($customer['CUST_COMMENT']);
			$this->memb_comment			= trim($customer['MEMB_COMMENT']);
			$this->last_update 		= trim($customer['LAST_UPDATE']);
			$this->update_by		= trim($customer['UPDATE_BY']);
			$this->cle_id			= trim($customer['CLE_ID']);

			$this->new = FALSE;
			return true;
		}
		else
		{
			$this->setError('setCustomer', '1', 'Contact Invalid');
			return false;
		}

	}

	/**
	 * Returns an array of valid titles from table TITLE
	 * @return array
	 */
	static function getTitles()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM TITLE");
		while($ti = $rs->FetchRow())
		{
			$titles[trim($ti['TITLE_ID'])] = $ti;
		}
		return $titles;
	}

	/**
	 * Returns and array of valid statuses from STATUS
	 * Maybe this should be called getStatii? There is no plaural for status!!!!
	 * @return array
	 */
	static function getStatuses()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM STATUS");
		while($sti = $rs->FetchRow())
		{
			$statii[trim($sti['STATUS_ID'])] = $sti;
		}
		return $statii;
	}

	/**
	 * Returns an array of valid patron types from table PATRON_TYPE
	 * @return array
	 */
	static function getPatronTypes()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM PATRON_TYPE");
		while($pt = $rs->FetchRow())
		{
			$patron_types[trim($pt['PATRON_TYPE_ID'])] = $pt;
		}
		return $patron_types;
	}

	/**
	 * Returns an cdbAddr object matching contact
	 * @return object
	 */
	public function getAddress()
	{
		if(!$this->address)
		{
			$rs = self::$db->Execute("SELECT *
								FROM CUSTOMER_ADDRESS
								WHERE trim(CUST_ID)='{$this->cust_id}'
								ORDER BY ADDR_ID DESC");
			$addr_id = array_shift($rs->getRows());
			$this->address = new cdbAddr($addr_id['ADDR_ID'], 'contact', $this->contact_id);
		}
		return $this->address;
	}

	/**
	 * Sets Phones to Contact Object
	 */
	protected function setPhones()
	{
		global $db;
		$rs = self::$db->Execute("SELECT * FROM CUSTOMER_PHONE
									 WHERE trim(CUST_ID)='{$this->cust_id}'");
		while ($p = $rs->FetchRow())
		{
			$this->phones["{$p['PHONE_ID']}"] =
				new cdbPhone($p['PHONE_ID'], 'customer', $this->cust_id);
		}
	}


	/**
	 * Returns Customer Id
	 * @return int
	 */
	public function getCustID() { return $this->cust_id; }

	/**
	 * Returns Barcode
	 * @return string
	 */
	public function getBarcode(){ return $this->barcode; }


	/**
	 * Sets a new bar code
	 * @return bool
	 */
	public function setNewBarcode()
	{
		$barcode = self::$db->GenID('BARCODE_SEQ');;
		$this->setEvent('customer', $this->cust_id, 'R', "Barcode: '{$this->barcode}' -> '$barcode'.");
		$this->barcode = $barcode;
		return true;
	}

	/**
	 * Returns Title ID
	 * @return int
	 */
	public function getTitleId() { return $this->title_id; }


	/**
	 * Returns Title ID Description
	 * @return string
	 */
	public function getTitleDesc() { return $this->title_desc; }


	/**
	 * Sets Title ID
	 * @param int $title_id
	 * @return bool
	 */
	public function setTitle($title_id)
	{
		if(in_array($title_id, array_keys(cdbCustomer::getTitles())))
		{
			$this->setEvent('customer', $this->cust_id, 'N', "Title Changed: '{$this->title_id}' -> '$title_id'.");
			$this->title_id = $title_id;
			return true;
		}
		else
		{
			$this->setError('setTitle', '1', 'Title Type Invalid');
			return false;
		}
	}


	/**
	 * Returns Status ID
	 * @return int
	 */
	public function getStatusId() { return $this->status_id; }


	/**
	 * Returns Status Description
	 * @return string
	 */
	public function getStatusDesc() { return $this->status_desc; }


	/**
	 * Sets Status ID
	 * @param int $status_id
	 * @return bool
	 */
	public function setStatus($status_id)
	{
		if(in_array($status_id, array_keys(cdbCustomer::getStatuses())))
		{
			$this->setEvent('customer', $this->cust_id, 'O', "Status Changed: '{$this->status_id}' -> '$status_id'.");
			$this->status_id = $status_id;
			return true;
		}
		else
		{

			$this->setError('setStatus', '1', 'Status Type Invalid');
			return false;
		}
	}


	/**
	 * Returns Patron Type ID
	 * @return int
	 */
	public function getPatronTypeId() { return $this->patron_type_id; }

	/**
	 * Returns Patron Type Description
	 * @return string
	 */
	public function getPatronTypeDesc() { return $this->patron_type_desc; }

	/**
	 * Sets Patron Type
	 * @param int $patron_type_id
	 * @return bool
	 */
	public function setPatronType($patron_type_id)
	{
		if(in_array($patron_type_id, array_keys(cdbCustomer::getPatronTypes())))
		{
			$this->setEvent('customer', $this->cust_id, 'O', "Patron Type Changed: '{$this->patron_type_id}' -> '$patron_type_id'.");
			$this->patron_type_id = $patron_type_id;
			return true;
		}
		else
		{
			$this->setError('setPatronType', '1', 'Patron Type Invalid');
			return false;
		}
	}


	/**
	 * Returns Credit Mode
	 * @return string 'Y' or 'N'
	 */
	public function getCM() { return $this->cm; }

	/**
	 * Sets Credit Mode
	 * @param string $yn 'Y' or 'N'
	 * @return bool
	 */
	public function setCM($yn)
	{
		switch(strtolower($yn))
		{
			case 'y':
				$this->setEvent('customer', $this->cust_id, 'O',  "CM: '{$this->cm}' -> 'Y'.");
				$this->cm = 'Y';
				return true;
				break;
			case 'n':
				$this->setEvent('customer', $this->cust_id, 'O',  "CM: '{$this->cm}' -> 'N'.");
				$this->cm = 'N';
				return true;
				break;
			default:
				$this->setError('setCM', '1', 'CM Must be Y or N.');
				return false;
				break;
		}
	}

	/**
	 * Returns Charging
	 * @return string 'Y' or 'N'
	 */
	public function getCharging() { return $this->charging; }

	/**
	 * Sets Charging
	 * @param string $yn 'Y' or 'N'
	 * @return bool
	 */
	public function setCharging($yn)
	{
		switch(strtolower($yn))
		{
			case 'y':
				$this->setEvent('customer', $this->cust_id, 'O',  "Charging: '{$this->charging}' -> 'Y'.");
				$this->charging = 'Y';
				return true;
				break;
			case 'n':
				$this->setEvent('customer', $this->cust_id, 'O',  "Charging: '{$this->charging}' -> 'N'.");
				$this->charging = 'N';
				return true;
				break;
			default:
				$this->setError('setCharging', '1', 'Charging Must be Y or N.');
				return false;
				break;
		}
	}

	/**
	 * Returns Area ID
	 * @return int
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
			$this->setEvent('customer', $this->cust_id, 'O', "Area Changed'{$this->area_id}' -> '$area_id'.");
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
	 * Returns Suspended
	 * @return string 'Y' or 'N'
	 */
	public function getSuspended() { return $this->suspended; }

	/**
	 * Sets Charging
	 * @param string $yn 'Y' or 'N'
	 * @return bool
	 */
	public function setSuspended($yn)
	{
		switch(strtolower($yn))
		{
			case 'y':
				$this->setEvent('customer', $this->cust_id, 'O',  "Suspended '{$this->suspended}' -> 'Y'.");
				$this->suspended = 'Y';
				return true;
				break;
			case 'n':
				$this->setEvent('customer', $this->cust_id, 'O',  "Suspended '{$this->suspended}' -> 'N'.");
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
	 * Returns Dues
	 * @return int
	 */
	public function getDues() { return $this->dues; }

	/**
	 * Sets Dues
	 * @param int $dues
	 * @return bool
	 */
	public function setDues($dues)
	{
		if(is_numeric($dues))
		{
			$this->setEvent('customer', $this->cust_id, 'O', "Dues: '{$this->dues}' -> '$dues'.");
			$this->dues = $dues;
			return true;
		}
		else
		{
			$this->setError('setDues', '1', 'Dues must contain only numbers.');
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
			$this->setEvent('customer', $this->cust_id, 'O', "Exp Date Changed '{$this->exp_date}' -> '$y-$m-$d'.");
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
			$this->setEvent('customer', $this->cust_id, 'O',  "Cust Comment '{$this->cust_comment}' -> '$comment'.");
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
			$this->setEvent('customer', $this->cust_id, 'O',  "Cust Comment '{$this->memb_comment}' -> '$comment'.");
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
	 * Returns and array of Allowed CLE ID's
	 * @return array
	 */
	static function getCleIDs()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM CLE_SPECIAL ORDER BY CLE_ID");
		while($cle = $rs->FetchRow())
		{
			$cle_ids[trim($cle['CLE_ID'])] = $cle;
		}
		return $cle_ids;
	}	
	
	/**
	 * Returns Cle ID
	 * @return string
	 */
	public function getCleID() 
	{ 
		return $this->cle_id; 
	}

	/**
	 * Sets CLE ID 
	 * @param $cle_id
	 * @return bool
	 */
	public function setCleID($cle_id)
	{
		if(in_array($cle_id, array_keys(cdbCustomer::getCleIDs())))
		{
			$this->setEvent($this->parent, $this->parent_id, 'A', "CLE ID Changed: '{$this->cle_id}' -> '$cle_id'.");
			$this->cle_id = $cle_id;
			return true;
		}
		else
		{
			$this->setError('setCleID', '1', 'CLE ID Invalid');
			return false;
		}
	}	
	
	/*
	// DEPRICATE? Only 4 entries with this info.
	public function getCCLast4() { return $this->cc_last4; }
	public function setCCLast4($cc4)
	{
		if(strlen($cc4) <= 4)
		{
			$this->setEvent('customer', $this->cust_id, 'O',  "CC Last 4 '{$this->cc_last4}' -> '$cc4'.");
			$this->cc_last4 = $comment;
			return true;
		}
		else
		{
			$this->setError('setCCLast4', '1', 'CC Last 4 Invalid.');
			return false;
		}
	}
	*/

	/**
	 * Search CUSTOMER Table and return Array of results
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
		$valid_columns = array(		'CUST_ID'		=> 	array('int', 'CUSTOMER'),
									'BARCODE'		=> 	array('int', 'CUSTOMER'),
									'COMPANY_ID'	=> 	array('int', 'CUSTOMER'),
								    'ACCOUNT_NBR'	=> 	array('str', 'COMPANY'),
								    'NAME'			=> 	array('str', 'COMPANY'),
								    'FOA'			=> 	array('str', 'CUSTOMER'),
								 	'LNAME' 		=> 	array('str', 'CUSTOMER'),
									'FNAME'			=> 	array('str', 'CUSTOMER'),
									'MNAME'			=>	array('str', 'CUSTOMER'),
									'TITLE_ID'		=> 	array('int', 'CUSTOMER'),
									'EMAIL'			=> 	array('str', 'CUSTOMER'),
									'STATUS_ID'		=> 	array('str', 'CUSTOMER'),
									'PATRON_TYPE_ID'	=> 	array('str', 'CUSTOMER'),
									'CM'			=> 	array('bool', 'CUSTOMER'),
									'CHARGING'		=> 	array('bool', 'CUSTOMER'),
									'AREA_ID'		=> 	array('str', 'CUSTOMER'),
									'SUSPENDED'		=> 	array('bool', 'CUSTOMER'),
									'DUES'			=> 	array('int', 'CUSTOMER'),
									'CLE_ID'		=> 	array('int', 'CUSTOMER'),
									'EXP_DATE'		=> 	array('date', 'CUSTOMER'),
									'LAST_UPDATE' 	=> 	array('date', 'CUSTOMER)',
									'CUST_COMMENT' 	=> 	array('str', 'CUSTOMER'),
									'MEMB_COMMENT' 	=> 	array('str', 'CUSTOMER'),
									'UPDATE_BY'		=>  array('str', 'CUSTOMER'),
									));

		$results = self::genSearch(self::MASTER_QUERY, $valid_columns, 'CUST_ID', $arr_terms, $sort, $sort_order, $andor);
		return $results;
	}

	/**
	 * Returns an array of registered, but not yet commited, events
	 * @return array
	 */
	public function getEvents()
	{
		$events = $this->getEventsFor('customer', $this->cust_id);
		return $events;
	}

	public function commit()
	{
		global $db;
		$customer_vars = array(
								'cud' => $this->cust_id,
								'bar' => $this->barcode,
								'cid' => $this->company_id,
								'foa' => $this->foa,
								'lnm' => $this->lname,
								'fnm' => $this->fname,
								'mnm' => $this->mname,
								'tit' => $this->title_id,
								'eml' => $this->email,
								'sts' => $this->status_id,
								'pti' => $this->patron_type_id,
								'cm'  => $this->cm,
								'cc4' => $this->cc_last4,
								'chg' => $this->charging,
								'aid' => $this->area_id,
								'sus' => $this->suspended,
								'due' => $this->dues,
								'exp' => $this->exp_date,
								'cce' => $this->cc_exp_date,
								'ccm'	=> $this->cust_comment,
								'mcm'	=> $this->memb_comment,
								'cle'	=> $this->cle_id,
								'usr' => $this->currentUser,
							);

		if(!$this->new)
		{
			$query = self::$db->Prepare("UPDATE CUSTOMER
									SET
									BARCODE=:bar,
									FOA=:foa,
									LNAME=:lnm,
									FNAME=:fnm,
									MNAME=:mnm,
									TITLE_ID=:tit,
									EMAIL=:eml,
									STATUS_ID=:sts,
									PATRON_TYPE_ID=:pti,
									CM=:cm,
									CC_LAST4=:cc4,
									CHARGING=:chg,
									AREA_ID=:aid,
									SUSPENDED=:sus,
									DUES=:due,
									EXP_DATE=:exp,
									CC_EXP_DATE=:cce,
									CUST_COMMENT=:ccm,
									MEMB_COMMENT=:mcm,
									CLE_ID=:cle,
									LAST_UPDATE=TO_CHAR(sysdate, 'DD-MM-YY'),
									UPDATE_BY=:usr
									WHERE TRIM(CUST_ID)=:cud");
		}
		else
		{
			$query = self::$db->Prepare("INSERT INTO CUSTOMER
									(CUST_ID, COMPANY_ID, BARCODE,
									FOA, LNAME, FNAME, MNAME, EMAIL, TITLE_ID,
									STATUS_ID, PATRON_TYPE_ID, CM, CC_LAST4,
									CHARGING, AREA_ID, SUSPENDED, DUES,
									EXP_DATE, CC_EXP_DATE, CUST_COMMENT, MEMB_COMMENT, CLE_ID,
									LAST_UPDATE, UPDATE_BY)
									VALUES
									(:cud, :cid, :bar,
									:foa, :lnm, :fnm, :mnm, :eml, :tit,
									:sts, :pti, :cm, :cc4,
									:chg, :aid, :sus, :due,
									:exp, :cce, :ccm, :mcm, :cle,
									TO_CHAR(sysdate, 'DD-MM-YY'), :usr)
								 	");
		}

		$ok = self::$db->Execute($query, $customer_vars);
		if($ok)
		{
			$this->commitEvents('customer');
			$this->setCustomer($this->cust_id);
			return true;
		}
		else
		{
			print_r(self::$db->errorMsg());
			return false;
		}

	}


}