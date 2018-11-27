<?php

// activation du module block_class
module_enable(array('block_class'));

// activation du thème
db_update('system')
->fields(array('status' => 1))
->condition('type', 'theme')
->condition('name', 'crea_bootstrap')
->execute();

// ajout de la variable de thème pour les domaines
domain_conf_variable_set(1, 'domain_theme', 'crea_bootstrap');
domain_conf_variable_set(1, 'domain_css', '');
domain_conf_variable_set(1, 'site_slogan', "Centre de Recherches<br/>sur les Écosystèmes d'Altitude");
domain_conf_variable_set(2, 'domain_theme', 'crea');

// positionnement des blocks
db_update('block')
  ->fields(array('region' => 'sur_header', 'title' => '<none>', 'status' => '1', 'weight' => '-22', 'pages' => ''))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_login', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sur_header', 'title' => '<none>', 'status' => '1', 'weight' => '-20', 'pages' => ''))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_langue_switcher', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'navigation', 'title' => '<none>', 'status' => '1', 'weight' => '0', 'pages' => ''))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_main_menu', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'content', 'title' => '<none>', 'status' => '1', 'weight' => '-24', 'pages' => '<front>'))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_logos_hp', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'content', 'title' => '<none>', 'status' => '1', 'weight' => '-22', 'pages' => '<front>'))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_actus', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'content', 'title' => '<none>', 'status' => '1', 'weight' => '-21', 'pages' => '<front>'))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_social', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sub_content', 'title' => "live de l'observatoire", 'status' => '1', 'weight' => '-25', 'visibility' => 1, 'pages' => '<front>', 'css_class' => 'col col-md-4'))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_live_hp', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sub_content', 'title' => 'agenda du crea', 'status' => '1', 'weight' => '-24', 'visibility' => 1, 'pages' => '<front>', 'css_class' => 'col col-md-4'))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_agenda_hp', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sub_content', 'title' => '<none>', 'status' => '1', 'weight' => '0', 'visibility' => 1, 'pages' => '<front>', 'css_class' => 'col col-md-4'))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_tweet_hp', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

db_update('block')
  ->fields(array('region' => 'footer', 'title' => '<none>', 'status' => '1', 'weight' => '-25', 'pages' => ''))
  ->condition('theme', 'crea_bootstrap', '=')
  ->condition('delta', 'crea_logos_footer', '=')
  ->condition('module', 'crea_design', '=')
  ->execute();

variable_set('crea_block_social', "<ul>\015\012\011<li><a href=\"https://fr-fr.facebook.com/creamontblanc\"><span class=\"icon-facebook\">&nbsp;</span></a></li>\015\012\011<li><a href=\"https://twitter.com/creamontblanc\"><span class=\"icon-twitter\">&nbsp;</span></a></li>\015\012\011<li><a href=\"https://www.youtube.com/channel/UCWJTizJOA_m_CnBrdnZIIqw\"><span class=\"icon-youtube\">&nbsp;</span></a></li>\015\012\011<li><a href=\"https://www.flickr.com/photos/creamontblanc/\"><span class=\"icon-flickr\">&nbsp;</span></a></li>\015\012\011<li><a href=\"https://storify.com/creamontblanc\"><span class=\"icon-storify\">&nbsp;</span></a></li>\015\012\011<li><a href=\"https://www.instagram.com/creamontblanc/\"><span class=\"icon-instagram\">&nbsp;</span></a></li>\015\012\011<li><a href=\"http://www.scoop.it/u/crea-mont-blanc\"><span class=\"icon-scoop-it\">&nbsp;</span></a></li>\015\012</ul>\015\012\015\012<div class=\"clear\">&nbsp;</div>\015\012");
variable_set('live_image_src', "http://crea.montblanc.pro/crea/crealive/vallot.jpg");
variable_set('live_id_station', '231');

// cacher le champ langue et domaine de l'affichage des types de contenu
$content_types = node_type_get_types();
foreach ($content_types AS $key => $value){
  $variable_name = 'field_bundle_settings_node__' . $key;

  if ($page_display = variable_get($variable_name, false)) {
    if (isset($page_display['extra_fields']['display']['language'])){
      $page_display['extra_fields']['display']['language']['default']['weight'] = 0;
      $page_display['extra_fields']['display']['language']['default']['visible'] = FALSE;
    }

    if (isset($page_display['extra_fields']['display']['domain'])){
      $page_display['extra_fields']['display']['domain']['default']['weight'] = 0;
      $page_display['extra_fields']['display']['domain']['default']['visible'] = FALSE;
    }

    variable_set($variable_name, $page_display);
  }
}