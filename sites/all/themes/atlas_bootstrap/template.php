<?php
/**
 * @file
 * The primary PHP file for this theme.
 */

function atlas_bootstrap_preprocess_html(&$variables) {
  global $language;
  // Add font awesome cdn.
  drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.5.0/css/font-awesome.min.css', array(
    'type' => 'external'
  ));
  if($language->language == "en"){
    // on ajoute le css spécifique EN pour le slider
    drupal_add_css(drupal_get_path('theme', 'atlas_bootstrap') . '/css/twentytwenty/en.css');
  }

  $args = arg();
  if (isset($args[0])
  && $args[0] == 'node'
  && isset($args[1])){
    $nid = (int)$args[1];
    if ($node = node_load($nid)){
      if ($field_identite_visuelle = field_get_items('node', $node, 'field_identite_visuelle')){
        if (isset($field_identite_visuelle[0]['value'])){
          $variables['classes_array'][] = $field_identite_visuelle[0]['value'];
        }
      }
    }
  }
}

function atlas_bootstrap_menu_tree__main_menu($variables) {
  return '<ul class="nav navbar-nav">' . $variables['tree'] . '</ul>';
}

function atlas_bootstrap_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu multi-level" role="menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#title'] .= ' <span class="caret"></span>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] > 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu" role="menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#attributes']['class'][] = 'dropdown';
      $element['#attributes']['class'][] = 'dropdown-submenu';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }

  if ($element['#below']){
    $element['#localized_options']['fragment'] = FALSE;
    $output = l($element['#title'], NULL, $element['#localized_options']);
  }
  else{
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  }

  if (isset($element['#localized_options']['custom_classes'])){
    $custom_classes = explode(' ', $element['#localized_options']['custom_classes']);
    foreach ($custom_classes AS $custom_classe){
      $element['#attributes']['class'][] = filter_xss($custom_classe);
    }
  }

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function atlas_bootstrap_breadcrumb($variables) {
  $crumbs = '';
  $breadcrumbs = $variables['breadcrumb'];
  if(!empty($breadcrumbs)){
    $array_size = count($breadcrumbs);
    $crumbs = '<ol class="breadcrumb">';
    $crumbs .= '<li>' . l(t('Home'),'') . '</li>';
    $i = 1;
    while ($i < $array_size) {
      $crumbs .= '<li>' . $breadcrumbs[$i-1] . '</li>';
      $i++;
    }
    $crumbs .= '<li class="active">'. drupal_get_title() .'</li>';
    $crumbs .= '</ol>';
  }else{
    $trail = menu_get_active_trail();
    if (!empty($trail)) {
      $array_size = count($trail);
      if(isset($trail[1]) && $trail[1]['menu_name'] == 'main-menu'){
        $crumbs = '<ol class="breadcrumb">';
        $i = 1;
        while ($i <= $array_size) {
          if($i != $array_size){
            $crumbs .= '<li>' . l($trail[$i-1]['title'], $trail[$i-1]['href']) . '</li>';
          }else{
            $crumbs .= '<li class="active">' . $trail[$i-1]['title'] . '</li>';
          }
          $i++;
        }
        $crumbs .= '</ol>';
      }
    }
  }

  if ($crumbs == ''){
    $crumbs = '<ol class="breadcrumb">';
    $crumbs .= '<li>' . l(t('Home'),'') . '</li>';
    $crumbs .= '<li class="active">'. drupal_get_title() .'</li>';
    $crumbs .= '</ol>';
  }
  return $crumbs;
}

function atlas_bootstrap_preprocess_field(&$variables) {
  if($variables['element']['#field_name'] == 'field_slider') {
    $variables['theme_hook_suggestions'][] = 'crea_slider_before_after';
  }
  if($variables['element']['#field_name'] == 'field_module_kmz') {
    $variables['theme_hook_suggestions'][] = 'crea_modulekmz';
  }
  if($variables['element']['#field_name'] == 'field_time_machine') {
    $variables['theme_hook_suggestions'][] = 'crea_timeline';
  }
}

function atlas_bootstrap_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"container\"><div class=\"messages $type\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= reset($messages);
    }
    $output .= "</div></div>\n";
  }
  return $output;
}
