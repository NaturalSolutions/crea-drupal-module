<?php

// Configuration des domaines
domain_conf_variable_set(1, 'site_slogan', "Centre de Recherches\015\012sur les \303\211cosyst\303\250mes d'Altitude");
domain_conf_variable_set(2, 'site_slogan', "Phrase d'accroche\015\012Phrase d'accroche ......");
domain_conf_variable_set(2, 'domain_css', "");
domain_conf_variable_set(2, 'domain_logo', "sites/all/themes/atlas_bootstrap/logo-atlas.png");
domain_conf_variable_set(2, 'domain_favicon', "sites/all/themes/atlas_bootstrap/favicon-atlas.ico");
domain_conf_variable_set(2, 'domain_theme', "atlas_bootstrap");

// désactivation des blocks du thème CREA
db_update('block')
  ->fields(array('region' => '-1'))
  ->condition('theme', 'crea')
  ->execute();

// placement des blocs
db_update('block')
  ->fields(array('region' => '-1'))
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

// sur_header
db_update('block')
  ->fields(array('region' => 'sur_header', 'weight' => 0, 'title' => '<none>', 'status' => 1))
  ->condition('delta', 'crea_langue_switcher')
  ->condition('module', 'crea_design')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sur_header', 'weight' => 0, 'title' => '<none>', 'status' => 1))
  ->condition('delta', 'crea_login')
  ->condition('module', 'crea_design')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sur_header', 'weight' => -19, 'title' => '<none>', 'status' => 1))
  ->condition('delta', 'form')
  ->condition('module', 'search')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

// header
$delta = db_insert('block_custom')
  ->fields(array(
    'body' => "<p class=\"rteright\"><a href=\"http://www.creamontblanc.org\"><img alt=\"aller au site CREA Mont Blanc\" src=\"/sites/all/themes/crea_bootstrap/logo.png\" style=\"height: 80px;\" /></a></p>",
    'info' => "Retour au CREA",
    'format' => "full_html",
  ))
  ->execute();

$query = db_insert('block')->fields(array('visibility', 'custom', 'title', 'module', 'theme', 'status', 'weight', 'delta', 'cache'));
foreach (list_themes() as $key => $theme) {
  if ($theme->status) {
    $query->values(array(
      'visibility' => 0,
      'custom' => 0,
      'title' => '',
      'module' => 'block',
      'theme' => $theme->name,
      'status' => 0,
      'weight' => 0,
      'delta' => $delta,
      'cache' => DRUPAL_NO_CACHE,
    ));
  }
}
$query->execute();

db_merge('block')
  ->key(array('theme' => 'atlas_bootstrap', 'delta' => $delta, 'module' => 'block'))
  ->fields(array(
    'region' => 'header',
    'pages' => '',
    'status' => 1,
  ))
  ->execute();

// navigation
db_update('block')
  ->fields(array('region' => 'navigation', 'weight' => 0, 'title' => '<none>', 'status' => 1))
  ->condition('delta', 'crea_main_menu')
  ->condition('module', 'crea_design')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

// help
db_update('block')
  ->fields(array('region' => 'help', 'weight' => 5, 'status' => 1))
  ->condition('delta', 'help')
  ->condition('module', 'system')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

// content
db_update('block')
  ->fields(array('region' => 'content', 'weight' => -19, 'status' => 1))
  ->condition('delta', 'main')
  ->condition('module', 'system')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'content', 'weight' => -17, 'title' => '<none>', 'status' => 1, 'visibility' => 1, 'pages' => 'node/14
node/151'))
  ->condition('delta', 0)
  ->condition('module', 'crea_cartographie')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'content', 'weight' => -17, 'title' => '<none>', 'status' => 1, 'visibility' => 1, 'pages' => 'node/55
node/186'))
  ->condition('delta', 1)
  ->condition('module', 'crea_cartographie')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

// sub_content
db_update('block')
  ->fields(array('region' => 'sub_content', 'weight' => -25, 'title' => '<none>', 'status' => 1, 'css_class' => 'container'))
  ->condition('delta', 'crea_social')
  ->condition('module', 'crea_design')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'sub_content', 'weight' => -24, 'status' => 1))
  ->condition('delta', 6)
  ->condition('module', 'block')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

// footer
db_update('block')
  ->fields(array('region' => 'footer', 'weight' => -24, 'title' => '<none>', 'status' => 1))
  ->condition('delta', 'menu-footer')
  ->condition('module', 'menu')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'footer', 'weight' => -25, 'title' => '<none>', 'css_class' => 'col', 'status' => 1))
  ->condition('delta', 'crea_logos_footer')
  ->condition('module', 'crea_design')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();

db_update('block')
  ->fields(array('region' => 'footer', 'weight' => -23, 'status' => 1))
  ->condition('delta', 5)
  ->condition('module', 'block')
  ->condition('theme', 'atlas_bootstrap')
  ->execute();
