<?php 

function crea_users_saisir_faune_flore_form($form, &$form_state){
	drupal_add_js(drupal_get_path('module', 'crea_users') . '/js/saisir.js');

	$path = explode('/', current_path());

    $edit = false;
    $idObs = null;
    if(count($path) == 3){
        $idObs = (int)$path[2];
        if(is_int($idObs) && $idObs != 0){
            $edit = true;
        }
    }

    $espece = null;

    if($edit === true){
        $db_data = Database::getConnection('geonaturedb','default');

        $sqlObs = 'SELECT id_synthese, id_fiche_source, id_protocole, cd_nom, dateobs, observateurs, altitude_retenue,
                ST_X (ST_Transform (the_geom_2154, 4326)) AS pntx,
                ST_Y (ST_Transform (the_geom_2154, 4326)) AS pnty,
                remarques
                FROM "synthese".syntheseff
                WHERE id_synthese = '.$idObs.' 
                AND supprime = FALSE
                ORDER BY dateobs DESC';

        $resObs = $db_data->query($sqlObs);
        $observations = $resObs->fetchAll();
        if(count($observations) > 0){
            $obs = $observations[0];
            $dateObs = $obs->dateobs;
            $lat = $obs->pnty;
            $lng = $obs->pntx;
            $altitude = $obs->altitude;
            $protocole = $obs->id_protocole;
            $espece = $obs->cd_nom;
            $idReleve = $obs->id_fiche_source;
            /*$sqlObs = 'SELECT id_synthese, id_fiche_source, id_protocole, cd_nom, dateobs, observateurs, altitude_retenue,
                ST_X (ST_Transform (the_geom_2154, 4326)) AS pntx,
                ST_Y (ST_Transform (the_geom_2154, 4326)) AS pnty,
                remarques
                FROM "synthese".syntheseff
                WHERE id_synthese = '.$idObs.' 
                AND supprime = FALSE
                ORDER BY dateobs DESC';

            $resObs = $db_data->query($sqlObs);
            $observations = $resObs->fetchAll();*/
            $remarques = $obs->remarques;
        }
    }
	
	$form = array();

	$form['date_obs'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'd-m-Y',
		'#title' => t('Observation date'),
		'#date_label_position' => 'hidden',
		'#required' => true,
		'#size' => 50,
        '#default_value' => isset($dateObs) ? $dateObs : '',
	);

	$form['latitude'] = array(
		'#type' => 'textfield',
		'#title' => t('Latitude'),
		'#required' => true,
		'#description' => t('in decimal degrees : for example 46.26458'),
        '#default_value' => isset($lat) ? $lat : '',
	);

	$form['longitude'] = array(
		'#type' => 'textfield',
		'#title' => t('Longitude'),
		'#required' => true,
		'#description' => t('in decimal degrees : for example 7.28634'),
        '#default_value' => isset($lng) ? $lng : '',
	);

	$form['altitude'] = array(
		'#type' => 'textfield',
		'#title' => t('Altitude'),
        '#default_value' => isset($altitude) ? $altitude : '',
	);
	
	$taxon_tree = crea_get_available_taxons();
	$groups_name = unserialize(TAXONS_GROUPS);
	$protocoles = array();
	$groupes = array();
	
	foreach ($taxon_tree AS $protocol => $group){
		$protocoles[$protocol] = $protocol;
	}
	
	$form['protocole'] = array(
		'#type' => 'radios',
		'#options' => $protocoles,
		'#title' => t('Protocol'),
        '#default_value' => isset($protocole) ? $protocole : '',
		'#required' => false,
		'#multiple' => false,
	);
	
	foreach ($taxon_tree AS $protocol => $group){
		foreach ($group AS $group_id => $taxons){
			foreach ($taxons AS $key_taxon => $taxon){
				if (isset($groups_name[$group_id])){
					$groupes[$groups_name[$group_id]][$key_taxon] = $taxon;
				}
			}
		}
	}
	//$groupes['other'] = t('Other');
	
	drupal_add_js(array('CreaTaxonsGroupes' => array('taxon_tree' => $taxon_tree, 'groups_name' => $groups_name, 'espece' => $espece)), 'setting');
	
	$form['taxon'] = array(
		'#type' => 'select',
		'#options' => $groupes,
		'#title' => t('Species'),
        '#default_value' => isset($espece) ? $espece : '',
		'#required' => true,
	);

	$form['remarques'] = array(
		'#type' => 'textarea',
		'#title' => t('Comment'),
        '#default_value' => isset($remarques) ? $remarques : '',
	);

	if($edit === true){
        $sql_file = 'SELECT id_file FROM "prot_faune_flore_simple".t_releves_pffs 
        WHERE id_releve_pffs = :id_pffs';

        $res_file = $db_data->query($sql_file, array(
            ':id_pffs' => $idReleve,
        ))->fetchAssoc();
        if(isset($res_file['id_file'])){
            $idFile = $res_file['id_file'];
        }
    }
	
	$form['upload'] = array(
		'#type' => 'managed_file',
		'#title' => t('Choose a file'),
		'#description' => t('available formats : jpg, png, gif'),
		'#upload_location' => 'public://saisir/images',
		'#upload_validators' => array(
			'file_validate_extensions' => array('png gif jpg jpeg'),
		),
        '#default_value' => isset($idFile) ? $idFile : '',
		'#required' => false,
	);

    $form['edition'] = array(
        '#type' => 'hidden',
        '#default_value' => $edit === true ? 1 : 0,
    );

    $form['idObs'] = array(
        '#type' => 'hidden',
        '#default_value' => $idObs,
    );

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
    '#attributes' => array('class' => array('crea-button no-icon orange-button-link'))
);

	return $form;
}

function crea_users_saisir_faune_flore_form_validate(&$form, &$form_state){
	global $user;
	
	if (isset($user->name)
	&& isset($user->mail)){
		$geonatuser = verifyIfUserExistsInExternalBDD('geonaturedb', $user->name, $user->mail);
		if (empty($geonatuser)){
			form_set_error('', t('Unrecognized user'));
		}
	}
	
	$crea_available_taxons = variable_get('crea_available_taxons', array());
	if (isset($form_state['values']['taxon'])
	&& !in_array($form_state['values']['taxon'], $crea_available_taxons)){
		form_set_error('taxon', t('You have selected an invalide species.'));
	}
}

function crea_users_saisir_faune_flore_form_submit(&$form, &$form_state){
  global $user;
  $observation = array();
  if (isset($form_state['values'])) {
    // on récupère la date de la dernière obs de l'utilisateur
    $username = $user->data['profile']['last_name'].' '.$user->data['profile']['first_name'];
    $canInsert = canUserInsertObs('geonaturedb', $username);
    if($canInsert === true) {
      $observation['date_obs'] = isset($form_state['values']['date_obs']) ? filter_xss($form_state['values']['date_obs']) : '';
      $observation['latitude'] = isset($form_state['values']['latitude']) ? filter_xss(str_replace(',', '.', $form_state['values']['latitude'])) : '';
      $observation['longitude'] = isset($form_state['values']['longitude']) ? filter_xss(str_replace(',', '.', $form_state['values']['longitude'])) : '';
      $observation['altitude'] = isset($form_state['values']['altitude']) ? filter_xss($form_state['values']['altitude']) : '';
      $observation['remarques'] = isset($form_state['values']['remarques']) ? filter_xss($form_state['values']['remarques']) : '';
      $observation['id_file'] = isset($form_state['values']['upload']) ? filter_xss($form_state['values']['upload']) : '';

      $crea_available_taxons = variable_get('crea_available_taxons', array());
      if (isset($form_state['values']['taxon'])
        && in_array($form_state['values']['taxon'], $crea_available_taxons)
      ) {
        $taxon = getGetonatureTaxonInformation($form_state['values']['taxon']);
        if (is_object($taxon)) {
          $observation['taxon_cd_nom'] = $taxon->cd_nom;
          $observation['taxon_id'] = $taxon->id_nom;
          $observation['nom_francais'] = $taxon->nom_francais;
        } else {
          form_set_error('taxon', t('You have selected an invalide species.'));
        }

      } else {
        form_set_error('taxon', t('You have selected an invalide species.'));
      }

      if (is_numeric($form_state['values']['upload']) && $form_state['values']['upload'] > 0) {
        // Load the file via file.fid.
        $file = file_load($form_state['values']['upload']);
        if ($file) {
          // Change status to permanent.
          $file->status = FILE_STATUS_PERMANENT;
          // Save.
          file_save($file);
          // Record that the module (in this example, user module) is using the file.
          file_usage_add($file, 'user', 'user', $user->uid);
        }
      }

      $geonatuser = verifyIfUserExistsInExternalBDD('geonaturedb', $user->name, $user->mail);
      $observation['id_role'] = current($geonatuser)->id_role;

      if($form_state['values']['edition'] == 1){
          $observation['idObs'] = $form_state['values']['idObs'];
          crea_modify_protocole_faune_flore_observation($observation);
          drupal_set_message(t('Your observation has been modified. You can see it on the website now. Thanks'), 'status');
      }else{
          crea_save_protocole_faune_flore_observation($observation);
          drupal_set_message(t('Your observation has been saved. You can see it on the website now. Thanks'), 'status');
      }
    }
  }
}