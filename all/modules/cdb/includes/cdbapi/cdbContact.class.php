<?php
require_once('cdb.class.php');
require_once('cdbPerson.class.php');
/**
 * Project: Jenkins Law Customer DB
 * File: cdbContact.class.php
 *  
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.1.20091013
 * 
 */



/**
 * CDB Contact Object
 * 
 * Provides methods to access and modify the CONTACT 
 * table and related data.
 * 
 * @package JenkinsCustomerDB
 */
class cdbContact extends cdbPerson
{
	protected $new = FALSE;
	protected $contact_id;
	protected $contact_type_id	= NULL;
	protected $type_desc;
	protected $parent = "contact";
	
	const MASTER_QUERY = "SELECT CONTACT.*, CONTACT_TYPE.*, COMPANY.NAME, COMPANY.ACCOUNT_NBR
									FROM CONTACT
									LEFT OUTER JOIN CONTACT_TYPE
										ON CONTACT_TYPE.CONTACT_TYPE_ID = CONTACT.CONTACT_TYPE_ID
									LEFT OUTER JOIN COMPANY
										ON CONTACT.COMPANY_ID = COMPANY.COMPANY_ID";	
	
	/**
	 * CONSTRUCT!
	 * @param int $contact_id Contact ID
	 * @param int $company_id Company ID
	 */
	function __construct($contact_id = NULL, $company_id = NULL)
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$this->currentUser = self::$cdb->getUser();
		$this->parent = "CONTACT";
		if($contact_id != NULL)
		{
			$this->setContact($contact_id);
			$this->parent_id = $this->contact_id;
			$this->new = FALSE;
		}
		else
		{
			$this->company_id = $company_id;
			$this->contact_id = self::$db->GenID('CONTACT_ID_SEQ');
			$this->parent_id = $this->contact_id;
			$this->address = new cdbAddr(NULL, 'contact', $this->contact_id);		
			$this->new = TRUE;
		}
	}	
	
	/**
	 * Populates Contact Object
	 * @param int $contact_id Contact ID
	 * @return bool
	 */
	protected function setContact($contact_id)
	{	
		$query = self::$db->Prepare(self::MASTER_QUERY . " WHERE trim(CONTACT_ID)=:cid");	
		$rs = self::$db->Execute($query, array('cid' => "$contact_id"));
	
		if($rs->RecordCount() == 1)
		{
			$contact = $rs->getRows();
			$contact = array_shift($contact);
			
			$this->contact_id		= trim($contact['CONTACT_ID']);
			$this->company_id 		= trim($contact['COMPANY_ID']);
			$this->contact_type_id	= trim($contact['CONTACT_TYPE_ID']);
			$this->type_desc		= trim($contact['MENU_DESCRIPTION']);
			$this->foa		 		= trim($contact['FOA']);
			$this->lname	 		= trim($contact['LNAME']);
			$this->fname	 		= trim($contact['FNAME']);
			$this->mname 			= trim($contact['MNAME']);
			$this->email 			= trim($contact['EMAIL']);
			$this->last_update 		= trim($contact['LAST_UPDATE']);
			$this->update_by		= trim($contact['UPDATE_BY']);	
			
			$this->setPhones();

			$this->new = FALSE;
			return true;
		}
		else
		{
			$this->setError('setContact', '1', 'Contact Invalid');	
			return false;
		}			
		
	}
	
	/**
	 * Returns an array of phone types
	 * @return array
	 */
	static function getTypes()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM CONTACT_TYPE");
		while($ct = $rs->FetchRow())
		{
			$contact_types["{$ct['CONTACT_TYPE_ID']}"] = $ct;
		}
		return $contact_types;	
	}
	
	/**
	 * Returns contact_id
	 * @return int
	 */
	public function getContactID() { return $this->contact_id; }
	
	/**
	 * Returns contact type
	 * @return string
	 */
	public function getType() { return $this->contact_type_id; }
	
	/**
	 * Sets Contact Type
	 * @param string $contact_type 
	 * @return bool
	 */
	public function setType($contact_type)
	{
		if(in_array($contact_type, array_keys(cdbContact::getTypes())))
		{
			$this->setEvent('contact', $this->contact_id, 'O',  
				"Contact Type Changed: '{$this->contact_type_id}' -> '$contact_type'.");
			$this->contact_type_id = $contact_type;
			return true;
		}
		else
		{
			$this->setError('setType', '1', 'Contact Type Invalid');	
			return false;
		}
	}	
	
	/**
	 * Returns Contact Type Description
	 * @return string
	 */
	public function getTypeDesc() { return $this->type_desc; }
	
	/**
	 * Returns cdbAddr Object matching contact
	 * @return object
	 */
	public function getAddress()
	{
		if(!$this->address)
		{
			$rs = self::$db->Execute("SELECT * 
								FROM CONTACT_ADDRESS 
								WHERE trim(CONTACT_ID)='{$this->contact_id}' 
								ORDER BY ADDR_ID DESC");
			$addr_id = array_shift($rs->getRows());
			if(strlen($addr_id) > 0)
			{
				$this->address = new cdbAddr($addr_id['ADDR_ID'], 'contact', $this->contact_id);
			}
			else
			{
				$this->address = $this->getCompany()->getAddress();
			}
		}
		return $this->address;
	}	

	/**
	 * Sets Phones to Contact Object
	 */
	protected function setPhones()
	{
		$rs = self::$db->Execute("SELECT * FROM CONTACT_PHONE 
									 WHERE trim(CONTACT_ID)='{$this->contact_id}'");	
		while ($p = $rs->FetchRow())
		{
			$this->phones["{$p['PHONE_ID']}"] = 
				new cdbPhone($p['PHONE_ID'], 'contact', $this->contact_id);
		}		
	}
	
	/**
	 * Search CONTACT Table and return Array of results 
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
		$valid_columns = array(		'CONTACT_ID'	=> 	array('int', 'CONTACT'),
									'COMPANY_ID'	=> 	array('int', 'CONTACT'), 
								    'ACCOUNT_NBR'	=> 	array('str', 'COMPANY'), 
								    'NAME'			=> 	array('str', 'COMPANY'), 
								    'CONTACT_TYPE_ID'	=> 	array('str', 'CONTACT'), 
								    'FOA'			=> 	array('str', 'CONTACT'),
								 	'LNAME' 		=> 	array('str', 'CONTACT'),
									'FNAME'			=> 	array('str', 'CONTACT'),
									'MNAME'			=>	array('str', 'CONTACT'),
									'EMAIL'			=> 	array('str', 'CONTACT'),
									'LAST_UPDATE' 	=> 	array('date', 'CONTACT)',
									'UPDATE_BY'		=>  array('str', 'CONTACT'),
									));

		$results = self::genSearch(self::MASTER_QUERY, $valid_columns, 'CONTACT_ID', $arr_terms, $sort, $sort_order, $andor);
		return $results;
	}
	
	/**
	 * Returns an array of registered, but not yet commited, events
	 * @return array
	 */
	public function getEvents()
	{
		$events = $this->getEventsFor('contact', $this->contact_id);
		return $events;
	}	
	
	/**
	 * Commits modified CONTACT data to table and logs results
	 * @return bool
	 */
	public function commit()
	{
		$contact_vars = array(
								'ctd' => $this->contact_id,
								'cid' => $this->company_id,
								'cti' => $this->contact_type_id,
								'foa' => $this->foa,
								'lnm' => $this->lname,
								'fnm' => $this->fname,
								'mnm' => $this->mname,
								'eml' => $this->email,
								'usr'	=> $this->currentUser,
							);
							
		if(!$this->new)
		{
			$query = self::$db->Prepare("UPDATE CONTACT
									SET 
									CONTACT_TYPE_ID=:cti,
									FOA=:foa,
									LNAME=:lnm,
									FNAME=:fnm,
									MNAME=:mnm,
									EMAIL=:eml,
									LAST_UPDATE=TO_CHAR(sysdate, 'DD-MM-YY'),
									UPDATE_BY=:usr									
									WHERE TRIM(CONTACT_ID)=:ctd");
		}
		else
		{		
			$query = self::$db->Prepare("INSERT INTO CONTACT 
									(CONTACT_ID, COMPANY_ID, CONTACT_TYPE_ID,
									FOA, LNAME, FNAME, MNAME, EMAIL,
									LAST_UPDATE, UPDATE_BY)
									VALUES
									(:ctd, :cid, :cti, 
									:foa, :lnm, :fnm, :mnm, :eml,
									TO_CHAR(sysdate, 'DD-MM-YY'), :usr)
								 	");	
			$this->address->commit();
		}
		
		$ok = self::$db->Execute($query, $contact_vars);
		if($ok)
		{
			$this->commitEvents('contact');
			$this->setContact($this->contact_id);
			return true;
		}
		else
		{
			print_r(self::$db->errorMsg());
			return false;
		}		
							
							
	}
	
}