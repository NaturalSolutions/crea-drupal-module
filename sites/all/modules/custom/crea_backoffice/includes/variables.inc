<?php

/**
 * Implements hook_permission().
 */
function crea_backoffice_permission() {
    return array(
        'Edit CREA variables' => array(
            'title' => t('Edit CREA variables'),
        ),
    );
}

/**
 * Implements hook_variable_group_info().
 */
function crea_backoffice_variable_group_info() {
    $groups['crea_variable'] = array(
        'title' => t('CREA'),
        'description' => t('Specific variables'),
        'access' => 'Edit CREA variables',
    );

    return $groups;
}