<?php

/**
 * Formulaire
 */
function crea_gn_protocols_import_form($form = array(), &$form_state = array()){

    $form = array();

    $form['intro'] = array(
        '#type' => 'item',
        '#markup' => '<p>'. t('Select a protocol and a file. The file must be a .zip with one (or more) CSV', array(), array('context' => 'CREA_LNG')) .'</p>',
    );

    $protocoles = variable_get('geonature_protocols');
    $protocoles = unserialize($protocoles);

    $form['protocole'] = array(
        '#type' => 'select',
        '#title' => t('Protocol', array(), array('context' => 'CREA_LNG')),
        '#options' => $protocoles,
    );

    $form['file'] = array(
        '#type' => 'managed_file',
        '#title' => t('File', array(), array('context' => 'CREA_LNG')),
    	'#description' => t('valide format' . ' : zip'),
        '#title_display' => 'before',
        '#upload_location' => 'public://crea/protocol/',
        '#upload_validators' => array('file_validate_extensions' => array('zip')),
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Send', array(), array('context' => 'CREA_LNG')),
    );

    return $form;
}

/**
 * form_validate()
 * Perform validation before a form is submitted.
 * @param $form The form being used.
 * @param $form_state The form state array.
 *
 */

function crea_gn_protocols_import_form_validate($form, &$form_state) {

    if($form_state['input']['protocole'] != ""){

        if($form_state['input']['file']){
            $file = file_load($form_state['values']['file']);
            // check if directories exist
            if(!file_exists('public://crea/protocol/'.$form_state['input']['protocole'])){
                drupal_mkdir('public://crea/protocol/'.$form_state['input']['protocole'], null, true );
                drupal_chmod('public://crea/protocol/'.$form_state['input']['protocole'], 0777);
            }
            // Move the file into the Drupal file system.
            $mv = file_unmanaged_move($file->uri, 'public://crea/protocol/' . $form_state['input']['protocole']. '/' . date("Ymd_His") . '_PROTOCOL_' . $form_state['input']['protocole'] . '.zip', FILE_EXISTS_REPLACE);
            if ($mv === false) {
                form_set_error('file', t("Failed to write the uploaded file to the site's file folder.", array(), array('context' => 'CREA_LNG')));
            }
            else{
            	drupal_chmod($mv, 0777);
            }
            file_delete($file);
        }else{
            form_set_error('file', t('Problem with the file', array(), array('context' => 'CREA_LNG')));
        }

    }else{
        form_set_error('protocole', t('Choose a protocol', array(), array('context' => 'CREA_LNG')));
    }
}

/**
 * form_submit()
 * Perform submission for a form.
 * @param $form The form being used.
 * @param $form_state The form state array.
 *
 */

function crea_gn_protocols_import_form_submit($form, &$form_state) {
    drupal_set_message(t("File has been uploaded", array(), array('context' => 'CREA_LNG')));
    
    $perlExec = "/usr/bin/perl /home/crea-web/scripts/test_unzip.pl";
    exec($perlExec);
}
