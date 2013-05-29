<?php

/**
 * @file
 * person.inc
 *
 * Migration tasks for person entity.
 */

/**
 * TIP: An example of importing from an XML feed where both the id and the
 * data to import are in the same file.  The id is a part of the data.  See
 * the file in the xml directory - producers.xml which contains all IDs and
 * producer data for this example.
 *
 * Note that, if basing a migration on an XML source, you need to derive it
 * from XMLMigration instead of Migration.
 */
class Person extends XMLMigration {
  public function __construct() {
    parent::__construct(MigrateGroup::getInstance('wine', array('default')));
    $this->description = t('XML feed (multi items) of wine producers of the world');
    $this->dependencies = array('WineRegion', 'WineUser');

    // There isn't a consistent way to automatically identify appropriate "fields"
    // from an XML feed, so we pass an explicit list of source fields
    $fields = array(
      'name' => t('Producer name'),
      'description' => t('Description of producer'),
      'authorid' => t('Numeric ID of the author'),
      'region' => t('Name of region'),
    );

    // The source ID here is the one retrieved from each data item in the XML file, and
    // used to identify specific items
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'sourceid' => array(
          'type' => 'varchar',
          'length' => 4,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // IMPORTANT: Do not try this at home! We have included importable files
    // with the migrate_example module so it can be very simply installed and
    // run, but you should never include any data you want to keep private
    // (especially user data like email addresses, phone numbers, etc.) in the
    // module directory. Your source data should be outside of the webroot, and
    // should not be anywhere where it may get committed into a revision control
    // system.

    // This can also be an URL instead of a file path.
    $xml_folder = DRUPAL_ROOT . '/' . drupal_get_path('module', 'migrate_example') . '/xml/';
    $items_url = $xml_folder . 'producers.xml';

    // We use the MigrateSourceMultiItems class for any source where we obtain the list
    // of IDs to process and the data for each item from the same file. Typically the data
    // for an item is not contained in a single line within the source file. Examples include
    // multiple items defined in a single xml file or a single json file where in both cases
    // the id is part of the item.

    $item_xpath = '/producers/producer';  // relative to document

    $item_ID_xpath = 'sourceid';         // relative to item_xpath and gets assembled
                                         // into full path /producers/producer/sourceid

    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);

    $this->destination = new MigrateDestinationNode('migrate_example_producer');

    // TIP: Note that for XML sources, in addition to the source field passed to
    // addFieldMapping (the name under which it will be saved in the data row
    // passed through the migration process) we specify the Xpath used to retrieve
    // the value from the XML.
    // TIP: Note that all xpaths for fields begin at the last element of the item
    // xpath since each item xml chunk is processed individually.
    // (ex. xpath=name is equivalent to a full xpath of /producers/producer/name)
    $this->addFieldMapping('title', 'name')
         ->xpath('name');
    $this->addFieldMapping('uid', 'authorid')
         ->xpath('authorid')
         ->sourceMigration('WineUser')
         ->defaultValue(1);
    $this->addFieldMapping('migrate_example_wine_regions', 'region')
         ->xpath('region');
    $this->addFieldMapping('body', 'description')
         ->xpath('description');

    $this->addUnmigratedDestinations(array('revision_uid', 'created', 'changed',
      'status', 'promote', 'sticky', 'revision', 'log', 'language', 'tnid',
      'is_new', 'body:summary', 'body:format', 'body:language',
      'migrate_example_wine_regions:source_type', 'migrate_example_wine_regions:create_term',
      'comment'));
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->issueGroup(t('DNM'));
      if (module_exists('pathauto')) {
        $this->addFieldMapping('pathauto')
             ->issueGroup(t('DNM'));
      }
    }
    if (module_exists('statistics')) {
      $this->addUnmigratedDestinations(array('totalcount', 'daycount', 'timestamp'));
    }
  }
}
