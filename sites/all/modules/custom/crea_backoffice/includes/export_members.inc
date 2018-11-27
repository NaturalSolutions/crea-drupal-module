<?php 

function crea_backoffice_export_members_form($form, &$form_state){

	$form = array();
	
	$form['explication'] = array(
		'#markup' => '<p>' . t('Export members of the Drupal website') . '</p>'
	);

	$form['only_newsletter'] = array(
        '#title' => t('Only with newsletter'),
	    '#type' => 'checkbox',
        '#default_value' => true
	);

    $form['date_deb'] = array(
        '#title' => t('Date début'),
        '#type' => 'date',
        '#default_value' =>  array('year' => 2015, 'month' => 1, 'day' => 1)
    );

    $form['date_fin'] = array(
        '#title' => t('Date fin'),
        '#type' => 'date',
    );
	
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Download')
	);
	
	return $form;
}

function crea_backoffice_export_members_form_submit(&$form, &$form_state){
    $onlyNews = true;
    if (!isset($form_state['values']['only_newsletter'])
        || $form_state['values']['only_newsletter'] == 0
        ){
        $onlyNews = false;
    }

    $date_deb = $form_state['values']['date_deb'];
    $date_fin = $form_state['values']['date_fin'];

    $mktime_deb = mktime(0,0,0,$date_deb['month'],$date_deb['day'],$date_deb['year']);
    $mktime_fin = mktime(23,59,59,$date_fin['month'],$date_fin['day'],$date_fin['year']);

    drupal_add_http_header('Content-Type', 'text/csv; utf-8');
    drupal_add_http_header('Content-Disposition', 'attachment; filename=exportUsers.csv');

    $output = '';
    $keys = array();
    $headers = array('UID', 'PSEUDO', 'MAIL', 'PRENOM', 'NOM', 'CP', 'VILLE', 'MEMBRE CREA', 'NEWSLETTER', 'CREATION');

    foreach ($headers as $value) {
        $keys[] = $value;
    }
    if ($keys) {
        $output .= implode(";", $keys) . "\n";
    }

    // requete BDD
    $query = db_select('users', 'u');
    $query->fields('u', array('uid', 'name', 'mail', 'data', 'created'))
          ->condition('u.status', '1', '=')
          ->condition('u.created', $mktime_deb, '>=')
          ->condition('u.created', $mktime_fin, '<=')
          ->orderBy('u.uid');

    $users = $query->execute()->fetchAll();

    foreach($users as $u){
        $insertUser = false;
        $data = unserialize($u->data);
        if((int)$onlyNews == 1){
            if(isset($data['profile']['receive_newsletter']) && $data['profile']['receive_newsletter'] == "1"){
                $insertUser = true;
            }
        }else{
            $insertUser = true;
        }

        if($insertUser == true) {
            $output .= $u->uid . ';' .
                utf8_decode($u->name) . ';' .
                utf8_decode($u->mail) . ';';

            if (isset($data['profile']['first_name'])) {
                $output .=  utf8_decode($data['profile']['first_name']) . ';';
            } else {
                $output .= '' . ';';
            }
            if (isset($data['profile']['last_name'])) {
                $output .=  utf8_decode($data['profile']['last_name']) . ';';
            } else {
                $output .= '' . ';';
            }
            if (isset($data['profile']['postal_code'])) {
                $output .=  utf8_decode($data['profile']['postal_code']) . ';';
            } else {
                $output .= '' . ';';
            }
            if (isset($data['profile']['city'])) {
                $output .=  utf8_decode($data['profile']['city']) . ';';
            } else {
                $output .= '' . ';';
            }
            if (isset($data['profile']['crea_member'])) {
                $output .=  utf8_decode($data['profile']['crea_member']) . ';';
            } else {
                $output .= '' . ';';
            }
            if (isset($data['profile']['receive_newsletter'])) {
                $output .=  utf8_decode($data['profile']['receive_newsletter']) . ';';
            } else {
                $output .= '' . ';';
            }
            if (isset($u->created)) {
                $output .=  date("d-m-Y", $u->created) . ';';
            } else {
                $output .= '' . ';';
            }
            $output .= "\n";
        }
    }

    print $output;
    drupal_exit();
}