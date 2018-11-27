<?php 

function crea_backoffice_sqlite_reqdeletedatastation_form($form, &$form_state){

	$form = array();
	
	$form['explication'] = array(
		'#markup' => '<p>' . t('Sélectionnez la station et la période, la requête sera exécutée directement sur la base SQLITE') . '</p>'
	);

    $stations = array();
    $query = db_select('node', 'n');
    $query->join('field_data_field_id', 'nfid', 'nfid.entity_id = n.nid');
    $query->fields('n', array('title', 'nid'))
        ->fields('nfid', array('field_id_value'))
        ->condition('n.type', 'station')
        ->condition('nfid.bundle', 'station')
        ->orderBy('n.title');

    $results = $query->execute()->fetchAll();

    foreach($results AS $result){
        $stations[$result->field_id_value] = $result->title . ' (' . $result->field_id_value . ')';
    }

    $form['station'] = array(
        '#title' => t('Station'),
        '#type' => 'select',
        '#options' => $stations
    );

    $date_deb = '2017-01-01 00:00:00';
    $date_fin = '2017-01-01 00:00:00';
    $format = 'd-m-Y H:i:s';

    $form['date_debut'] = array(
        '#title' => t('Date début'),
        '#type' => 'date_select',
        '#default_value' => $date_deb,
        '#date_format' => $format,
        '#date_label_position' => 'within',
        '#date_year_range' => '-50:+3',
        '#date_increment' => 15,
    );

    $form['date_fin'] = array(
        '#title' => t('Date fin'),
        '#type' => 'date_select',
        '#default_value' => $date_fin,
        '#date_format' => $format,
        '#date_label_position' => 'within',
        '#date_year_range' => '-50:+3',
        '#date_increment' => 15,
    );

	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Exécuter')
	);
	
	return $form;
}

function crea_backoffice_sqlite_reqdeletedatastation_form_submit(&$form, &$form_state){
    $form_state['rebuild'] = TRUE;
    // exécution
    if(isset($form_state['input']['station'])
        && isset($form_state['input']['date_debut'])
        && isset($form_state['input']['date_fin'])
    ) {
        $deb = $form_state['input']['date_debut'];
        $fin = $form_state['input']['date_fin'];

        $station = $form_state['input']['station'];
        $from = $deb['year'].'-'.str_pad($deb['month'], 2, "0", STR_PAD_LEFT).'-'.str_pad($deb['day'], 2, "0", STR_PAD_LEFT).' '.
            str_pad($deb['hour'], 2, "0", STR_PAD_LEFT).':'.str_pad($deb['minute'], 2, "0", STR_PAD_LEFT).':'.str_pad($deb['second'], 2, "0", STR_PAD_LEFT);
        $to = $fin['year'].'-'.str_pad($fin['month'], 2, "0", STR_PAD_LEFT).'-'.str_pad($fin['day'], 2, "0", STR_PAD_LEFT).' '.
            str_pad($fin['hour'], 2, "0", STR_PAD_LEFT).':'.str_pad($fin['minute'], 2, "0", STR_PAD_LEFT).':'.str_pad($fin['second'], 2, "0", STR_PAD_LEFT);

        $perlExec = DIRECTORY_SEPARATOR."usr".DIRECTORY_SEPARATOR."bin".DIRECTORY_SEPARATOR."perl ".DIRECTORY_SEPARATOR."home".DIRECTORY_SEPARATOR."crea-web".DIRECTORY_SEPARATOR."scripts".DIRECTORY_SEPARATOR."crea_sqlite_requete_deletestation.pl ". escapeshellarg($station)." ". escapeshellarg($from)." ". escapeshellarg($to)." > ".DIRECTORY_SEPARATOR."dev".DIRECTORY_SEPARATOR."null &";
        exec($perlExec);
        drupal_set_message(t("Requête de suppression lancée sur la SQLITE : ").$perlExec);
    }
}

function crea_backoffice_sqlite_reqchangestation_form($form, &$form_state){

    $form = array();

    $form['explication'] = array(
        '#markup' => '<p>' . t('Sélectionnez la station à changer, celle à remplacer et la période. La requête sera exécutée directement sur la base SQLITE') . '</p>'
    );

    $stations = array();
    $query = db_select('node', 'n');
    $query->join('field_data_field_id', 'nfid', 'nfid.entity_id = n.nid');
    $query->fields('n', array('title', 'nid'))
        ->fields('nfid', array('field_id_value'))
        ->condition('n.type', 'station')
        ->condition('nfid.bundle', 'station')
        ->orderBy('n.title');

    $results = $query->execute()->fetchAll();

    foreach($results AS $result){
        $stations[$result->field_id_value] = $result->title . ' (' . $result->field_id_value . ')';
    }

    $form['station_from'] = array(
        '#title' => t('Station à remplacer'),
        '#type' => 'select',
        '#options' => $stations
    );

    $form['station_to'] = array(
        '#title' => t('Station de remplacement'),
        '#type' => 'select',
        '#options' => $stations
    );

    $date_deb = '2017-01-01 00:00:00';
    $date_fin = '2017-01-01 00:00:00';
    $format = 'd-m-Y H:i:s';

    $form['date_debut'] = array(
        '#title' => t('Date début'),
        '#type' => 'date_select',
        '#default_value' => $date_deb,
        '#date_format' => $format,
        '#date_label_position' => 'within',
        '#date_year_range' => '-50:+3',
        '#date_increment' => 15,
    );

    $form['date_fin'] = array(
        '#title' => t('Date fin'),
        '#type' => 'date_select',
        '#default_value' => $date_fin,
        '#date_format' => $format,
        '#date_label_position' => 'within',
        '#date_year_range' => '-50:+3',
        '#date_increment' => 15,
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Exécuter')
    );

    return $form;
}

function crea_backoffice_sqlite_reqchangestation_form_submit(&$form, &$form_state){
    $form_state['rebuild'] = TRUE;
    // exécution
    if(isset($form_state['input']['station_from'])
        && isset($form_state['input']['station_to'])
        && isset($form_state['input']['date_debut'])
        && isset($form_state['input']['date_fin'])
    ) {
        $deb = $form_state['input']['date_debut'];
        $fin = $form_state['input']['date_fin'];

        $station_from = $form_state['input']['station_from'];
        $station_to = $form_state['input']['station_to'];
        $from = $deb['year'].'-'.str_pad($deb['month'], 2, "0", STR_PAD_LEFT).'-'.str_pad($deb['day'], 2, "0", STR_PAD_LEFT).' '.
            str_pad($deb['hour'], 2, "0", STR_PAD_LEFT).':'.str_pad($deb['minute'], 2, "0", STR_PAD_LEFT).':'.str_pad($deb['second'], 2, "0", STR_PAD_LEFT);
        $to = $fin['year'].'-'.str_pad($fin['month'], 2, "0", STR_PAD_LEFT).'-'.str_pad($fin['day'], 2, "0", STR_PAD_LEFT).' '.
            str_pad($fin['hour'], 2, "0", STR_PAD_LEFT).':'.str_pad($fin['minute'], 2, "0", STR_PAD_LEFT).':'.str_pad($fin['second'], 2, "0", STR_PAD_LEFT);

        $perlExec = DIRECTORY_SEPARATOR."usr".DIRECTORY_SEPARATOR."bin".DIRECTORY_SEPARATOR."perl ".DIRECTORY_SEPARATOR."home".DIRECTORY_SEPARATOR."crea-web".DIRECTORY_SEPARATOR."scripts".DIRECTORY_SEPARATOR."crea_sqlite_requete_changestation.pl ".escapeshellarg($station_from)." ".escapeshellarg($station_to)." ".escapeshellarg($from)." ".escapeshellarg($to)." > ".DIRECTORY_SEPARATOR."dev".DIRECTORY_SEPARATOR."null &";
        exec($perlExec);

        drupal_set_message(t("Requête de changement lancée sur la SQLITE : ").$perlExec);
    }
}