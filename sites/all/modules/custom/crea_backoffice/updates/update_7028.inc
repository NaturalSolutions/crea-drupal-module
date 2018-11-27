<?php

// Permission sur le type de contenu "panel node"
user_role_change_permissions(5, array(
  "create panel-nodes" => true,
  "edit any panel-nodes" => true,
  "edit own panel-nodes" => true,
  "administer panel-nodes" => true,
  "delete any panel-nodes" => true,
  "create panel content" => true,
  "edit own panel content" => true,
  "edit any panel content" => true,
  "delete own panel content" => true,
  "delete any panel content" => true,
));

// Variables de configuration du type de contenu "panel node"
variable_set('i18n_node_extended_panel', 1);
variable_set('i18n_node_options_panel', array('current', 'required', 'lock'));
variable_set('language_content_type_panel', '1');
variable_set('menu_options_panel', array());
variable_set('node_options_panel', array('status'));
variable_set('comment_anonymous_panel', 0);
variable_set('comment_default_mode_panel', 0);
variable_set('comment_preview_panel', '0');
variable_set('comment_panel', COMMENT_NODE_HIDDEN);
variable_set('node_preview_panel', '0');
variable_set('node_submitted_panel', 0);

// Création d'un format de date custom
system_date_format_type_save(array(
  'type' => 'titre',
  'title' => 'titre',
  'locked' => false,
  'is_new' => true,
));

$date_format_custom = array(
  'type' => 'titre',
  'format' => 'd F Y',
  'locked' => false,
  'locales' => array('fr'),
  'is_new' => true,
);
system_date_format_save($date_format_custom);

$date_format_custom = array(
  'type' => 'titre',
  'format' => 'F d Y',
  'locked' => false,
  'locales' => array('en'),
  'is_new' => true,
);
system_date_format_save($date_format_custom);

// création de la page d'accueil ATLAS FR
$node = new stdClass();
$node->title = 'page d\'accueil ATLAS';
$node->type = 'panel';

node_object_prepare($node);

$node->language = 'fr';
$node->uid = 3;
$node->status = 1;
$node->promote = 0;
$node->comment = 1;

node_save($node);

domain_conf_variable_set(2, 'site_frontpage_fr', "node/" . $node->nid);

// création de la page d'accueil ATLAS EN
$node = new stdClass();
$node->title = 'homepage ATLAS';
$node->type = 'panel';

node_object_prepare($node);

$node->language = 'en';
$node->uid = 3;
$node->status = 1;
$node->promote = 0;
$node->comment = 1;

node_save($node);

domain_conf_variable_set(2, 'site_frontpage_en', "node/" . $node->nid);

// dépublication des anciennes page d'accueil
//page FR
$node = node_load(189);
$node->status = 0;
node_save($node);

//page EN
$node = node_load(190);
$node->status = 0;
node_save($node);