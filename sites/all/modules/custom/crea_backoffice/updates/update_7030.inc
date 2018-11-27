<?php

$delta = db_insert('block_custom')
  ->fields(array(
    'body' => "<div style=\"padding: 10px 15px; background:url('/sites/default/files/thumbnails/image/bg-banniere-atlas.jpg') no-repeat;\">
<p><span style=\"font-size:22px;\"><em><span class=\"white-text\">L'Atlas du Mont-Blanc est ......</span></em></span><br />
<span style=\"font-size:22px;\"><em><span class=\"white-text\">L'Atlas du Mont-Blanc est ......&nbsp; L'Atlas du Mont-Blanc est ......</span></em></span></p>

<p><a class=\"crea-button transparent-orange-button-link no-icon\" href=\"http://www.google.fr\">Saisir une observation</a></p>
</div>
",
    'info' => "bannière atlas",
    'format' => "full_html",
  ))
  ->execute();

$query = db_insert('block')->fields(array('visibility', 'custom', 'title', 'module', 'theme', 'status', 'weight', 'delta', 'cache', 'css_class'));
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
      'css_class' => 'banniere_atlas container'
    ));
  }
}
$query->execute();

foreach (list_themes() as $key => $theme) {
  db_merge('block')
    ->key(array('theme' => $theme->name, 'delta' => $delta, 'module' => 'block'))
    ->fields(array(
      'css_class' => 'banniere_atlas container',
      'pages' => ''
    ))
    ->execute();
}

db_merge('block')
  ->key(array('theme' => 'atlas_bootstrap', 'delta' => $delta, 'module' => 'block'))
  ->fields(array(
    'region' => 'sur_content',
    'pages' => '',
    'status' => 1
  ))
  ->execute();

// Variable du thème ATLAS
$atlas = variable_get('theme_atlas_bootstrap_settings');
$atlas['bootstrap_fluid_container'] = 1;
variable_set('theme_atlas_bootstrap_settings', $atlas);