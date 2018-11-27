<?php 
// ajout de la fonctionnalité de templates au WYSIWYG
$query = db_select('ckeditor_settings', 't')
->fields('t')
->condition('t.name', 'Full', '=');

$result = $query->execute()->fetchObject();

if (is_object($result)){
	$settings = unserialize($result->settings);
	if (isset($settings['toolbar'])){
		$settings['toolbar'] = "[['Source','Styles','FontSize','TextColor','Bold','Italic','Underline','-','NumberedList','BulletedList','-','linkit','Link','Unlink','Image','ScaldAtom','MediaEmbed','JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock','Templates']]";

		db_update('ckeditor_settings')
		->fields(array(
		'settings' => serialize($settings)
		))
		->condition('name', 'Full', '=')
		->execute();
	}
}