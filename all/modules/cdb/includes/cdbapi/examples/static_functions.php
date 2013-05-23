<?php

require_once("../cdbGlobal.class.php");
require_once("../cdbCompany.class.php");

/*
$search = cdbCustomer::search(array(
									"LNAME" => "Pop",
									), 
									"LNAME", "DESC");
									

print_r($search);
*/


//Company
$area_types = cdbCompany::getAreaTypes();
$categories = cdbCompany::getCategories();
$company_search = cdbCompany::search(array("MAIL_LABEL_NAME" => "Pop",), "MAIL_LABEL_NAME", "DESC");

// Contact
$contact_types = cdbContact::getTypes();
$contact_search = cdbContact::search(array("LNAME" => "Pop",), "LNAME", "DESC");

// Customer
$patron_types = cdbCustomer::getPatronTypes();
$statuses = cdbCustomer::getStatuses();
$titles = cdbCustomer::getTitles();
$customer_search = cdbCustomer::search(array("LNAME" => "Pop",), "LNAME", "DESC");

// Address
$addr_types = cdbAddr::getAddrTypes();

// Phones
$phone_types = cdbPhone::getPhoneTypes();

// Global
$ok = cdb::authenticateUser('bboooo', 'bABO');

// How to check for errors
