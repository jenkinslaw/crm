CDB Installation Profile
========================

This is a stadard drupal profile that also enables the Jenkins Customer
Database modules.


##Install##

This profile needs to be placed in the root profiles folder in order to work.
`cd $DRUPAL_ROOT_DIR`

`ln -s ../sites/default/profiles/jenkins_cdb jenkins_cdb`


##Usage##

`drush site-install jenkins_cdb`

You may also need to make sure that `seetings.php` is writable by the user running the drush command.
`chmod u+w settings.php`
