<?php

// ajout d'une option "orange" à la liste des entités visuelles
$field = field_read_field('field_identite_visuelle');
if ($field) {
  $field['settings']['allowed_values'] = array(
    'blue-layout' => 'bleu',
    'green-layout' => 'vert',
    'orange-layout' => 'orange',
  );
  field_update_field($field);
}