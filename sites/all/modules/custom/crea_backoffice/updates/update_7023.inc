<?php

// création des nouvelles instances de champ KMZ, slider et time machine
$fields = array('field_slider', 'field_time_machine', 'field_module_kmz');

foreach ($fields AS $field_name){
  if (is_null(field_info_instance('field_collection_item', $field_name, 'field_body_wrapper'))
  && $field_instance = field_info_instance('node', $field_name, 'page')){
    $field_instance['entity_type'] = 'field_collection_item';
    $field_instance['bundle'] = 'field_body_wrapper';

    $field_instance['display']['default']['label'] = 'hidden';

    field_create_instance($field_instance);
  }
}

// ajout au field group
$group = field_group_load_field_group('group_collection_contenu', 'field_collection_item', "field_body_wrapper", 'form');
foreach ($fields AS $field_name){
  if (!in_array($field_name, $group->children)){
    $group->children[] = $field_name;
  }
}
field_group_group_save($group);
