<?php

/**
 * Formulaire
 */
function crea_backoffice_synchrotemp_form($form = array(), &$form_state = array()){

    $form = array();

    $form['intro'] = array(
        '#type' => 'item',
        '#markup' => '<p>'. t('Select date to synchronize temperatures data') .'</p>',
    );

    $form['date_from'] = array(
        '#type' => 'date',
        '#title' => t('From ', array(), array('context' => 'CREA_LNG')),
        '#required' => true,
    );

    if (isset($form_state['storage']['date_from'])) {
        $form['date_from']['#default_value'] = $form_state['storage']['date_from'];
    }

    $form['date_to'] = array(
        '#type' => 'date',
        '#title' => t('To ', array(), array('context' => 'CREA_LNG')),
        '#required' => true,
        '#default_value' => $form_state['date_to']
    );

    if (isset($form_state['storage']['date_to'])) {
        $form['date_to']['#default_value'] = $form_state['storage']['date_to'];
    }

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit', array(), array('context' => 'CREA_LNG'))
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

function crea_backoffice_synchrotemp_form_validate($form, &$form_state) {

    $from = mktime(0,0,0,$form_state['input']['date_from']['month'],$form_state['input']['date_from']['day'],$form_state['input']['date_from']['year']);
    $to = mktime(0,0,0,$form_state['input']['date_to']['month'],$form_state['input']['date_to']['day'],$form_state['input']['date_to']['year']);
    if($from > $to){
        form_set_error('date_from', t('Date "from" must be lower than date "to"', array(), array('context' => 'CREA_LNG')));
    }
}

/**
 * form_submit()
 * Perform submission for a form.
 * @param $form The form being used.
 * @param $form_state The form state array.
 *
 */

function crea_backoffice_synchrotemp_form_submit($form, &$form_state) {
    $form_state['storage']['date_from'] = $form_state['input']['date_from'];
    $form_state['storage']['date_to'] = $form_state['input']['date_to'];
    // Rebuild the form
    $form_state['rebuild'] = TRUE;

    $from = $form_state['input']['date_from']['year'].'-'.str_pad($form_state['input']['date_from']['month'], 2, "0", STR_PAD_LEFT).'-'.str_pad($form_state['input']['date_from']['day'], 2, "0", STR_PAD_LEFT).' 00:00:00';
    $to = $form_state['input']['date_to']['year'].'-'.str_pad($form_state['input']['date_to']['month'], 2, "0", STR_PAD_LEFT).'-'.str_pad($form_state['input']['date_to']['day'], 2, "0", STR_PAD_LEFT).' 00:00:00';
    $perlExec = "cd /home/crea-collect/CREAstations/perl && PERL5LIB=/home/crea-collect/perl5/lib/perl5 perl /home/crea-collect/CREAstations/perl/crea_sqlite_to_csv_temperatures_manual.pl '".$from."' '".$to."' > /home/crea-collect/CREAstations/perl/logs/drup_sqlitetocsv.log 2>&1";
    exec($perlExec);
    drupal_set_message(t("Synchro has been launched : ").$perlExec);
}
