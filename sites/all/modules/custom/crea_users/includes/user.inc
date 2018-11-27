<?php 

function crea_unit_list_callback(){
	$unit_list = array();
	$db_data = Database::getConnection('usershubdb','default');

	$sql = 'SELECT id_unite, nom_unite 
            FROM "utilisateurs".bib_unites;';
	$res = $db_data->query($sql);
	$results = $res->fetchAll();

	if (!empty($results)){
		foreach ($results AS $result){
			$unit_list[$result->id_unite] = $result->nom_unite;
		}
		db_set_active();
		return $unit_list;
	}
	else{
		db_set_active();
		return $unit_list;
	}
}

function crea_users_form_user_register_form_alter(&$form, &$form_state){
	$form['account']['first_name'] = array(
		'#type' => 'textfield',
		'#title' => t('First name'),
		'#maxlength' => 60,
		'#description' => '',
		'#required' => true,
		'#attributes' => array('class' => array('first_name')),
		'#default_value' => '',
		'#access' => true,
	);
	$form['account']['last_name'] = array(
		'#type' => 'textfield',
		'#title' => t('Last name'),
		'#maxlength' => 60,
		'#description' => '',
		'#required' => true,
		'#attributes' => array('class' => array('last_name')),
		'#default_value' => '',
		'#access' => true,
	);

	$form['account']['postal_code'] = array(
		'#type' => 'textfield',
		'#title' => t('Postal code'),
		'#maxlength' => 60,
		'#description' => '',
		'#required' => true,
		'#attributes' => array('class' => array('postal_code')),
		'#default_value' => '',
		'#access' => true,
	);
	$form['account']['city'] = array(
		'#type' => 'textfield',
		'#title' => t('City'),
		'#maxlength' => 60,
		'#description' => '',
		'#required' => true,
		'#attributes' => array('class' => array('city')),
		'#default_value' => '',
		'#access' => true,
	);
	/*$form['account']['organism'] = array(
		'#type' => 'textfield',
		'#title' => t('Organism'),
		'#maxlength' => 60,
		'#description' => '',
		'#required' => false,
		'#attributes' => array('class' => array('organism')),
		'#default_value' => '',
		'#access' => true,
		'#autocomplete_path' => 'users/organism'
	);*/

	/*$form['account']['user_type'] = array(
		'#type' => 'select',
		'#title' => t('User type'),
		'#maxlength' => 60,
		'#description' => '',
		'#required' => false,
		'#attributes' => array('class' => array('user_type')),
		'#default_value' => '',
		'#access' => true,
		'#options' => crea_unit_list_callback()
	);*/

	$form['account']['crea_member'] = array(
		'#type' => 'checkbox',
		'#title' => t('CREA member'),
		'#description' => '',
		'#required' => false,
		'#attributes' => array('class' => array('crea_member')),
		'#default_value' => array(),
		'#access' => true,
	);

	$form['account']['receive_newsletter'] = array(
		'#type' => 'checkbox',
		'#title' => t('subscribe to CREA newsletters'),
		'#description' => '',
		'#required' => false,
		'#attributes' => array('class' => array('receive_newsletter')),
		'#default_value' => array(),
		'#access' => true,
	);


	$form['account']['last_name']['#weight'] = -10;
	$form['account']['first_name']['#weight'] = -9;
	$form['account']['name']['#weight'] = -8;
	$form['account']['pass']['#weight'] = -7;
	$form['account']['mail']['#weight'] = -6;
	$form['account']['postal_code']['#weight'] = -5;
	$form['account']['city']['#weight'] = -4;
	//$form['account']['organism']['#weight'] = -3;
	//$form['account']['user_type']['#weight'] = -2;
	$form['account']['crea_member']['#weight'] = -1;
	$form['account']['receive_newsletter']['#weight'] = 0;

  if (isset($form['captcha'])){
    $form['actions']['submit']['#weight'] = 1;
    $form['captcha']['#weight'] = 0;
  }

	$form['#validate'][] = 'crea_users_form_user_register_form_validate';
}

function crea_users_form_user_profile_form_alter(&$form, &$form_state){
  $form['#validate'][] = 'crea_users_form_user_profile_form_validate';
}

function crea_users_form_user_register_form_validate($form, &$form_state){
	if (isset($form_state['input']['pass']['pass1'])
	&& isset($form_state['input']['pass']['pass2'])
	&& isset($form_state['values']['pass'])
	&& $form_state['input']['pass']['pass1'] === $form_state['input']['pass']['pass2']){
		// TODO
		// voir si on echappe le password sauvegardé par sécurité
		$form_state['values']['password_saved'] = $form_state['values']['pass'];
	}

	$userExists = verifyIfUserExistsInExternalBDD('geonaturedb', $form_state['values']['name'], $form_state['values']['mail']);

	if (is_array($userExists)
	&& !empty($userExists)){
		form_set_error('name', t('Please, enter another username'));
		form_set_error('mail', t('Please, entre another email address'));
	}
}

function crea_users_form_user_profile_form_validate($form, &$form_state){
  if (isset($form_state['input']['pass']['pass1'])
    && isset($form_state['input']['pass']['pass2'])
    && isset($form_state['values']['pass'])
    && $form_state['input']['pass']['pass1'] === $form_state['input']['pass']['pass2']){
    // TODO
    // voir si on echappe le password sauvegardé par sécurité
    $form_state['values']['password_saved'] = $form_state['values']['pass'];
  }
}