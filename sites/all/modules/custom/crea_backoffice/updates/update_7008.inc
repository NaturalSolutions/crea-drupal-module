<?php

// Activation du module scald_file
$enable_dependencies = TRUE;
module_enable(array('scald_file'), $enable_dependencies);

// ajustement de la configuration pour les pages vis a vis des atoms
$instance = field_info_instance('node', 'field_media', 'page');
$instance['settings']['referencable_types'] = array(
    'audio' => 'audio',
    'flash' => 'flash',
    'image' => 'image',
    'video' => 'video',
    'file' => 'file'
);
field_update_instance($instance);

// droits pour scald file et les autres oubliés
// ajout de la permission pour créer un atom pour le manager
$role_manager = user_role_load_by_name('manager');
$manager_rid = $role_manager->rid;
$permissions = user_role_permissions( array( $manager_rid => 'manager' ) );
$permissions[$manager_rid]['create atom of any type'] = TRUE;
$permissions[$manager_rid]['create atom of audio type'] = TRUE;
$permissions[$manager_rid]['create atom of flash type'] = TRUE;
$permissions[$manager_rid]['create atom of image type'] = TRUE;
$permissions[$manager_rid]['create atom of video type'] = TRUE;
$permissions[$manager_rid]['create atom of file type'] = TRUE;
user_role_change_permissions($manager_rid, $permissions[$manager_rid]);


// ajout de la permission pour créer un atom pour l admin
$role_admin = user_role_load_by_name('administrator');
$admin_rid = $role_admin->rid;
$permissions = user_role_permissions(array($admin_rid => 'administrator'));
$permissions[$admin_rid]['create atom of any type'] = TRUE;
$permissions[$admin_rid]['create atom of audio type'] = TRUE;
$permissions[$admin_rid]['create atom of flash type'] = TRUE;
$permissions[$admin_rid]['create atom of image type'] = TRUE;
$permissions[$admin_rid]['create atom of video type'] = TRUE;
$permissions[$admin_rid]['create atom of file type'] = TRUE;
user_role_change_permissions($admin_rid, $permissions[$admin_rid]);

// champ field_links sur les pages
// on supprime ce qui concerne field_links si existant
$fields_page = field_info_instances("node", "page");
if(isset($fields_page['field_links'])){
    $instance = field_read_instance('node', 'field_links', 'page');
    field_delete_instance($instance);
    field_delete_field('field_links');
}
// creation du champ field_links
$field = field_read_field('field_links');
if (!$field){
    $field = array(
        'translatable'=> 0,
        'entity_types' => array(),
        'settings' => array(
            'attributes' => array(
                'target' => 'default',
                'class' => '',
                'rel' => '',
            ),
            'url' => 0,
            'title' => 'optional',
            'title_value' => '',
            'title_maxlength' => 128,
            'enable_tokens' => 1,
            'display' => array(
                'url_cutoff' => 80
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
                        'field_data_field_links' => array(
                            'url' => 'field_links_url',
                            'title' => 'field_links_title',
                            'attributes' => 'field_links_attributes'
                        )

                    ),
                    'FIELD_LOAD_REVISION' => array(
                        'field_revision_field_links' => array(
                            'url' => 'field_links_url',
                            'title' => 'field_links_title',
                            'attributes' => 'field_links_attributes'
                        )
                    )
                )
            )
        ),
        'foreign keys' => array(),
        'indexes' => array(),
        'field_name' => 'field_links',
        'type' => 'link_field',
        'module' => 'link',
        'active' => 1,
        'locked' => 0,
        'cardinality' => -1,
        'deleted' => 0,
        'columns' => array(
            'url' => array(
                'type' => 'varchar',
                'length' => 2048,
                'not null' => '',
                'sortable' => 1,
            ),
            'title' => array(
                'type' => 'varchar',
                'length' => 255,
                'not null' => '',
                'sortable' => 1,
            ),
            'attributes' => array(
                'type' => 'text',
                'size' => 'medium',
                'not null' => ''
            )
        )
    );

    field_create_field($field);
}

// ajout du champ field_links sur le contenu page
if(!isset($fields_page['field_links'])) {
    $instance = array(
        'label' => st('Links'),
        'widget' => array(
            'type' => 'link_field',
            'module' => 'link',
            'active' => 0,
            'settings' => array()
        ),
        'settings' => array(
            'absolute_url' => 1,
            'validate_url' => 1,
            'url' => 0,
            'title' => 'optional',
            'title_value' => '',
            'title_label_use_field_label' => 0,
            'title_maxlength' => 128,
            'enable_tokens' => 1,
            'display' => array(
                'url_cutoff' => 80
            ),
            'attributes' => array(
                'target' => 'default',
                'rel' => '',
                'configurable_class' => 0,
                'class' => '',
                'configurable_title' => 0,
                'title' => '',
            ),
            'rel_remove' => 'default',
            'linkit' => array(
                'enable' => 0,
                'profile' => '',
                'button_text' => 'Search'
            ),
            'user_register_form' => ''
        ),
        'display' => array(
            'default' => array(
                'label' => 'above',
                'type' => 'link_default',
                'settings' => array(),
                'module' => 'link',
            ),
            'teaser' => array(
                'type' => 'hidden',
                'label' => 'above',
                'settings' => array(),
                'weight' => 0
            )
        ),
        'required' => 0,
        'description' => '',
        'default_value' => '',
        'field_name' => 'field_links',
        'entity_type' => 'node',
        'bundle' => 'page',
        'deleted' => 0
    );
    field_create_instance($instance);
}

//throw new DrupalUpdateException();