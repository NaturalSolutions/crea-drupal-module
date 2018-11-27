<?php 

// menu disponibles pour les pages et webform
$page_menu = array(
	'main-menu' => 'main-menu',
	'devel' => 0,
	'menu-footer' => 'menu-footer',
	'management' => 0,
	'navigation' => 0,
	'user-menu' => 0
);
variable_set('menu_options_page', $page_menu);
variable_set('menu_options_webform', $page_menu);

variable_set('menu_parent_page', '');
variable_set('menu_parent_webform', '');

$domain_conf = domain_conf_variable_get(1, 'menu_options_page');
$domain_conf['menu-footer'] = 'menu-footer';
domain_conf_variable_set(1, 'menu_options_page', $domain_conf);

$domain_conf = domain_conf_variable_get(2, 'menu_options_page');
$domain_conf['menu-footer'] = 'menu-footer';
domain_conf_variable_set(2, 'menu_options_page', $domain_conf);

// webforms language
variable_set('i18n_node_extended_webform', 1);
variable_set('i18n_node_options_webform', array('current', 'required', 'lock'));
variable_set('language_content_type_webform', '1');

// permissions des webform
$manager_permissions = array(
	'create webform content' => true,
	'delete own webform content' => true,
	'delete any webform content' => true,
	'access own webform results' => true,
	'access all webform results' => true,
	'edit any webform content' => true,
	'edit own webform content' => true,
	'edit own webform submissions' => true,
	'edit all webform submissions' => true,
	'delete all webform submissions' => true,
	'delete own webform submissions' => true,
	'edit webform components' => true,
	'access own webform submissions' => true
);

user_role_change_permissions(5, $manager_permissions);

// block des cartes à passer sous le contenu
db_update('block')
->fields(array('weight' => '-18'))
->condition('module', 'crea_cartographie', '=')
->condition('delta', 0, '=')
->condition('theme', 'crea', '=')
->execute();

db_update('block')
->fields(array('weight' => '-17'))
->condition('module', 'crea_cartographie', '=')
->condition('delta', 1, '=')
->condition('theme', 'crea', '=')
->execute();

// global redirect
$global_redirect = array(
    'language_redirect' => 1,
);
variable_set('globalredirect_settings', $global_redirect);

// permissions pour le manager sur les contenus par domaine
$manager_permissions = array(
    'set domain access' => true,
    'publish to any assigned domain' => true,
    'publish from assigned domain' => true,
    'publish from default domain' => true,
    'edit domain content' => true,
    'delete domain content' => true,
    'view unpublished domain content' => true
);

user_role_change_permissions(5, $manager_permissions);
