<?php
$content_type_name = 'slideshow_home';
if ( ! in_array( $content_type_name, node_type_get_names() ) ) {
  $type = array(
      'type' => $content_type_name,
      'name' => t( 'Slideshow Home' ),
      'base' => 'node_content',
      'description' => t( 'Contenu du slideshow de la page d\'accueil.' ),
      'custom' => 1,
      'modified' => 1,
      'locked' => 0,
  );
  $type = node_type_set_defaults( $type );
  node_type_save( $type );
  node_add_body_field( $type );
  
  $role_manager = user_role_load_by_name('manager');
  $manager_rid = $role_manager->rid;
  $editor_permissions = array(
	'create slideshow_home content' => TRUE,
	'edit own slideshow_home content' => TRUE,
	'edit any slideshow_home content' => TRUE,
	'delete own slideshow_home content' => TRUE,
	'delete any slideshow_home content' => TRUE,
  );
  user_role_change_permissions($manager_rid, $editor_permissions);
}

$field_name = 'field_slide_link';
if ( ! field_info_field($field_name)) {
  $field = array(
      'field_name' => $field_name,
      'type' => 'link_field',
  );
  $field = field_create_field($field);

  $instance = array(
    'field_name' => $field['field_name'],
    'entity_type' => 'node',
    'description' => t('Slide link'),
    'label' => t('Link'),
    'bundle' => $content_type_name,
    'required' => FALSE,
  );
  field_create_instance($instance);
}
$field_name = 'field_slide_image';

//  Verify the field does not already exist.
if ( ! field_info_field( $field_name ) ) {
  $field = array(
      'field_name' => $field_name,
      'type' => 'atom_reference',
  );
  $field = field_create_field( $field );
  $instance = array(
      'field_name' => $field_name ,
      'entity_type' => 'node',
      'label' => t('Slide image'),
      'bundle' => $content_type_name,
      'required' => 1,
      'settings' => array(
          'referencable_types' => array(
              'image' => 'image',
          ),
          'user_register_form' => FALSE,
          'file_directory' => 'slideshow_home',
      ),
      'widget' => array(
          'weight' => 1,
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

  
  //  Create an instance of the field and bind it to the bundle.
  field_create_instance($instance);
}