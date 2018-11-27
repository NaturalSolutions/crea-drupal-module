<?php 

$types = node_type_get_types();
foreach ($types AS $type){
	variable_set('comment_anonymous_'.$type->type, 0);
	variable_set('comment_default_mode_'.$type->type, 0);
	variable_set('comment_'.$type->type, '0');
	variable_set('comment_preview_'.$type->type, '0');
	variable_set('language_content_type_'.$type->type, '1');
	variable_set('node_submitted_'.$type->type, 0);
	variable_set('node_preview_'.$type->type, '0');
	variable_set('node_options_'.$type->type, array());
	variable_set('i18n_node_options_'.$type->type, array('current', 'required'));
	variable_set('i18n_node_extended_'.$type->type, '1');
}

db_update('menu_custom')
->fields(array(
	'i18n_mode' => 5
))
->condition('menu_name', 'main-menu', '=')
->execute();


// Profile linkit
$query = db_select('linkit_profiles', 'l')
->fields('l')
->condition('l.name', 'internal_path', '=');

$result = $query->execute()->fetchObject();

if (!is_object($result)){
	db_insert('linkit_profiles')
	->fields(array(
		'name' => 'internal_path',
		'admin_title' => 'internal path',
		'admin_description' => '',
		'profile_type' => '1',
		'data' => serialize(array(
			'text_formats' => array(
				'full_html' => 'full_html',
				'filtered_html' => 'filtered_html',
				'plain_text' => 0
			),
			'search_plugins' => array(
				'entity:scald_atom' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'entity:taxonomy_term' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'entity:comment' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'entity:file' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'entity:node' => array(
					'enabled' => 1,
					'weight' => -10
				),
				'entity:user' => array(
					'enabled' => 0,
					'weight' => -10
				)
			),
			'entity:scald_atom' => array(
				'result_description' => '',
				'bundles' => array(
					'audio' => 0,
					'flash' => 0,
					'image' => 0,
					'video' => 0
				),
				'group_by_bundle' => 0
			),
			'entity:comment' => array(
				'result_description' => '',
				'bundles' => array(
					'comment_node_news' => 0,
					'comment_node_page' => 0,
					'comment_node_press_release' => 0,
					'comment_node_webform' => 0,
					'comment_node_faune' => 0,
					'comment_node_flore' => 0,
					'comment_node_station' => 0
				),
				'group_by_bundle' => 0
			),
			'entity:node' => array(
				'result_description' => '',
				'bundles' => array(
					'news' => 'news',
					'page' => 'page',
					'press_release' => 'press_release',
					'webform' => 'webform',
					'faune' => 'faune',
					'flore' => 'flore',
					'station' => 'station'
				),
				'group_by_bundle' => 0,
				'include_unpublished' => 0
			),
			'entity:file' => array(
				'result_description' => '',
				'bundles' => array(
					'image' => 0,
					'video' => 0,
					'audio' => 0,
					'document' => 0
				),
				'group_by_bundle' => 0,
				'show_scheme' => 0,
				'group_by_bundle' => 0,
				'url_type' => 'entity',
				'image_extra_info' => array(
					'thumbnail' => 'thumbnail',
					'dimensions' => 'dimensions'
				)
			),
			'entity:taxonomy_term' => array(
				'result_description' => '',
				'bundles' => array(
					'scald_authors' => 0,
					'scald_tags' => 0,
					'tags' => 0
				),
				'group_by_bundle' => 0,
			),
			'entity:user' => array(
				'result_description' => '',
			),
			'insert_plugin' => array(
				'url_method' => 2
			),
			'attribute_plugins' => array(
				'accesskey' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'target' => array(
					'enabled' => 1,
					'weight' => -10
				),
				'class' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'rel' => array(
					'enabled' => 0,
					'weight' => -10
				),
				'id' => array(
					'enabled' => 1,
					'weight' => -10
				),
				'title' => array(
					'enabled' => 1,
					'weight' => -10
				)
			),
			'autocomplete' => array(
				'charLimit' => 3,
				'wait' => 350,
				'remoteTimeout' => 10000
			)
		))
	))
	->execute();
}


// Profiles ckeditor
$query = db_select('linkit_profiles', 'l')
->fields('l')
->condition('l.name', 'internal_path', '=');

$result = $query->execute()->fetchObject();

if (is_object($result)){
	db_update('ckeditor_settings')
	->fields(array(
		'settings' => serialize(array(
			'skin' => 'office2013',
			'ckeditor_path' => '%m/ckeditor',
			'ckeditor_local_path' => '',
			'ckeditor_plugins_path' => '%m/plugins',
			'ckeditor_plugins_local_path' => '',
			'ckfinder_path' => '%m/ckfinder',
			'ckfinder_local_path' => '',
			'ckeditor_aggregate' => 'f',
			'toolbar_wizard' => 't',
			'loadPlugins' => array()
		))
	))
	->condition('name', 'CKEditor Global Profile', '=')
	->execute();
}


$query = db_select('ckeditor_settings', 't')
->fields('t')
->condition('t.name', 'Advanced', '=');

$result = $query->execute()->fetchObject();

if (is_object($result)){
	db_update('ckeditor_settings')
	->fields(array(
		'settings' => serialize(array(
			'ss' => '2',
			'toolbar' => "[
	    ['Source','Format','Styles','FontSize','TextColor','Bold','Italic','Underline','-','NumberedList','BulletedList','-','linkit','Link','Unlink','Image','ScaldAtom','MediaEmbed','JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock']
	]",
			'expand' => 't',
			'default' => 't',
			'show_toggle' => 't',
			'uicolor' => 'custom',
			'uicolor_user' => '#D3D3D3',
			'width' => '100%',
			'lang' => 'en',
			'auto_lang' => 't',
			'language_direction' => 'default',
			'allowed_content' => 't',
			'extraAllowedContent' => '',
			'enter_mode' => 'p',
			'shift_enter_mode' => 'br',
			'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
			'custom_formatting' => 'f',
			'formatting' => array(
				'custom_formatting_options' => array(
					'indent' => 'indent',
					'breakBeforeOpen' => 'breakBeforeOpen',
					'breakAfterOpen' => 'breakAfterOpen',
					'breakAfterClose' => 'breakAfterClose',
					'breakBeforeClose' => 0,
					'pre_indent' => 0
				)
			),
			'css_mode' => 'none',
			'css_path' => '',
			'css_style' => 'theme',
			'styles_path' => '',
			'filebrowser' => 'none',
			'filebrowser_image' => '',
			'filebrowser_flash' => '',
			'UserFilesPath' => '%b%f/',
			'UserFilesAbsolutePath' => '%d%b%f/',
			'forcePasteAsPlainText' => 'f',
			'html_entities' => 'f',
			'scayt_autoStartup' => 'f',
			'theme_config_js' => 'f',
			'js_conf' => '',
			'loadPlugins' => array(
				'dnd' => array(
					'name' => 'dnd',
					'desc' => 'Scald Drag and Drop integration',
					'path' => '%base_path%sites/all/modules/contrib/scald/modules/library/dnd/plugins/ckeditor/',
					'buttons' => array(
						'ScaldAtom' => array(
							'label' => 'ScaldAtom',
							'icon' => 'icons/atom.png'
						)		
					)
				),
				'drupalbreaks' => array(
					'name' => 'drupalbreaks',
					'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
					'path' => '%plugin_dir%drupalbreaks/',
					'buttons' => array(
						'DrupalBreak' => array(
							'label' => 'DrupalBreak',
							'icon' => 'images/drupalbreak.png'
						)
					),
					'default' => 't'
				),
				'linkit' => array(
					'name' => 'linkit',
					'desc' => 'Support for Linkit module',
					'path' => '%base_path%sites/all/modules/contrib/linkit/editors/ckeditor/',
					'buttons' => array(
						'linkit' => array(
							'label' => 'Linkit',
							'icon' => 'icons/linkit.png'
						)
					)
				),
				'mediaembed' => array(
					'name' => 'mediaembed',
					'desc' => 'Plugin for inserting Drupal embeded media',
					'path' => '%plugin_dir%mediaembed/',
					'buttons' => array(
						'MediaEmbed' => array(
							'label' => 'MediaEmbed',
							'icon' => 'images/icon.png'
						)
					)
				)
			)
		))
	))
	->condition('name', 'Advanced', '=')
	->execute();
}


$query = db_select('ckeditor_settings', 't')
->fields('t')
->condition('t.name', 'Full', '=');

$result = $query->execute()->fetchObject();

if (is_object($result)){
	db_merge('ckeditor_settings')
	->fields(array(
		'name' => 'Full',
		'settings' => serialize(array(
			'ss' => '2',
			'toolbar' => "[
	    ['Source','Format','Styles','FontSize','TextColor','Bold','Italic','Underline','-','NumberedList','BulletedList','-','linkit','Link','Unlink','Image','ScaldAtom','MediaEmbed','JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock']
	]",
			'expand' => 't',
			'default' => 't',
			'show_toggle' => 't',
			'uicolor' => 'custom',
			'uicolor_user' => '#D3D3D3',
			'width' => '100%',
			'lang' => 'en',
			'auto_lang' => 't',
			'language_direction' => 'default',
			'allowed_content' => 't',
			'extraAllowedContent' => '',
			'enter_mode' => 'p',
			'shift_enter_mode' => 'br',
			'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
			'custom_formatting' => 'f',
			'formatting' => array(
				'custom_formatting_options' => array(
					'indent' => 'indent',
					'breakBeforeOpen' => 'breakBeforeOpen',
					'breakAfterOpen' => 'breakAfterOpen',
					'breakAfterClose' => 'breakAfterClose',
					'breakBeforeClose' => 0,
					'pre_indent' => 0
				)
			),
			'css_mode' => 'none',
			'css_path' => '',
			'css_style' => 'theme',
			'styles_path' => '',
			'filebrowser' => 'none',
			'filebrowser_image' => '',
			'filebrowser_flash' => '',
			'UserFilesPath' => '%b%f/',
			'UserFilesAbsolutePath' => '%d%b%f/',
			'forcePasteAsPlainText' => 'f',
			'html_entities' => 'f',
			'scayt_autoStartup' => 'f',
			'theme_config_js' => 'f',
			'js_conf' => '',
			'loadPlugins' => array(
				'dnd' => array(
					'name' => 'dnd',
					'desc' => 'Scald Drag and Drop integration',
					'path' => '%base_path%sites/all/modules/contrib/scald/modules/library/dnd/plugins/ckeditor/',
					'buttons' => array(
						'ScaldAtom' => array(
							'label' => 'ScaldAtom',
							'icon' => 'icons/atom.png'
						)		
					)
				),
				'drupalbreaks' => array(
					'name' => 'drupalbreaks',
					'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
					'path' => '%plugin_dir%drupalbreaks/',
					'buttons' => array(
						'DrupalBreak' => array(
							'label' => 'DrupalBreak',
							'icon' => 'images/drupalbreak.png'
						)
					),
					'default' => 't'
				),
				'linkit' => array(
					'name' => 'linkit',
					'desc' => 'Support for Linkit module',
					'path' => '%base_path%sites/all/modules/contrib/linkit/editors/ckeditor/',
					'buttons' => array(
						'linkit' => array(
							'label' => 'Linkit',
							'icon' => 'icons/linkit.png'
						)
					)
				),
				'mediaembed' => array(
					'name' => 'mediaembed',
					'desc' => 'Plugin for inserting Drupal embeded media',
					'path' => '%plugin_dir%mediaembed/',
					'buttons' => array(
						'MediaEmbed' => array(
							'label' => 'MediaEmbed',
							'icon' => 'images/icon.png'
						)
					)
				)
			)
		))
	))
	->condition('name', 'Full', '=')
	->execute();
}

