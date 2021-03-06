<?php
// on recupere les champs du slider
$fields_tm = field_info_instances("node", "time_machine");

// ajout du type de contenu slider si inexistant
$types = node_type_get_types();
if(!in_array('time_machine', $types)) {
    $type = array(
        'type' => 'time_machine',
        'name' => st('Time machine'),
        'base' => 'node_content',
        'description' => st('Slider for displaying few pics with their legends'),
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

// Add the field "field_illustration" to the content type.
if(!isset($fields_tm['field_illustration'])) {
    $instance = array(
        'field_name' => 'field_illustration',
        'entity_type' => 'node',
        'label' => st('Pics for the timeline'),
        'bundle' => 'time_machine',
        'required' => 1,
        'settings' => array(
            'referencable_types' => array(
                'image' => 'image',
            ),
            'user_register_form' => FALSE,
        ),
        'widget' => array(
            'weight' => 2,
            'type' => 'atom_reference_textfield',
            'module' => 'atom_reference',
            'active' => 1,
            'settings' => array(
                'context' => 'sdl_library_item',
            ),
        ),
        'display' => array(
            'default' => array(
                'label' => 'hidden',
                'type' => 'full',
                'settings' => array('link' => 0),
                'module' => 'atom_reference',
                'weight' => 1,
            ),
        ),
    );
    field_create_instance($instance);
}

// on supprime ce qui concerne time_machine si existant
$fields_page = field_info_instances("node", "page");
if(isset($fields_page['field_time_machine'])){
    $instance = field_read_instance('node', 'field_time_machine', 'page');
    field_delete_instance($instance);
    field_delete_field('field_time_machine');
}
// creation du champ field_time_machine
$field = field_read_field('field_time_machine');
if (!$field){
    $field = array(
        'field_name' => 'field_time_machine',
        'translatable' => 0,
        'entity_types' => array(),
        'settings' => array(
            'referenceable_types' => array(
                'time_machine' => 'time_machine',
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
                        'field_data_field_time_machine' => array(
                            'nid' => 'field_time_machine_nid'
                        )
                    ),
                    'FIELD_LOAD_REVISION' => array(
                        'field_revision_field_time_machine' => array(
                            'nid' => 'field_time_machine_nid'
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
        'field_name' => 'field_time_machine',
        'type' => 'node_reference',
        'module' => 'node_reference',
        'active' => 1,
        'locked' => 0,
        'cardinality' => 1,
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

// ajout du champ field_time_machine sur le contenu page
if(!isset($fields_slider['field_time_machine'])) {
    $instance = array(
        'field_name' => 'field_time_machine',
        'entity_type' => 'node',
        'label' => st('time machine'),
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

// ajout de la permission pour créer une timeline pour le manager
$role_manager = user_role_load_by_name('manager');
$manager_rid = $role_manager->rid;
$permissions = user_role_permissions( array( $manager_rid => 'manager' ) );
$permissions[$manager_rid]['create time_machine content'] = TRUE;
$permissions[$manager_rid]['edit own time_machine content'] = TRUE;
$permissions[$manager_rid]['edit any time_machine content'] = TRUE;
$permissions[$manager_rid]['delete own time_machine content'] = TRUE;
$permissions[$manager_rid]['delete any time_machine content'] = TRUE;
// Grant permissions to our 'editor' role
user_role_change_permissions($manager_rid, $permissions[$manager_rid]);


// ajout de la permission pour créer une timeline pour l admin
$role_admin = user_role_load_by_name('administrator');
$admin_rid = $role_admin->rid;
$permissions = user_role_permissions(array($admin_rid => 'administrator'));
$permissions[$admin_rid]['create time_machine content'] = TRUE;
$permissions[$admin_rid]['edit own time_machine content'] = TRUE;
$permissions[$admin_rid]['edit any time_machine content'] = TRUE;
$permissions[$admin_rid]['delete own time_machine content'] = TRUE;
$permissions[$admin_rid]['delete any time_machine content'] = TRUE;
// Grant permissions to our 'administrator' role
user_role_change_permissions($admin_rid, $permissions[$admin_rid]);

//throw new DrupalUpdateException();