<?php 

// Enable the CREA theme.
db_update('system')
->fields(array('status' => 1))
->condition('type', 'theme')
->condition('name', 'crea')
->execute();
variable_set('theme_default', 'crea');

// Enable the admin theme.
db_update('system')
->fields(array('status' => 1))
->condition('type', 'theme')
->condition('name', 'adminimal')
->execute();
variable_set('admin_theme', 'adminimal');

db_update('block')
->fields(array('status' => 0))
->condition('theme', 'adminimal')
->condition('module', 'locale')
->condition('delta', 'language')
->execute();

db_update('block')
->fields(array('status' => 0))
->condition('theme', 'adminimal')
->condition('module', 'search')
->condition('delta', 'form')
->execute();

db_update('block')
->fields(array('status' => 0))
->condition('theme', 'adminimal')
->condition('module', 'crea_design')
->condition('delta', 'crea_social')
->execute();

db_update('block')
->fields(array('status' => 0))
->condition('theme', 'adminimal')
->condition('module', 'crea_design')
->condition('delta', 'crea_slideshow')
->execute();

db_update('block')
->fields(array('status' => 0))
->condition('theme', 'adminimal')
->condition('module', 'crea_cartographie')
->condition('delta', 0)
->execute();

// Disable other themes
db_update('system')
->fields(array('status' => 0))
->condition('type', 'theme')
->condition('name', array('garland', 'seven', 'bartik'), 'IN')
->execute();