<?php
require_once("cdbGlobal.class.php");
/**
 * Project: Jenkins Law Customer DB
 * File: cdb.class.php
 *  
 * @author Gaurav Pophaly <gpophaly@jenkinslaw.org>
 * @package JenkinsCustomerDB
 * @version 1.1.20090915
 */


/**
 * CDB Master Class
 *
 * Provides basic functionality required to use anything
 * with Jenkin Law's abhorrent Customer DB Database.
 * All classes MUST extend from this one.
 * 
 * @package JenkinsCustomerDB
 */
abstract class customerDB
{
	protected $currentUser = "www";
	protected $cdbErrors = array();
	protected $cdbEvents = array();
	protected static $eventTypes;
	protected static $cdb;
	protected static $db;
	
	function __construct()
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		$this->currentUser = self::$cdb->getUser();
	}
		
	/**
	* Use to set an error for a function that can later be retrived on failures.
	* @param string $param Usually the name of the function
	* @param int $ekey A Unique key for the error
	* @param string $value Error Description
	* @return void
	*/
	protected function setError($param, $ekey, $value)
	{
		//trigger_error("setError: {$param} - {$ekey} - {$value}", E_USER_WARNING);
		$param = strtolower($param);
		$this->cdbErrors["{$param}"]["{$ekey}"] = $value; 
	}
	
	/**
	* Use to get an error or errors for a failed function call.
	* For example, if class->foo() returns false, you can get the error by calling class->getError('foo')
	* @param string $param Usually the name of the function
	* @param string $returnWhat Either 'ALL' for both errors and keys, 'EKEY' for only keys, 'EMSG' for only error messages
	* @return array
	*/
	public function getError($param, $returnWhat = 'ALL')
	{
		$param = strtolower($param);
		if(is_array($this->cdbErrors["{$param}"]))
		{
			switch($returnWhat)
			{
				case 'ALL':
					$return_error = $this->cdbErrors["{$param}"];
				break;	
				case 'EKEY':
					$return_error = array_keys($this->cdbErrors["{$param}"]);
				break;
				case 'EMSG':
					$return_error = array_values($this->cdbErrors["{$param}"]);
				break;	
			}
			
			if(sizeof($return_error) == 1)
			{
				$return_error = array_shift($return_error);
			}
			
			return $return_error;
			
		}
		else
		{
			return FALSE;	
		}
	}
		
	/**
	 * Returns an array of all possible event types from EVENT_TYPE table
	 * @return array
	 */
	protected function getEventTypes()
	{
		if(sizeof(self::$eventTypes) == 0)
		{
			$rs = self::$db->Execute("SELECT * FROM EVENT_TYPE");
			while($et = $rs->FetchRow())
			{
				self::$eventTypes["{$et['EVENT_TYPE_ID']}"] = $et;
			}
		}
		return self::$eventTypes;
	}	
		
	/**
	 * Inserts event into event log
	 * @param string $module 			Module or Class, ie. 'company', 'contact' or 'customer' 
	 * @param string $module_key 		ID of module or class. ie. the company_id or contact_id, etc
	 * @param string $etype			Type of Event as defined in getEventTypes();
	 * @param string $sys_comments		Comments provided by the class system
	 * @param string $usr_comments		Comments provided by the user
	 * @return bool
	 */
	public function setEvent($module, $module_key, $etype = 'O', $sys_comments = "", $usr_comments = "")
	{
		$module = strtolower($module);
		if($this->eventMatchTable($module) && in_array($etype, array_keys($this->getEventTypes())))
		{
			$this->cdbEvents["$module"]["$module_key"]["$etype"]['sys_comments'] .= "\n" . $sys_comments;
			$this->cdbEvents["$module"]["$module_key"]["$etype"]['usr_comments'] .= "\n" . $usr_comments;
			return true;
		}
		else
		{
			$this->setError('setEvent', 1, 'Not a valid event module or type.');
			return false;
		}
		
	}
	
	/**
	 * Returns the table name used to match events based on class/module
	 * @param string $module Module or Class, ie. 'company', 'contact' or 'customer' 
	 * @return string
	 */
	protected function eventMatchTable($module)
	{
		$module = strtolower($module);
		$valid_modules = array(
						"company" => "COMPANY_EVENT",
						"contact" => "CONTACT_EVENT",
						"customer" => "CUSTOMER_EVENT",
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
	 * Returns the id column name for the table used to match events
	 * @param string $module Module or Class, ie. 'company', 'contact' or 'customer' 
	 * @return string
	 */
	protected function matchCol($module)
	{
		$module = strtolower($module);
		$valid_modules = array(
						"company" => "COMPANY_ID",
						"contact" => "CONTACT_ID",
						"customer" => "CUST_ID",
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
	 * Inserts events set by setEvent() into the table
	 * @param string $module Module or Class, ie. 'company', 'contact' or 'customer' 
	 * @return bool
	 */
	protected function commitEvents($module)
	{
		$module = strtolower($module);
		
		$query = self::$db->Prepare("INSERT INTO EVENT_LOG 
			(EVENT_ID, EVENT_TYPE_ID, USER_COMMENTS, SYS_COMMENTS, UPDATE_BY)
			VALUES
			(:eid, :et, :uc, :sc, :ub)
		 	");
		
		if(sizeof($this->cdbEvents["{$module}"]) > 0) 
		{
			foreach($this->cdbEvents["{$module}"] as $mod_key => $events)
			{ 
				foreach($events as $etype => $event)
				{
					$event_id = self::$db->GenID('EVENT_LOG_SEQ');
					$event_vals = array(
										'eid' => $event_id,
										'et' => $etype,
										'uc' => trim($event['usr_comments']),
										'sc' => trim($event['sys_comments']),
										'ub' => $this->currentUser,
										);
										
										
					if(self::$db->Execute($query, $event_vals))
					{
						$event_table = $this->eventMatchTable($module);
						$event_col = $this->matchCol($module);
						$ok = self::$db->Execute("INSERT INTO {$event_table} 
											($event_col, EVENT_ID) 
											values ('$mod_key', '$event_id')");
						if($ok)
						{
							unset($this->cdbEvents["{$module}"]["{$mod_key}"]["{$etype}"]);
						}
						else
						{
							print("$etype: ");
							print_r(self::$db->errorMsg());						
						}
		
					}
					
				}
			}
		}
		
	}

	/**
	 * Discards registered events before inputted into the EVENT_LOG
	 * @param string $module Module or Class, ie. 'company', 'contact' or 'customer' 
	 */
	protected function abandonEvents($module)
	{
		unset($this->cdbEvents["{$module}"]);
	}
	
	/**
	 * Gets events from EVENT_LOG
	 * @param string $module Module or Class, ie. 'company', 'contact' or 'customer' 
	 * @param int $module_id The id from the key colum from module table
	 * @return unknown_type
	 */
	public function getEventsFor($module, $module_id)
	{
		$module = strtolower($module);	
		$event_table = $this->eventMatchTable($module);
		$event_col = $this->matchCol($module);
		$eq = self::$db->Prepare("SELECT EVENT_LOG.*, EVENT_TYPE.MENU_DESCRIPTION, EVENT_TYPE.LONG_DESCRIPTION  
								FROM EVENT_LOG, {$event_table}, EVENT_TYPE
								WHERE 
								EVENT_LOG.EVENT_TYPE_ID = EVENT_TYPE.EVENT_TYPE_ID AND
								EVENT_LOG.EVENT_ID = {$event_table}.event_id
								AND {$event_table}.{$event_col} = :mid");
		$rs = self::$db->Execute($eq, array('mid' => $module_id));
		
		while($e = $rs->FetchRow())
		{
			$events["{$e['EVENT_ID']}"] = $e;
		}
		return $events;
	}
	
	/**
	 * Returns the WHERE portion of a query
	 * @param array $valid_cols Array of valid columns. i.e.: array(COLUMN_NAME => array(COLUMN_TYPE, TABLE_NAME)); Valid column types are 'str', 'int', 'date' and 'bool('Y' or 'N')'
	 * @param array $arr_terms Array of search terms. i.e.: array(COLUMN_NAME => TERM); 
	 * @param str $andor Bind the where terms by 'AND' or 'OR'
	 * @return string
	 */
	protected static function whereQ($valid_cols, $arr_terms, $andor = 'AND')
	{
		if($andor == "OR") { $andor = "OR";	}
		else { $andor = "AND"; }
		
		foreach($arr_terms as $col => $term)
		{
			$col = strtoupper($col);
			if(in_array($col, array_keys($valid_cols)))
			{
				$col_type = $valid_cols["{$col}"];
				switch($col_type[0])
				{
					case 'str':
						$where .= " $andor {$col_type[1]}.{$col} LIKE concat('%', concat(:{$col}, '%'))";
						break;
					case 'char':	
						if(is_array($term) && sizeof($term) > 0)
						{
							$where .= " $andor (";
							foreach($term as $ot)
							{
								if(strlen($ot) == 1)
								{
									$where .= "{$col_type[1]}.{$col} = '$ot' OR ";
								}
							}
							$where = substr($where, 0, -3);
							$where .= " )";
						}
						elseif(strlen($term) == 1)
						{
							$where .= " $andor {$col_type[1]}.{$col} = '{$term}'";
						}
						break;
					case 'int':
						if(is_array($term))
						{
							if(is_numeric($term[0]) && is_numeric($term[1]))
							{
								$where .= " $andor {$col_type[1]}.{$col} BETWEEN {$term[0]} AND {$term[1]}";
							}
						}
						else
						{
							$where .= " $andor {$col_type[1]}.{$col} LIKE concat('%', concat(:{$col}, '%'))";	
						}
						break;
					case 'date':
						if(is_array($term))
						{
							$date1 = date('Y-m-d', strtotime($term[0]));
							$date2 = date('Y-m-d', strtotime($term[1]));
							$where .= " $andor {$col_type[1]}.{$col} BETWEEN to_date('{$date1}', 'YYYY-MM-DD') 
										AND to_date('{$date2}', 'YYYY-MM-DD')";
						}
						else
						{
							$date1 = date('Y-m-d', strtotime($term));
							$where .= " $andor {$col_type[1]}.{$col} LIKE to_date('{$date1}', 'YYYY-MM-DD')";
						}
						break;
					case 'bool':
						if($term == 'Y' || $term == 'N')
						{
							$where .= " $andor {$col_type[1]}.{$col} = '{$term}'";	
						}
						break;
				}
			}
		}
		
		//print($where);
		$where = substr($where, 4);
		return $where;
	}
	
	/**
	 * Returns the ORDER BY portion of a query
	 * @param array $valid_cols Array of valid columns. i.e.: array(COLUMN_NAME => array(COLUMN_TYPE, TABLE_NAME)); Valid column types are 'str', 'int', 'date' and 'bool('Y' or 'N')'
	 * @param string $sort Column name to sort by
	 * @param string $sort_order Ascending: 'ASC' or descending: 'DESC'
	 * @return string
	 */
	protected static function orderQ($valid_cols, $sort = NULL, $sort_order = "ASC")
	{
		if($sort_order == "DESC") { $sort_order = "DESC";	}
		else { $sort_order = "ASC"; }
		
		if(in_array($sort, array_keys($valid_cols)) && $sort_order != NULL)
		{
			$sortby = "ORDER BY {$sort} {$sort_order}";
			return $sortby;
		}
		else
		{
			return "";
		}
		
	}
	
	/**
	 * Returns the results of a query search
	 * @param string $query The general query
	 * @param array $valid_columns Array of valid columns. i.e.: array(COLUMN_NAME => array(COLUMN_TYPE, TABLE_NAME)); Valid column types are 'str', 'int', 'date' and 'bool('Y' or 'N')'
	 * @param string $keycol Primary key column of query
	 * @param array $arr_terms Array of search terms. i.e.: array(COLUMN_NAME => TERM); 
	 * @param string $sort Column name to sort by
	 * @param string $sort_order Column name to sort by
	 * @param string $andor Ascending: 'ASC' or descending: 'DESC'
	 * @return array
	 */
	protected static function genSearch($query, $valid_columns, $keycol, $arr_terms, $sort = NULL, $sort_order = "ASC", $andor = 'AND')
	{
		self::$cdb = cdb::getCDB();
		self::$db = self::$cdb->getDB();
		if(sizeof($arr_terms) > 0)
		{
			$where = self::WhereQ($valid_columns, $arr_terms, $andor);
			$sort = self::orderQ($valid_columns, $sort, $sort_order);
			
			$query = $query . " WHERE " . $where . " " . $sort;
			//print($query . "<br><br>\n\n");
			$query = self::$db->Prepare($query);
			
			$rs = self::$db->Execute($query, $arr_terms);

			if(sizeof($rs) > 0)
			{			
				foreach($rs as $k => $r)
				{
					$results["{$r[$keycol]}"] = $r;
				}
			}
			else
			{
				$results = array();
			}
			return $results;
		}
		else
		{		
			return FALSE;
		}
	}
}
