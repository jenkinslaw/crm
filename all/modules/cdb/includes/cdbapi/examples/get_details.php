<?php
require_once("../cdbGlobal.class.php");
require_once("../cdbCompany.class.php");

// Just a QnD display function for formatting
function display()
{
	print("<br><b>" . func_get_arg(0) . ": </b>");
	$na = func_num_args();

	for($x = 1; $x < $na; $x++)
	{
		print(" " . func_get_arg($x));
	}
}

function display_events_table($arr)
{
	print("<br><b>Events</b>");
	print('<table>');
	foreach($arr as $i)
	{
		print("<tr>");
		print("<td>{$i['EVENT_ID']}</td>
				<td>{$i['EVENT_TYPE_ID']}</td>
				<td>{$i['MENU_DESCRIPTION']}</td>
				<td>{$i['USER_COMMENTS']}</td>
				<td>{$i['SYS_COMMENTS']}</td>
				<td>{$i['LAST_UPDATE']}</td>
				<td>{$i['UPDATE_BY']}</td>");	
		print("</tr>");	
	}
	print('</table>');
}

print("<br> GETTING COMPANY DETAILS AND REQUISITE SUB OBJECTS <br>");

print("<br> Getting a company... <br>");

$c = new cdbCompany('1013763');

display('Company ID', 	$c->getCompanyID());
display('Account Nbr', 	$c->getAccountNbr());
display('Category:', 	$c->getCategoryID(), 	$c->getCategoryDesc());
display('Area', 		$c->getAreaID(), 		$c->getAreaDesc());
display('# of Attys', 	$c->getNumOfAttys());
display('Exp Date', 	$c->getExpDate());
display('MBS', 			$c->getMBS());
display('Name', 		$c->getCompanyName());
display('Billing Name', $c->getBillingName());
display('Mail Label Name', 	$c->getMailLabelName());

display('Member Comment',	$c->getMembComment());
display('Cust Comment',		$c->getCustComment());

display('Last Update',	$c->getLastUpdate(), 	$c->getUpdateBy());

print("<br>");

$ca = $c->getAddress();
display('Address Type', $ca->getType(), $ca->getTypeDesc());
display('Address', $ca->getAddrLine1(), $ca->getAddrLine2(), $ca->getAddrLine3()
		, $ca->getCity(), $ca->getState(), $ca->getPostalCode(), $ca->getCountry());
display('Address Last Update',	$ca->getLastUpdate(), 	$ca->getUpdateBy());

print("<br>");

display('Email',		$c->getEmail());
display('Website',		$c->getWebsite());

foreach($c->getPhones() as $pid)
{
	$p = $c->getPhone($pid);
	display('Phone', $p->getType(), $p->getTypeDesc(), $p->getPhoneNbr(), $p->getHours(),	
			$p->getLastUpdate(), 	$p->getUpdateBy());
}

display_events_table($c->getEvents());


print("<br><br> Getting Contacts...");

foreach($c->getContacts() as $cid)
{
	print('<br>');
	
	$cc = new cdbContact($cid);
	// Can also do $cc = $c->getContact($cid);
	
	display('Contact ID', 	$cc->getContactID());
	display('Type', 		$cc->getType(), 		$cc->getTypeDesc());
	display('FOA', 			$cc->getFOA());
	display('First Name', 	$cc->getFName());
	display('Middle Name', 	$cc->getMName());
	display('Last Name', 	$cc->getLName());
	display('Email', 		$cc->getEmail());
	
	$ca = $cc->getAddress();
	display('Address Type', $ca->getType(), $ca->getTypeDesc());
	display('Address', $ca->getAddrLine1(), $ca->getAddrLine2(), $ca->getAddrLine3()
			, $ca->getCity(), $ca->getState(), $ca->getPostalCode(), $ca->getCountry());	
	display('Address Last Update',	$ca->getLastUpdate(), 	$ca->getUpdateBy());
	
	foreach($cc->getPhones() as $pid)
	{
		$p = $cc->getPhone($pid);
		display('Phone', $p->getType(), $p->getTypeDesc(), $p->getPhoneNbr(), $p->getHours(),	
			$p->getLastUpdate(), 	$p->getUpdateBy());
	}	
	
	display_events_table($cc->getEvents());
	
}

print("<br><br> Getting Customers/Patrons...");

foreach($c->getCustomers() as $cid)
{
	print('<br>');
	
	$cc = new cdbCustomer($cid);
	// Can also do $cc = $c->getContact($cid);
	
	display('Contact ID', 	$cc->getCustID());
	display('Barcode', 		$cc->getBarcode());
	display('Status', 		$cc->getStatusID(), 	$cc->getStatusDesc());
	display('Patron Type',	$cc->getPatronTypeID(), $cc->getPatronTypeDesc());
	display('Area', 		$cc->getAreaID(), 		$cc->getAreaDesc());
	display('FOA', 			$cc->getFOA());
	display('First Name', 	$cc->getFName());
	display('Middle Name', 	$cc->getMName());
	display('Last Name', 	$cc->getLName());
	display('Title', 		$cc->getTitleID(),	$cc->getTitleDesc());
	display('Email', 		$cc->getEmail());
	
	display('CM',			$cc->getCM());
	display('Charging',		$cc->getCharging());
	display('Suspended',	$cc->getSuspended());
	display('Dues',			$cc->getDues());
	display('ExpDate',		$cc->getExpDate());
	
	display('Member Comment',	$cc->getMembComment());
	display('Cust Comment',		$cc->getCustComment());	
	
	display('Last Update',	$cc->getLastUpdate(), 	$cc->getUpdateBy());
	
	$ca = $cc->getAddress();
	display('Address Type', $ca->getType(), $ca->getTypeDesc());
	display('Address', $ca->getAddrLine1(), $ca->getAddrLine2(), $ca->getAddrLine3()
			, $ca->getCity(), $ca->getState(), $ca->getPostalCode(), $ca->getCountry());
	display('Address Last Update',	$ca->getLastUpdate(), 	$ca->getUpdateBy());	
	
	foreach($cc->getPhones() as $pid)
	{
		$p = $cc->getPhone($pid);
		display('Phone', $p->getType(), $p->getTypeDesc(), $p->getPhoneNbr(), $p->getHours(),	
			$p->getLastUpdate(), 	$p->getUpdateBy());
	}	
	
	display_events_table($cc->getEvents());
	
}
