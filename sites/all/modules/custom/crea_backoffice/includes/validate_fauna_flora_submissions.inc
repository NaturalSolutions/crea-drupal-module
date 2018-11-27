<?php 

function crea_backoffice_validate_pffs_submissions_form($form, &$form_state){
	global $base_url, $conf;
	$form = array();
	
	$observations = getGeonaturePFFSUnpublishedObservations();
	//creaDump::lock($observations);
	
	$header = array(
		'name' => array('field' => 'name', 'data' => t('name'), 'sort'=> 'asc'),
		'species' => array('field' => 'species', 'data' => t('species'), 'sort'=> 'asc'),
		'date_obs' => array('field' => 'date_obs', 'data' => t('date obs'), 'sort'=> 'asc'),
		'date_insert' => array('field' => 'date_insert', 'data' => t('date insert'), 'sort'=> 'asc'),
		'altitude' => array('data' => t('altitude')),
		'remarque' => array('data' => t('remarque')),
		'photo' => array('data' => t('photo')),
	);
	
	$options = array();
	$markers = array();
	
	foreach ($observations AS $observation){
		if (isset($observation->id_file)
		&& $observation->id_file !== ''){
			$id_img = filter_xss($observation->id_file);
			$img_file = file_load($id_img);
			$img = theme_image_style(array(
				"style_name" => 'thumbnail',
				"path" => $img_file->uri,
				"title" => '',
				"alt" => '',
				"width" => NULL,
				"height" => NULL,
			));
			$img_link = l($img, file_create_url($img_file->uri), array('html' => true, 'attributes' => array('class' => array('colorbox'))));
		}
		else{
			$img_link = '';
		}
		$options[$observation->id_pffs] = array(
			'name' => filter_xss($observation->nom_role) . ' ' . filter_xss($observation->prenom_role),
			'species' => filter_xss($observation->nom_taxon_saisi),
			'date_obs' => filter_xss($observation->dateobs),
			'date_insert' => filter_xss($observation->date_insert),
			'altitude' => filter_xss($observation->altitude),
			'remarque' => filter_xss($observation->commentaire),
			'photo' => $img_link,
		);
		
		$markers[] = array(
			'lat' => $observation->y,
			'long' => $observation->x,
		);
	}
	
	$form['explication'] = array(
		'#markup' => '<p>' . t('Enable or delete the users observations below.') . '</p>'
	);
	
	$form['observations'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No content available.'),
		'#multiple' => TRUE,
		'#attributes' => array(
			'class' => array('taxon_table')
		)
	);	
	
	$form['map'] = array(
		'#markup' => '<div id="map" class="map"></div><div style="clear: both;"></div>',
	);
	
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Enable')
	);
	$form['actions']['delete'] = array(
		'#type' => 'submit',
		'#value' => t('Delete')
	);
	
	
	
	$mapOptions = array();
	$mapOptions['map_lat'] = '45.9';
	$mapOptions['map_long'] = '6.95';
	$mapOptions['map_zoom'] = '10';
	
	$map_infos = array(
		'mapOptions' => $mapOptions,
		'mapMarkers' => $markers,
		'mapIcon' => $base_url . base_path() . drupal_get_path('theme', 'crea') . '/images/marker-icon.png',
		'mapIconShadow' => $base_url . base_path() . drupal_get_path('theme', 'crea') . '/images/marker-icon-shadow.png'
	);
	drupal_add_js(array('CreaCartographieMap' => $map_infos, 'IGNkey' => $conf['domain_ign_key']), 'setting');
	
	drupal_add_js(drupal_get_path('theme', 'crea').'/js/leaflet/leaflet.js');
	drupal_add_js(drupal_get_path('module', 'crea_backoffice').'/js/crea_map.js');
	
	drupal_add_css(drupal_get_path('theme', 'crea') . '/js/leaflet/leaflet.css');
	drupal_add_css(drupal_get_path('module', 'crea_backoffice') . '/css/map.css');
	
	return $form;
}

function crea_backoffice_validate_pffs_submissions_form_submit(&$form, &$form_state){
	$action = "update";
	if (isset($form_state['values']['op'])
	&&isset($form_state['values']['submit'])
	&&isset($form_state['values']['delete'])){
		if ($form_state['values']['op'] == $form_state['values']['submit']){
			$action = "enable";
		}
		elseif ($form_state['values']['op'] == $form_state['values']['delete']){
			$action = "delete";
		}
	}
	
	if (isset($form_state['values']['observations'])
	&& is_array($form_state['values']['observations'])
	&& !empty($form_state['values']['observations'])){
		$enabled_obs = array();
		foreach ($form_state['values']['observations'] AS $key => $value){
			if ($value !== 0){
				$enabled_obs[] = $key;
			}
		}
		
		switch ($action){
			case 'enable':
				$status = crea_publish_protocole_faune_flore_observations($enabled_obs);
			break;
			
			case 'delete':
				$status = crea_delete_protocole_faune_flore_observations($enabled_obs);
			break;
		}
		
		if (!status){
			form_set_error('', t('Error while updating'));
		}
	}
}