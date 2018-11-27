<?php

$obsolete_node_types = array('slideshow_home', 'faune', 'flore');

// suppression des contenus qui ne servent plus
$query = db_select('node', 'n')
  ->fields('n', array('nid'))
  ->condition('n.type', $obsolete_node_types, 'IN');

$results = $query->execute()->fetchAll();

foreach($results AS $result){
  $node = node_delete($result->nid);
}

// suppression des types de contenus qui ne servent plus
foreach ($obsolete_node_types AS $type){
  node_type_delete($type);
}

// création du type de contenu "question scientifique"
$types = node_type_get_types();
if(!array_key_exists('question_scientifique', $types)) {
  $type = array(
    'type' => 'question_scientifique',
    'name' => st('Question scientifique'),
    'base' => 'node_content',
    'description' => st(''),
    'custom' => 1,
    'modified' => 1,
    'locked' => 0,
  );
  $type = node_type_set_defaults($type);
  node_type_save($type);
  // variables by default
  variable_set('i18n_node_extended_'.$type->type, 1);
  variable_set('i18n_node_options_'.$type->type, array('current', 'required', 'lock'));
  variable_set('language_content_type_'.$type->type, '1');
  variable_set('menu_options_'.$type->type, array());
  variable_set('node_options_'.$type->type, array('status'));
  variable_set('comment_anonymous_'.$type->type, 0);
  variable_set('comment_default_mode_'.$type->type, 0);
  variable_set('comment_preview_'.$type->type, '0');
  variable_set('comment_'.$type->type, COMMENT_NODE_HIDDEN);
  variable_set('node_preview_'.$type->type, '0');
  variable_set('node_submitted_'.$type->type, 0);

  // Add the field "field_illustration" to the content type.
  $instance = array(
    'field_name' => 'field_illustration',
    'entity_type' => 'node',
    'label' => st('Illustration'),
    'bundle' => 'question_scientifique',
    'required' => 1,
    'settings' => array(
      'referencable_types' =>
        array (
          'image' => 'image',
        ),
      'user_register_form' => false,
    ),
    'widget' =>
      array (
        'weight' => '3',
        'type' => 'atom_reference_textfield',
        'module' => 'atom_reference',
        'active' => 1,
        'settings' =>
          array (
            'context' => 'sdl_library_item',
          ),
      ),
    'display' =>
      array (
        'default' =>
          array (
            'label' => 'hidden',
            'type' => 'full',
            'weight' => '2',
            'settings' =>
              array (
                'link' => 0,
                'override' => 0,
              ),
            'module' => 'atom_reference',
          ),
      ),
  );
  field_create_instance($instance);

  // Add the field "body" to the content type.
  $instance = array(
    'field_name' => 'body',
    'entity_type' => 'node',
    'label' => st('Description'),
    'bundle' => 'question_scientifique',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'display_summary' => 0,
      'linkit' => array(
        'enable' => 0,
        'button_text' => 'Search'
      ),
      'dnd_enabled' => 0,
      'mee_enabled' => 0,
      'context_default' => 'sdl_editor_representation',
      'context' => 'title'
    ),
    'widget' => array(
      'weight' => 4,
      'type' => 'text_textarea_with_summary',
      'module' => 'text',
      'active' => 1,
      'settings' => array(
        'row' => 20,
        'summary_rows' => 5
      ),
    ),
    'display' => array(
      'default' => array(
        'label' => 'above',
        'type' => 'text_default',
        'settings' => array(),
        'module' => 'text',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'type' => 'hidden',
        'settings' => array(),
        'weight' => 0,
      ),
    ),
  );
  field_create_instance($instance);

  // Add the field "field_body_wrapper" to the content type.
  $instance = array(
    'field_name' => 'field_body_wrapper',
    'entity_type' => 'node',
    'label' => st('zone de contenu'),
    'bundle' => 'question_scientifique',
    'required' => 0,
    'widget' =>
      array (
        'weight' => '9',
        'type' => 'field_collection_embed',
        'module' => 'field_collection',
        'active' => 0,
        'settings' =>
          array (
          ),
      ),
    'settings' =>
      array (
        'user_register_form' => false,
      ),
    'display' =>
      array (
        'default' =>
          array (
            'label' => 'hidden',
            'type' => 'field_collection_view',
            'weight' => '1',
            'settings' =>
              array (
                'edit' => 'Editer',
                'delete' => 'Supprimer',
                'add' => 'Ajouter',
                'description' => true,
                'view_mode' => 'full',
              ),
            'module' => 'field_collection',
          ),
      ),
  );
  field_create_instance($instance);
}

// creation du champ field_subtitle
$field = field_read_field('field_subtitle');
if (!$field) {
  $field = array(
    'field_name' => 'field_subtitle',
    'type' => 'text',
    'module' => 'text',
    'active' => 1,
    'locked' => 0,
    'cardinality' => 1,
    'deleted' => 0,
    'translatable' => '0',
    'entity_types' =>
      array (
      ),
    'settings' =>
      array (
        'max_length' => '255',
      ),
    'storage' =>
      array (
        'type' => 'field_sql_storage',
        'settings' =>
          array (
          ),
        'module' => 'field_sql_storage',
        'active' => '1',
        'details' =>
          array (
            'sql' =>
              array (
                'FIELD_LOAD_CURRENT' =>
                  array (
                    'field_data_field_subtitle' =>
                      array (
                        'value' => 'field_subtitle_value',
                        'format' => 'field_subtitle_format',
                      ),
                  ),
                'FIELD_LOAD_REVISION' =>
                  array (
                    'field_revision_field_subtitle' =>
                      array (
                        'value' => 'field_subtitle_value',
                        'format' => 'field_subtitle_format',
                      ),
                  ),
              ),
          ),
      ),
    'foreign keys' =>
      array (
        'format' =>
          array (
            'table' => 'filter_format',
            'columns' =>
              array (
                'format' => 'format',
              ),
          ),
      ),
    'indexes' =>
      array (
        'format' =>
          array (
            0 => 'format',
          ),
      ),
  );
  field_create_field($field);

  // Add the field "field_body_wrapper" to the content type.
  $instance = array(
    'field_name' => 'field_subtitle',
    'entity_type' => 'node',
    'label' => st('Question scientifique'),
    'bundle' => 'question_scientifique',
    'required' => 0,
    'widget' =>
      array (
        'weight' => '1',
        'type' => 'text_textfield',
        'module' => 'text',
        'active' => 1,
        'settings' =>
          array (
            'size' => '60',
          ),
      ),
    'settings' =>
      array (
        'text_processing' => '0',
        'linkit' =>
          array (
            'enable' => 0,
            'profile' => '',
            'button_text' => 'Rechercher',
          ),
        'dnd_enabled' => 0,
        'mee_enabled' => 0,
        'context_default' => 'sdl_editor_representation',
        'context' => 'title',
        'user_register_form' => false,
      ),
    'display' =>
      array (
        'default' =>
          array (
            'label' => 'above',
            'type' => 'text_default',
            'settings' =>
              array (
              ),
            'module' => 'text',
            'weight' => 3,
          ),
      ),
  );
  field_create_instance($instance);
}

// Modification du display mode de chaque champ
if ($field_instance = field_read_instance('node', 'question_scientifique', 'field_subtitle')){
  $field_instance['display'] = array (
    'default' =>
      array (
        'label' => 'hidden',
        'type' => 'text_default',
        'weight' => '0',
        'settings' =>
          array (
          ),
        'module' => 'text',
      ),
    'teaser' =>
      array (
        'label' => 'hidden',
        'type' => 'text_default',
        'weight' => '1',
        'settings' =>
          array (
          ),
        'module' => 'text',
      ),
  );

  field_update_instance($field_instance);
}

if ($field_instance = field_read_instance('node', 'question_scientifique', 'body')){
  $field_instance['display'] = array (
    'default' =>
      array (
        'label' => 'hidden',
        'type' => 'text_default',
        'weight' => '1',
        'settings' =>
          array (
          ),
        'module' => 'text',
      ),
    'teaser' =>
      array (
        'label' => 'above',
        'type' => 'hidden',
        'weight' => '5',
        'settings' =>
          array (
          ),
      ),
  );

  field_update_instance($field_instance);
}

if ($field_instance = field_read_instance('node', 'question_scientifique', 'field_illustration')){
  $field_instance['display'] = array (
    'default' =>
      array (
        'label' => 'hidden',
        'type' => 'hidden',
        'weight' => '3',
        'settings' =>
          array (
          ),
      ),
    'teaser' =>
      array (
        'label' => 'hidden',
        'type' => 'full',
        'weight' => '0',
        'settings' =>
          array (
            'link' => 0,
            'override' => 0,
          ),
        'module' => 'atom_reference',
      ),
  );

  field_update_instance($field_instance);
}

if ($field_instance = field_read_instance('node', 'question_scientifique', 'field_body_wrapper')){
  $field_instance['display'] = array (
    'default' =>
      array (
        'label' => 'hidden',
        'type' => 'field_collection_view',
        'weight' => '2',
        'settings' =>
          array (
            'edit' => 'Editer',
            'delete' => 'Supprimer',
            'add' => 'Ajouter',
            'description' => true,
            'view_mode' => 'full',
          ),
        'module' => 'field_collection',
      ),
    'teaser' =>
      array (
        'label' => 'above',
        'type' => 'hidden',
        'weight' => '4',
        'settings' =>
          array (
          ),
      ),
  );

  field_update_instance($field_instance);
}

// permissions pour le nouveau type de contenu
user_role_change_permissions(3, array(
  "create question_scientifique content on assigned domains" => true,
  "update question_scientifique content on assigned domains" => true,
  "delete question_scientifique content on assigned domains" => true,
  "create question_scientifique content" => true,
  "edit own question_scientifique content" => true,
  "edit any question_scientifique content" => true,
  "delete own question_scientifique content" => true,
  "delete any question_scientifique content" => true,
));

user_role_change_permissions(4, array(
  "create question_scientifique content" => true,
  "edit own question_scientifique content" => true,
  "edit any question_scientifique content" => true,
  "delete own question_scientifique content" => true,
));

user_role_change_permissions(5, array(
  "create question_scientifique content" => true,
  "edit own question_scientifique content" => true,
  "edit any question_scientifique content" => true,
  "delete own question_scientifique content" => true,
  "delete any question_scientifique content" => true,
));

// url alias des contenus
variable_set('pathauto_node_panel_pattern', '[node:title]');
variable_set('pathauto_node_webform_pattern', '[node:title]');
variable_set('pathauto_node_question_scientifique_pattern', '[node:title]');