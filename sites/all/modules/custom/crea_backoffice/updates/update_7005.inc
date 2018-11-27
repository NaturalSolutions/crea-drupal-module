<?php

// Activation du site name dans le thème crea
$theme_crea_settings = variable_get('theme_crea_settings');
$theme_crea_settings['toggle_name'] = 1;
variable_set('theme_crea_settings', $theme_crea_settings);

// Placement des blocs
// block de recherche
db_update('block')
->fields(array('region' => 'header','status' => '1'))
->condition('theme', 'crea', '=')
->condition('module', 'search', '=')
->execute();

// block langue switcher
db_update('block')
->fields(array('region' => 'header', 'status' => '1'))
->condition('theme', 'crea', '=')
->condition('module', 'locale', '=')
->execute();

// ajout de la permission pour voir le block search
$role_admin = user_role_load_by_name('anonymous user');
$admin_rid = $role_admin->rid;
$permissions = user_role_permissions(array($admin_rid => 'anonymous user'));
$permissions[$admin_rid]['search content'] = TRUE;
user_role_change_permissions($admin_rid, $permissions[$admin_rid]);

$role_admin = user_role_load_by_name('authenticated user');
$admin_rid = $role_admin->rid;
$permissions = user_role_permissions(array($admin_rid => 'authenticated user'));
$permissions[$admin_rid]['search content'] = TRUE;
user_role_change_permissions($admin_rid, $permissions[$admin_rid]);

// Suppréssion du cache
drupal_flush_all_caches();

//throw new DrupalUpdateException();