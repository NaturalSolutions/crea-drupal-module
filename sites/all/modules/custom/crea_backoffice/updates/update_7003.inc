<?php

// Suppréssion du cache
drupal_flush_all_caches();

// Action des modules
$enable_dependencies = TRUE;
module_enable(array('devel', 'page_manager', 'panels'), $enable_dependencies);

// Ajout des liens manquants dans le menu footer
$item = array(
	'link_path' => '<front>',
	'link_title' => 'Partenaires',
	'menu_name' => 'menu-footer',
	'weight' => 10,
	'module' => 'menu',
);
menu_link_save($item);

$item = array(
	'link_path' => '<front>',
	'link_title' => 'Faire un don',
	'menu_name' => 'menu-footer',
	'weight' => 20,
	'module' => 'menu',
);
menu_link_save($item);

$item = array(
	'link_path' => 'https://fr-fr.facebook.com/creamontblanc',
	'link_title' => 'Facebook',
	'menu_name' => 'menu-footer',
	'weight' => 30,
	'module' => 'menu',
);
menu_link_save($item);

$item = array(
	'link_path' => 'https://twitter.com/creamontblanc',
	'link_title' => 'Twitter',
	'menu_name' => 'menu-footer',
	'weight' => 40,
	'module' => 'menu',
);
menu_link_save($item);

//throw new DrupalUpdateException();