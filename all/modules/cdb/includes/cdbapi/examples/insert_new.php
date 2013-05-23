<?php

require_once("../cdbGlobal.class.php");
require_once("../cdbCompany.class.php");

print("<br> CREATING A NEW COMPANY AND REQUISITE SUB OBJECTS <br>");

print("<br> Creating a new company...");

$cdb = cdb::getCDB();
$cdb->setUser('asather');

$c = new cdbCompany();
$c->setCompanyName("Shadow Grasshopper Law");
$c->setCategory('1');
$c->setArea('L');
$c->setExpDate('12', '21', '2009');
$c->setMBS('Y');
$c->setSuspended('N');
$c->setProbation('Y');
$c->setEmail('gpophaly@jenkinslaw.org');
$c->setWebsite('www.jenkinslaw.org');
$c->setCustComment('AWESOME!');
$c->setMembComment('RADICAL DUDE!');
// BUG ORA-02291: integrity constraint (JLL.CO_EVENT_COMPANY_FK) violated - parent key not found 
// But all data is there?! The order of commit()'s is important!
$c->commit();

print("<br> Setting new company's address...");

$ca = $c->getAddress();
$ca->setType('8');
$ca->setAddrLine1('One Lawn Way');
$ca->setAddrLine2('Grass Patch 18');
$ca->setAddrLine3('Grass Blade 42 ');
$ca->setCity('Hopper Pond');
$ca->setState('PA');
$ca->setPostalCode('19147');
$ca->setCountry('USA');
$ca->commit();

print("<br> Setting new company's phones...");

$cp1 = $c->newPhone();
$cp1->setType('O');
$cp1->setPhoneNbr('111-111-1111');
$cp1->commit();

$cp2 = $c->newPhone();
$cp2->setType('F');
$cp2->setPhoneNbr('111-111-1112');
$cp2->commit();

print("<br> Go check out company id: ". $c->getCompanyID());

print("<br><br> Setting new company's billing contact...");

$b = new cdbContact(NULL, $c->getCompanyId());
$b->setType('B');
$b->setFOA('Dr.');
$b->setFName('Andrew');
$b->setMName('Jay');
$b->setLName('Sather');
$b->setEmail('asather@jenkinslaw.org');
$b->commit();

print("<br> Setting new billing contacts address...");
$ba = $b->getAddress();
$ba->setType('4');
$ba->setAddrLine1('62 Brookshire Terrace');
$ba->setCity('Philadelphia');
$ba->setState('PA');
$ba->setPostalCode('19116');
$ba->setCountry('USA');
$ba->commit();

print("<br> Setting new billing contacts phones...");
$bp1 = $b->newPhone();
$bp1->setType('D');
$bp1->setPhoneNbr('222-222-2221');
$bp1->commit();

$bp2 = $b->newPhone();
$bp2->setType('O'); // CANNOT USE 'C' to add cell phone, must be 'O'
$bp2->setPhoneNbr('222-222-2222');
$bp2->commit();

print("<br> Go check out billing contact id: ". $b->getContactID());


print("<br><br> Setting new company's membership contact...");

$m = new cdbContact(NULL, $c->getCompanyId());
$m->setType('M');
$m->setFOA('Rev.');
$m->setFName('Gaurav');
$m->setMName('M');
$m->setLName('Pophaly');
$m->setEmail('gpop@jenkinslaw.org');
$m->commit();

print("<br> Setting new membership contacts address...");
$ma = $m->getAddress();
$ma->setType('2');
$ma->setAddrLine1('507 S 9th St');
$ma->setAddrLine2('Apt 2');
$ma->setCity('Philadelphia');
$ma->setState('PA');
$ma->setPostalCode('19147');
$ma->setCountry('USA');
$ma->commit();

print("<br> Setting new membership contacts phones...");
$mp1 = $m->newPhone();
$mp1->setType('M');
$mp1->setPhoneNbr('333-333-3331');
$mp1->commit();

$mp2 = $m->newPhone();
$mp2->setType('H'); // CANNOT USE 'C' to add cell phone, must be 'O'
$mp2->setPhoneNbr('333-333-3332');
$mp2->commit();

$mp2 = $m->newPhone();
$mp2->setType('F'); // CANNOT USE 'C' to add cell phone, must be 'O'
$mp2->setPhoneNbr('333-333-3333');
$mp2->commit();

print("<br> Go check out mebership contact id: ". $m->getContactID());

print("<br><br> Setting new company's customer/patron (attorney)...");
$p = new cdbCustomer(NULL, $c->getCompanyId());
//$p->setFOA('Mr.');
$p->setFName('Barack');
$p->setMName('H');
$p->setLName('Obama');
$p->setTitle('Esq.');
$p->setEmail('bobamba@whitehouse.gov');
$p->setStatus('1');
$p->setPatronType('001');
$p->setCM('Y');
$p->setCharging('Y');
$p->setSuspended('N');
$p->setDues('255');
$p->setExpDate("01", "20", "2012");
$p->setCustComment("No we can't.");
$p->setMembComment('Yes we can.');
$p->commit();

print("<br> Setting new customer's address...");
$pa = $p->getAddress();
$pa->setType('1');
$pa->setAddrLine1('1600 Pennsylvania Ave');
$pa->setAddrLine2('NW');
$pa->setAddrLine3('The White House');
$pa->setCity('Washington');
$pa->setState('DC');
$pa->setPostalCode('20500-0004');
$pa->setCountry('USA');
$pa->commit();

print("<br> Setting new customers phones...");
$pp1 = $p->newPhone();
$pp1->setType('D');
$pp1->setPhoneNbr('444-444-4441');
$pp1->commit();

$pp2 = $p->newPhone();
$pp2->setType('H'); // CANNOT USE 'C' to add cell phone, must be 'O'
$pp2->setPhoneNbr('444-444-4442');
$pp2->commit();

print("<br> Go check out customer id: ". $p->getCustID());