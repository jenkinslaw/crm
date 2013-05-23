<?php

require_once("../cdbGlobal.class.php");
require_once("../cdbCompany.class.php");

$search_terms = array('CONTACT_TYPE_ID' => 'B',
						'LNAME' => 'Esq');

$find_esq = cdbContact::Search($search_terms);

foreach($find_esq as $e)
{	
	$c = new cdbContact($e['CONTACT_ID']);
	
	$old_lname = $c->getLName();
	
	$new_lname = str_ireplace(', Esq.', '', $old_lname);
	$new_lname = str_ireplace(', Esquire', '', $new_lname);
	$new_lname = str_ireplace(',Esq.', '', $new_lname);
	$new_lname = str_ireplace(',Esquire', '', $new_lname);
	$new_lname = str_ireplace(' Esq.', '', $new_lname);
	$new_lname = str_ireplace(' Esquire', '', $new_lname);
	$new_lname = trim($new_lname);
	
	print("<br>Setting {$c->getContactID()} Lname: '{$old_lname}' to '{$new_lname}'");
	
	$c->setLName($new_lname);
	//$c->commit();	
	
}