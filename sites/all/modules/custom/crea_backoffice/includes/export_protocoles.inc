<?php 

function crea_backoffice_export_protocoles_form($form, &$form_state){

	$form = array();
	
	$form['explication'] = array(
		'#markup' => '<p>' . t('Choisissez votre protocole :') . '</p>'
	);
	
	$form['protocole'] = array(
        '#title' => t('Protocole'),
	    '#type' => 'select',
        '#options' => array('grenouille' => 'grenouille','mesange' => 'mesange')
	);
	
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Download')
	);
	
	return $form;
}

function crea_backoffice_export_protocoles_form_submit(&$form, &$form_state){

    drupal_add_http_header('Content-Type', 'text/csv; utf-8');
    drupal_add_http_header('Content-Disposition', 'attachment; filename=protocole_'.$form_state['values']['protocole'].'.csv');

    $output = '';
    $keys = array();

    if($form_state['values']['protocole'] == 'grenouille') {
        $headers = array('ID FICHE','SITE', 'ESPECE', 'DATE', 'STADE', 'NBPONTES');
    }
    if($form_state['values']['protocole'] == 'mesange') {
        $headers = array('ID FICHE', 'SITE', 'NICHOIR', 'ESPECE', 'DATE', 'STADE', 'TAILLE PONTE', 'TAILLE NICHEE', 'AGE PLUME', 'HAUTEUR NID');
    }

    foreach ($headers as $value) {
        $keys[] = $value;
    }
    if ($keys) {
        $output .= implode(";", $keys) . "\n";
    }

    $db_data = Database::getConnection('geonaturedb','default');

    if($form_state['values']['protocole'] == 'grenouille'){
        $sql = 'SELECT f.id_pgre, f.dateobs, f.nom_lieu, r.nom_taxon_saisi, r.stade, r.nbr_pontes 
                FROM "prot_grenouille".t_fiches_pgre f, "prot_grenouille".t_releves_pgre r 
                WHERE r.id_pgre = f.id_pgre
                ORDER BY f.id_pgre;';
    }
    if($form_state['values']['protocole'] == 'mesange'){
        $sql = 'SELECT f.id_pmes, f.dateobs, f.nom_lieu, r.nichoir, r.nom_taxon_saisi, r.stade_nid, r.taille_ponte, r.taille_nichee, r.age_plume, r.hauteur_nid 
                FROM "prot_mesange".t_fiches_pmes f, "prot_mesange".t_releves_pmes r 
                WHERE r.id_pmes = f.id_pmes
                ORDER BY f.id_pmes;';
    }

    $res_prot = $db_data->query($sql)->fetchAll();

    db_set_active();

    foreach($res_prot as $r){

        if($form_state['values']['protocole'] == 'grenouille') {
            $output .= $r->id_pgre . ';';
        }
        if($form_state['values']['protocole'] == 'mesange') {
            $output .= $r->id_pmes . ';';
        }

        $output .= $r->nom_lieu . ';';
        if($form_state['values']['protocole'] == 'mesange') {
            $output .= $r->nichoir . ';';
        }
        $output .= utf8_decode($r->nom_taxon_saisi) . ';';
        $output .= $r->dateobs . ';';

        if($form_state['values']['protocole'] == 'grenouille') {
            $output .= $r->stade . ';';
            $output .= $r->nbr_pontes . ';';
        }

        if($form_state['values']['protocole'] == 'mesange') {
            $output .= $r->stade_nid . ';';
            $output .= $r->taille_ponte . ';';
            $output .= $r->taille_nichee . ';';
            $output .= $r->age_plume . ';';
            $output .= $r->hauteur_nid . ';';
        }

        $output .= "\n";
    }

    print $output;
    drupal_exit();
}