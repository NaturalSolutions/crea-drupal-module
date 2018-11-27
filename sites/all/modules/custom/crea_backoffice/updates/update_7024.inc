<?php

// Création du champ "identité visuelle"
$fields_page = field_info_instances("node", "page");
if(!isset($fields_page['field_identite_visuelle'])) {
  $field_identite = array(
    'field_name' => 'field_identite_visuelle',
    'type' => 'list_text',
    'module' => 'list',
    'cardinality' => 1,
    'translatable' => '0',
    'entity_types' => array(),
    'settings' => array(
      'allowed_values' => array(
        'blue-layout' => 'bleu',
        'green-layout' => 'vert',
        ),
      'allowed_values_function' => '',
      ),
    'storage' => array(
      'type' => 'field_sql_storage',
      'settings' => array(),
      'module' => 'field_sql_storage',
      'active' => '1',
      'details' => array(
        'sql' => array(
          'FIELD_LOAD_CURRENT' => array(
            'field_data_field_identite_visuelle' => array(
              'value' => 'field_identite_visuelle_value',
            ),
          ),
          'FIELD_LOAD_REVISION' => array(
            'field_revision_field_identite_visuelle' => array(
              'value' => 'field_identite_visuelle_value',
            ),
          ),
        ),
      ),
    ),
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
  );

  field_create_field($field_identite);
}
else{
  $field_identite = $fields_page['field_identite_visuelle'];
}

// Création de l'instance du champ
if (is_null(field_info_instance('node', 'field_identite_visuelle', 'page'))){
  $field_instance_identite = array(
    "label" => "identité visuelle",
    "widget" => array(
      "weight" => 1,
      "type" => "options_select",
      "module" => "options",
      "active" => 1,
      "settings" => array()
    ),
    "settings" => array(
      "user_register_form" => ''
    ),
    "display" => array(
      "default" => array(
        "label" => "hidden",
        "type" => "hidden",
        "weight" => 9,
        "settings" => array(),
      ),
      "teaser" => array(
        "type" => "hidden",
        "label" => "above",
        "settings" => array(),
        "weight" => 0,
      ),
    ),
    "required" => 0,
    "description" => "Choisissez la couleur du titre de la page, de sa barre de soulignement et des liens de la page",
    "default_value" => '',
    "id" => $field_identite['id'],
    "field_name" => "field_identite_visuelle",
    "entity_type" => "node",
    "bundle" => "page",
    "deleted" => 0
  );
  field_create_instance($field_instance_identite);
}


