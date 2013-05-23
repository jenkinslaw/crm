<?php
require_once('cdbCompany.class.php');
/**
 * Project: Jenkins Law Customer DB
 * File: cdbPerson.class.php
 *
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.0.20090814
 */



/**
 * CDB Master Person Class
 *
 * The is the master class for customers and contacts.
 * All classes that describe people are extended
 * from this.
 *
 * @package JenkinsCustomerDB
 */
abstract class cdbPerson extends customerDB
{
	protected $company_id;
	protected $company;
	protected $foa			= NULL;
	protected $lname		= NULL;
	protected $fname		= NULL;
	protected $mname		= NULL;
	protected $email		= NULL;
	protected $last_update;
	protected $update_by;
	protected $parent;
	protected $parent_id;
	protected $address;
	protected $phones = array();

	/**
	 * Returns a cdbCompany object that matches contact/customer
	 * @return object
	 */
	public function getCompany()
	{
		if(!is_object($this->company))
		{
			$this->company = new cdbCompany($this->company_id, 'COMPANY_ID');
		}

		return $this->company;
	}

	/**
	 * Returns and array of FOAs
	 * @return array
	 */
	static function getFOAs()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$rs = self::$db->Execute("SELECT * FROM FOA");
		while($foa = $rs->FetchRow())
		{
			$foas[trim($foa['FOA'])] = $foa;
		}
		return $foas;
	}

	/**
	 * Returns FOA
	 * @return string
	 */
	public function getFOA() { return $this->foa; }

	/**
	 * Sets FOA
	 * @param string $foa
	 * @return bool
	 */
	public function setFOA($foa)
	{
		if(in_array($foa, array_keys(cdbPerson::getFOAs())))
		{
			$this->setEvent($this->parent, $this->parent_id, 'A', "FOA Changed: '{$this->foa}' -> '$foa'.");
			$this->foa = $foa;
			return true;
		}
		else
		{
			$this->setError('setFOA', '1', 'FOA Invalid');
			return false;
		}
	}

	/**
	 * Returns Last Name
	 * @return string
	 */
	public function getLName() { return $this->lname; }

	/**
	 * Sets Last name
	 * @param string $str
	 * @return bool
	 */
	public function setLName($str)
	{
		if(strlen($str) <= 40)
		{
			$this->setEvent($this->parent, $this->parent_id, 'N',  "Last Name '{$this->lname}' -> '$str'.");
			$this->lname = $str;
			return true;
		}
		else
		{
			$this->setError('setLName', '1', 'Last Name length too long.');
			return false;
		}
	}

	/**
	 * Returns First Name
	 * @return string
	 */
	public function getFName() { return $this->fname; }

	/**
	 * Sets First Name
	 * @param string $str
	 * @return bool
	 */
	public function setFName($str)
	{
		if(strlen($str) <= 32)
		{
			$this->setEvent($this->parent, $this->parent_id, 'N',  "First Name '{$this->fname}' -> '$str'.");
			$this->fname = $str;
			return true;
		}
		else
		{
			$this->setError('setFName', '1', 'First Name length too long.');
			return false;
		}
	}

	/**
	 * Returns Middle Name
	 * @return bool
	 */
	public function getMName() { return $this->mname; }

	/**
	 * Sets Middle Name
	 * @param string $str
	 * @return bool
	 */
	public function setMName($str)
	{
		if(strlen($str) <= 32)
		{
			$this->setEvent($this->parent, $this->parent_id, 'N',  "Middle Name '{$this->mname}' -> '$str'.");
			$this->mname = $str;
			return true;
		}
		else
		{
			$this->setError('setMName', '1', 'Middle Name length too long.');
			return false;
		}
	}

	/**
	 * Returns Email
	 * @return string
	 */
	public function getEmail() { return $this->email; }

	/**
	 * Sets Email
	 * @param $email
	 * @return bool
	 */
	public function setEmail($email)
	{
		if(preg_match('/^[_A-z0-9-]+((\.|\+)[_A-z0-9-]+)*@[A-z0-9-]+(\.[A-z0-9-]+)*(\.[A-z]{2,4})$/',$email)
			&& strlen($email) <= 40)
		{
			$this->setEvent($this->parent, $this->parent_id, 'O',  "Email '{$this->email}' -> '$email'.");
			$this->email = $email;
			return true;
		}
		else
		{
			$this->setError('setEmail', '1', 'Email format invalid.');
			return false;
		}
	}

	public function getLastUpdate() { return $this->last_update; }
	public function getUpdateBy() { return $this->update_by; }

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
	 * Returns the ID of a NEW phone number to be added
	 * @return object
	 */
	public function newPhone()
	{
		$new_phone = new cdbPhone(NULL, $this->parent, $this->parent_id);
		$new_phone_id = $new_phone->getPhoneId();
		$this->phones["$new_phone_id"] = $new_phone;
		return $this->phones["$new_phone_id"];
	}


}
