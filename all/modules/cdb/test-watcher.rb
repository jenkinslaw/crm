# Modify this file as necessary to run specific tests on file changes.
# @see https://github.com/mynyml/watchr for usage details.

watch( 'company.module|CompanyEntityForm' ) {|md| `drush test-run CompanyModuleTestCase`}

watch( 'cdb.module' ) {|md| `drush test-run CdbModuleTestCase`}

watch( 'EntityForm|CompanyEntityForm' ) {|md| `drush test-run CdbEntityTestCase`}

watch( '.*\.test' ) { |md| 
  puts `run-tests.sh --url 'http://localhost' --color --verbose --file 'sites/all/modules/cdb/#{md[0]}'`
}

