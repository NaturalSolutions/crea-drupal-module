<?php 

function crea_users_synthese_faune_flore_form($form, &$form_state){
	$form = array();

	$form['date_obs_start'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'd-m-Y',
		'#title' => t('Start date'),
		'#required' => true,
	);
	
	$form['date_obs_end'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'd-m-Y',
		'#title' => t('End date'),
		'#required' => true,
	);
	
	$form['protocole'] = array(
		'#type' => 'select',
		'#options' => array('faune', 'flore'),
		'#title' => t('Protocole'),
		'#required' => true,
	);
	
	$crea_available_taxons = variable_get('crea_available_taxons', array());
	$options_taxon = array();
	
	$taxons = getGeonatureAvailableTaxons();
	if (is_array($taxons)
	&& !empty($taxons)){
		foreach ($taxons AS $taxon){
			if (isset($taxon->cd_nom)
			&& isset($taxon->nom_francais)
			&& in_array($taxon->cd_nom, $crea_available_taxons)){
				$options_taxon[$taxon->cd_nom] = $taxon->nom_francais;
			}
		}
	}
	
	$form['taxon'] = array(
		'#type' => 'select',
		'#options' => $options_taxon,
		'#title' => t('Species'),
		'#required' => true,
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	return $form;
}

function crea_users_synthese_faune_flore_form_validate(&$form, &$form_state){

}

function crea_users_synthese_faune_flore_form_submit(&$form, &$form_state){

}