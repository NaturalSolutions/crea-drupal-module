<?php
$plugin = array(
  'single' => TRUE,
  'title' => t('CREA custom content'),
  'description' => t(''),
  'category' => t('CREA'),
  'edit form' => 'crea_backoffice_custom_content_edit_form',
  'render callback' => 'crea_backoffice_custom_content_render',
  'admin info' => 'crea_backoffice_custom_content_admin_info',
  'defaults' => array(
    'title' => '',
    'title_icon' => '',
    'body' => '',
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function crea_backoffice_custom_content_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = isset($conf['title']) ? $conf['title'] : '';
    return $block;
  }
}

/**
 * 'Edit form' callback for the content type.
 */
function crea_backoffice_custom_content_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['title'] = array(
    '#title' => t('Title'),
    '#description' => t(''),
    '#type' => 'textfield',
    '#default_value' => isset($conf['title']) ? $conf['title'] : '',
    '#required' => FALSE,
  );

  $form['title_icon'] = array(
    '#title' => t('Icon title class'),
    '#description' => t('loupe, feuille, montagne, list, live, tweet, video'),
    '#type' => 'textfield',
    '#default_value' => isset($conf['title_icon']) ? $conf['title_icon'] : '',
    '#required' => FALSE,
  );

  $form['body'] = array(
    '#title' => t('Content'),
    '#description' => t(''),
    '#type' => 'text_format',
    '#format' => isset($conf['body']['format']) ? $conf['body']['format'] : 'full_html',
    '#default_value' => isset($conf['body']['value']) ? $conf['body']['value'] : '',
    '#required' => FALSE,
    '#dnd-enabled' => TRUE,
    '#dnd-settings' => array('drop_selector' => '#edit-body-value .drop'),
    'mee' => array(
      '#prefix' => '<div class="mee-wrap-editor-library">',
      '#suffix' => '</div>',
      '#attached' => array(
        'css' => array(drupal_get_path('module', 'mee') . '/css/mee.css'),
        'js' => array(drupal_get_path('module', 'mee')  . '/mee.js'),
        'library' => array(
          array('dnd', 'library'),
        ),
      ),
      '#element_validate' => array('crea_backoffice_field_text_validate'),
      '#weight' => 0.5,
      'resource_manager' => array(
        '#theme' => 'mee_resource_manager',
      ),
    )
  );
  $sas = scald_rendered_to_sas($form['body']['#default_value']);
  $scald_included = scald_included($sas);
  $sids = array_unique($scald_included);
  $form['body']['#default_value'] = scald_sas_to_rendered($form['body']['#default_value']);

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function crea_backoffice_custom_content_edit_form_submit($form, &$form_state) {
  watchdog('crea_panel_submit', serialize($form_state['values']));
  watchdog('crea_panel_submit', serialize($form_state['plugin']));
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
      watchdog('crea_panel_submit_value', serialize($form_state['conf'][$key]));
    }
  }
}

/**
 * See ctools_plugin_examples for more advanced info
 */
function crea_backoffice_custom_content_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  // initial content is blank
  $block->title = '';
  $block->content = '';

  // Add in the content
  if(isset($conf['title'])
  && !empty($conf['title'])){
    $block->content .= '<h2 class="block-title">';
    if (isset($conf['title_icon'])){
      $block->content .= '<span class="icon ' . $conf['title_icon'] . '"> </span>';
    }
    $block->content .= '<span class="title">' . check_plain($conf['title']) . '</span></h2>';
  }

  if (isset($conf['body'])){
    $block->content .= check_markup($conf['body']['value'], $conf['body']['format']);
  }

  return $block;
}