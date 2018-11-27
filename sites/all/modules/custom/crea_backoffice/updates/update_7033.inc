<?php

if ($field_instance = field_read_instance('node', 'question_scientifique', 'field_subtitle')){
  $field_instance['display'] = array (
    'default' =>
      array (
        'label' => 'hidden',
        'type' => 'hidden',
        'weight' => '2',
        'settings' =>
          array (
          ),
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