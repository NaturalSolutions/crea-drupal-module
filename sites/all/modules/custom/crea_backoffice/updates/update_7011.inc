<?php 

// Activation de la langue pour les contenu slideshow home

variable_set('i18n_node_extended_slideshow_home', 1);
variable_set('i18n_node_options_slideshow_home', array('current', 'required'));
variable_set('language_content_type_slideshow_home', '1');
variable_set('menu_options_slideshow_home', array());
variable_set('node_options_slideshow_home', array('status'));
variable_set('comment_anonymous_slideshow_home', 0);
variable_set('comment_default_mode_slideshow_home', 0);
variable_set('comment_preview_slideshow_home', '0');
variable_set('comment_slideshow_home', COMMENT_NODE_HIDDEN);
variable_set('node_preview_slideshow_home', '0');
variable_set('node_submitted_slideshow_home', 0);

$variable_realm_list_language = variable_get('variable_realm_list_language', array());

if (!in_array('accueil_mb_live_txt', $variable_realm_list_language)){
	array_push($variable_realm_list_language, 'accueil_mb_live_txt');
	variable_set('variable_realm_list_language', $variable_realm_list_language);
}

module_enable(array('crea_users'));