<?php

// on recupere les champs du module_kmz et de la page
$fields_kmz = field_info_instances("node", "module_kmz");
$fields_page = field_info_instances("node", "page");

// ajout du type de contenu module kmz si inexistant
$types = node_type_get_types();
if(!in_array('module_kmz', $types)) {
    $type = array(
        'type' => 'module_kmz',
        'name' => st('KMZ Module'),
        'base' => 'node_content',
        'description' => st('Module to display KMZ files'),
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
}

// Add the field "scald_file" to the content type.
if(!isset($fields_kmz['scald_file'])) {
    $instance = array(
        'field_name' => 'scald_file',
        'entity_type' => 'node',
        'label' => st('KMZ file(s)'),
        'bundle' => 'module_kmz',
        'required' => 1,
        'settings' => array(
            'file_extensions' => 'kmz',
            'description_field' => 1
        ),
        'widget' => array(
            'weight' => 2,
            'type' => 'file_generic',
            'module' => 'file',
            'active' => 1,
            'settings' => array(
                'progress_indicator' => 'throbber',
            ),
        ),
        'display' => array(
            'default' => array(
                'label' => 'hidden',
                'type' => 'full',
                'settings' => array('link' => 0, 'override' => 0),
                'module' => 'atom_reference',
                'weight' => 1,
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
}
// Add the field "body" to the content type.
if(!isset($fields_kmz['body'])) {
    $instance = array(
        'field_name' => 'body',
        'entity_type' => 'node',
        'label' => st('Description'),
        'bundle' => 'module_kmz',
        'required' => 1,
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
}

// ajout du champ field_module_kmz sur le contenu page
// on supprime ce qui concerne field_module_kmz si existant
if(isset($fields_page['field_module_kmz'])){
    $instance = field_read_instance('node', 'field_module_kmz', 'page');
    field_delete_instance($instance);
    field_delete_field('field_module_kmz');
}
// creation du champ field_module_kmz
$field = field_read_field('field_module_kmz');
if (!$field){
    $field = array(
        'field_name' => 'field_module_kmz',
        'translatable' => 0,
        'entity_types' => array(),
        'settings' => array(
            'referenceable_types' => array(
                'module_kmz' => 'module_kmz',
            ),
            'view' => array(
                'view_name' => '',
                'display_name' => '',
                'args' => array()
            )
        ),
        'storage' => array(
            'type' => 'field_sql_storage',
            'settings' => array(),
            'module' => 'field_sql_storage',
            'active' => 1,
            'details' => array(
                'sql' => array(
                    'FIELD_LOAD_CURRENT' => array(
                        'field_data_field_module_kmz' => array(
                            'nid' => 'field_module_kmz_nid'
                        )
                    ),
                    'FIELD_LOAD_REVISION' => array(
                        'field_revision_field_module_kmz' => array(
                            'nid' => 'field_module_kmz_nid'
                        )
                    )
                )
            )
        ),
        'foreign keys' => array(
            'nid' => array(
                'table' => 'node',
                'columns' => array(
                    'nid' => 'nid'
                )
            )
        ),
        'indexes' => array(
            'nid' => array(
                '0' => 'nid'
            )
        ),
        'field_name' => 'field_module_kmz',
        'type' => 'node_reference',
        'module' => 'node_reference',
        'active' => 1,
        'locked' => 0,
        'cardinality' => -1,
        'deleted' => 0,
        'columns' => array(
            'nid' => array(
                'type' => 'int',
                'unsigned' => 1,
                'not null' => FALSE
            )
        )
    );

    field_create_field($field);
}

// ajout du champ field_module_kmz sur le contenu page
if(!isset($fields_page['field_module_kmz'])) {
    $instance = array(
        'field_name' => 'field_module_kmz',
        'entity_type' => 'node',
        'label' => st('KMZ modules'),
        'bundle' => 'page',
        'required' => 0,
        'settings' => array(
            'user_register_form' => FALSE,
        ),
        'widget' => array(
            'weight' => 43,
            'type' => 'node_reference_autocomplete',
            'module' => 'node_reference',
            'active' => 1,
            'settings' => array(
                'autocomplete_match' => 'contains',
                'size' => 60,
                'autocomplete_path' => 'node_reference/autocomplete'
            ),
        ),
        'display' => array(
            'default' => array(
                'label' => 'above',
                'type' => 'node_reference_default',
                'settings' => array(),
                'module' => 'node_reference',
                'weight' => 3
            ),
        ),
    );
    field_create_instance($instance);
}

// ajout de la permission pour créer un slider pour le manager
$role_manager = user_role_load_by_name('manager');
$manager_rid = $role_manager->rid;
$permissions = user_role_permissions( array( $manager_rid => 'manager' ) );
$permissions[$manager_rid]['create module_kmz content'] = TRUE;
$permissions[$manager_rid]['edit own module_kmz content'] = TRUE;
$permissions[$manager_rid]['edit any module_kmz content'] = TRUE;
$permissions[$manager_rid]['delete own module_kmz content'] = TRUE;
$permissions[$manager_rid]['delete any module_kmz content'] = TRUE;
// Grant permissions to our 'editor' role
user_role_change_permissions($manager_rid, $permissions[$manager_rid]);


// ajout de la permission pour créer un slider pour l admin
$role_admin = user_role_load_by_name('administrator');
$admin_rid = $role_admin->rid;
$permissions = user_role_permissions(array($admin_rid => 'administrator'));
$permissions[$admin_rid]['create module_kmz content'] = TRUE;
$permissions[$admin_rid]['edit own module_kmz content'] = TRUE;
$permissions[$admin_rid]['edit any module_kmz content'] = TRUE;
$permissions[$admin_rid]['delete own module_kmz content'] = TRUE;
$permissions[$admin_rid]['delete any module_kmz content'] = TRUE;
// Grant permissions to our 'administrator' role
user_role_change_permissions($admin_rid, $permissions[$admin_rid]);

//throw new DrupalUpdateException();
