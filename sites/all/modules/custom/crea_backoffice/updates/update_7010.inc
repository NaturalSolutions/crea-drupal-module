<?php 

db_update('filter_format')
->fields(array(
	'weight' => -10
))
->condition('format', 'full_html', '=')
->execute();

db_update('filter_format')
->fields(array(
	'weight' => -9,
	'status' => 0
))
->condition('format', 'filtered_html', '=')
->execute();

db_update('filter_format')
->fields(array(
	'weight' => -8
))
->condition('format', 'plain_text', '=')
->execute();


$query = db_select('ckeditor_settings', 't')
->fields('t')
->condition('t.name', 'Full', '=');

$result = $query->execute()->fetchObject();

if (is_object($result)){
	$settings = unserialize($result->settings);
	if (isset($settings['toolbar'])){
		$settings['toolbar'] = "[['Source','Styles','FontSize','TextColor','Bold','Italic','Underline','-','NumberedList','BulletedList','-','linkit','Link','Unlink','Image','ScaldAtom','MediaEmbed','JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock']]";
		
		db_update('ckeditor_settings')
		->fields(array(
			'settings' => serialize($settings)
		))
		->condition('name', 'Full', '=')
		->execute();
	}
}

variable_set('menu_options_page', array('main-menu'));

if (module_enable(array('transliteration'), TRUE)){
	variable_set('pathauto_transliterate', 1);
}