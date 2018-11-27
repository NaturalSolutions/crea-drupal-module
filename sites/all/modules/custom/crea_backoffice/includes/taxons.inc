<?php 

function crea_backoffice_taxons_form($form, &$form_state){
	$form = array();
	
	$options = array();

	$geonature_group_amphibien = variable_get('geonature_group_amphibien',1);
	$geonature_group_mammiferes = variable_get('geonature_group_mammiferes',11);
	$geonature_group_oiseaux = variable_get('geonature_group_oiseaux',12);
	$geonature_group_reptiles = variable_get('geonature_group_reptiles',14);
	$geonature_group_flore = variable_get('geonature_group_flore',1003);

	$protocols = array(
		'fauna' => array(
			$geonature_group_amphibien,
			$geonature_group_mammiferes,
			$geonature_group_oiseaux,
			$geonature_group_reptiles),
		'flora' => array(
			$geonature_group_flore
		)
	);
	
	$groups_name = array(
		$geonature_group_amphibien => "Amphibiens",
		$geonature_group_mammiferes => "Mammifères",
		$geonature_group_oiseaux => "Oiseaux",
		$geonature_group_reptiles => "Reptiles",
		$geonature_group_flore => "Plantes vasculaires",
	);
	
	foreach ($groups_name AS $key => $value){
		$query = db_select('locales_target', 'lt');
		$query->join('locales_source', 'ls', 'ls.lid = lt.lid');
		$query->fields('ls', array('source'))
		->condition('lt.translation', $value, '=')
		->condition('lt.language', 'fr', '=')
		->range(0, 1);
		
		$res = $query->execute()->fetchObject();
		
		if (is_object($res)){
			$groups_name[$key] = t($res->source, array(), array('context' => 'CREA_LNG'));
		}
	}
	
	$taxons = getGeonatureAvailableTaxons($protocols);
	
	$crea_available_taxons = variable_get('crea_available_taxons', array());
	
	foreach ($protocols AS $key_protocol => $groups){
		if (isset($taxons[$key_protocol])){
			$form[$key_protocol] = array(
				'#type' => 'fieldset',
				'#title' => t($key_protocol),
				'#empty' => true
			);
			
			foreach ($groups AS $key_group){
				if (isset($taxons[$key_protocol][$key_group])){					
					if (is_array($taxons[$key_protocol][$key_group])
					&& !empty($taxons[$key_protocol][$key_group])){
						$form[$key_protocol]['#empty'] = false;
						
						$form[$key_protocol][$key_group] = array(
							'#type' => 'fieldset',
							'#title' => $groups_name[$key_group]
						);
						
						$options = array();
						$default_options = array();
						foreach ($taxons[$key_protocol][$key_group] AS $taxon){
							if (isset($taxon->cd_nom)
							&& isset($taxon->nom_francais)){
								$options[$taxon->cd_nom] = $taxon->nom_francais;
								
								if (in_array($taxon->cd_nom, $crea_available_taxons)){
									$default_options[] = $taxon->cd_nom;
								}
							}
						}
						if (!empty($options)){
							if (count($options) > 1 ){
								$form[$key_protocol][$key_group]['group_'.$key_group] = array(
									'#type' => 'checkboxes',
									//'#title' => t('Available taxons'),
									'#description' => t('Check the available taxons for this group of species'),
									'#options' =>  $options,
									'#default_value' => $default_options,
									'#multiple' => true,
								);
							}
							else{
								$form[$key_protocol][$key_group]['taxon_'.key($options)] = array(
									'#type' => 'checkbox',
									'#title' => current($options),
									'#description' => t('Check the available taxons for this group of species'),
									'#default_value' => isset($crea_available_taxons[key($options)]) ? true : false,
								);
							}
						}
					}
				}
			}
		}
		
		if ($form[$key_protocol]['#empty']){
			unset($form[$key_protocol]);
		}
	}
	
	
	
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit')
	);
	
	return $form;
}

function crea_backoffice_taxons_form_submit(&$form, &$form_state){
	if (isset($form_state['values'])){
		$available_taxons = array();
		foreach ($form_state['values'] AS $key => $value){
			if (preg_match('/^group_/', $key)){
				foreach ($value AS $key_taxon => $value_taxon){
					if ($value_taxon !== 0){
						$available_taxons[$key_taxon] = $key_taxon;
					}
				}
			}
			
			if (preg_match('/^taxon_(.*)/', $key, $matches)){
				if ($value === 1
				&& isset($matches[1])){
					$available_taxons[$matches[1]] = $matches[1];
				}
			}
		}
		
		variable_set('crea_available_taxons', $available_taxons);
	}
}