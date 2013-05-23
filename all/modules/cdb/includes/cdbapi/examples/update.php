<?php
require_once("../cdbGlobal.class.php");
require_once("../cdbCompany.class.php");

print("<br> CREATING A NEW COMPANY AND REQUISITE SUB OBJECTS <br>");

print("<br> Updating company...");

$cdb = cdb::getCDB();
$cdb->setUser('www');

$c = new cdbCompany('1013763');
$c->setCompanyName("The Law Offices of Shadow Grasshopper and Associates");
$c->setCategory('2');
$c->setArea('R');
$c->setExpDate('09', '16', '2009');
$c->setMBS('N');
$c->setSuspended('Y');
$c->setEmail('gpop@jenkinslaw.org');
$c->setWebsite('http://www.jenkinslaw.org');
$c->setCustComment('');
$c->setMembComment('');
$c->commit();

print("<br> Updating company's address...");

$ca = $c->getAddress();
$ca->setType('8');
$ca->setAddrLine1('Two Lawn Patch');
$ca->setAddrLine2('Suite 42');
$ca->setAddrLine3('');
$ca->setCity('Grassville');
$ca->setState('NJ');
$ca->setPostalCode('08824');
$ca->setCountry('USA');
$ca->commit();

print("<br> Updating company's phones...");

$pids = $c->getPhones();
foreach($pids as $pid)
{
	$p = $c->getPhone($pid);
	$p->setPhoneNbr('999-999-9999');
	$p->commit();
}

print("<br> Go check out company id: ". $c->getCompanyID());

print("<br><br> Updating company's billing contact...");

$b = new cdbContact('4588');
$b->setType('B');
$b->setFOA('Ms.');
$b->setFName('Andy');
$b->setMName('J');
$b->setLName('Rather');
$b->setEmail('asa@jenkinslaw.org');
$b->commit();

print("<br> Updating billing contacts address...");
$ba = $b->getAddress();
$ba->setType('4');
$ba->setAddrLine1('62 Brookshire Terrace BBBB');
$ba->setAddrLine2('Apt 48095');
$ba->setCity('University City');
$ba->setState('NY');
$ba->setPostalCode('222222');
$ba->setCountry('USA');
$ba->commit();

print("<br> Setting new billing contacts phones...");
$pids = $b->getPhones();
foreach($pids as $pid)
{
	$p = $b->getPhone($pid);
	$p->setPhoneNbr('999-999-9999');
	$p->commit();
}

print("<br> Go check out billing contact id: ". $b->getContactID());


print("<br><br> Updating company's membership contact...");

$m = new cdbContact('4589');
$m->setType('M');
$m->setFOA('Hon.');
$m->setFName('G');
$m->setMName('Money');
$m->setLName('Popdawg');
$m->setEmail('gmoneypopdog@jenkinslaw.org');
$m->commit();

print("<br> Updating membership contacts address...");
$ma = $m->getAddress();
$ma->setType('2');
$ma->setAddrLine1('448 Julia St');
$ma->setAddrLine2('Apt 311');
$ma->setCity('New Orleans');
$ma->setState('LA');
$ma->setPostalCode('91068');
$ma->setCountry('USA');
$ma->commit();

print("<br> Updating membership contacts phones...");
$pids = $m->getPhones();
foreach($pids as $pid)
{
	$p = $m->getPhone($pid);
	$p->setPhoneNbr('999-999-9999');
	$p->commit();
}

print("<br> Go check out mebership contact id: ". $m->getContactID());

print("<br><br> Setting new company's customer/patron (attorney)...");
$p = new cdbCustomer('30757');
$p->setFOA('Hon.');
$p->setFName('Kcarab');
$p->setMName('The Pres');
$p->setLName('amabo');
$p->setTitle('Para.');
$p->setEmail('thepresident@whitehouse.gov');
$p->setStatus('2');
$p->setPatronType('011');
$p->setCM('N');
$p->setCharging('N');
$p->setSuspended('Y');
$p->setDues('999');
$p->setExpDate("09", "16", "2012");
$p->setCustComment("");
$p->setMembComment('');
$p->commit();

print("<br> Updating customer's address...");
$pa = $p->getAddress();
$pa->setType('1');
$pa->setAddrLine1('1604 Pennsylvania Ave');
$pa->setAddrLine2('NE');
$pa->setAddrLine3('The Off-White House');
$pa->setCity('Honolulu');
$pa->setState('HA');
$pa->setPostalCode('121234');
$pa->setCountry('USA');
$pa->commit();

print("<br> Updating customers phones...");
$pids = $p->getPhones();
foreach($pids as $pid)
{
	$pp = $p->getPhone($pid);
	$pp->setPhoneNbr('999-999-9999');
	$pp->commit();
}

print("<br> Go check out customer id: ". $p->getCustID());