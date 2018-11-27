<?php

function crea_theme()
{
	$items = array();

	$items['user_register_form'] = array(
		'render element'		=> 'form',
		'template'				=> 'user-register-form',
		'path' 					=> drupal_get_path('theme', 'crea') . '/templates',
	);

	return $items;
}

/**
 * Implements template_preprocess_html().
 */
function crea_preprocess_html(&$variables) {
  global $language;

  if($language->language == "en"){
    // on ajoute le css spécifique EN pour le slider
    drupal_add_css(drupal_get_path('theme', 'crea') . '/css/twentytwenty/en.css');
  }
}

/**
 * Implements template_preprocess_page.
 */
function crea_preprocess_page(&$variables) {

}

/**
 * Implements template_preprocess_node.
 */
function crea_preprocess_node(&$variables) {
}

/**
 * Implements template_preprocess_field.
 */
function crea_preprocess_field(&$variables) {
  if($variables['element']['#field_name'] == 'field_slider') {
    $variables['theme_hook_suggestions'][] = 'crea_slider_before_after';
  }
  if($variables['element']['#field_name'] == 'field_module_kmz') {
    $variables['theme_hook_suggestions'][] = 'crea_modulekmz';
  }
  if($variables['element']['#field_name'] == 'field_time_machine') {
    $variables['theme_hook_suggestions'][] = 'crea_timeline';
  }
}

/**
 * Implements theme_form_element_label.
 */
function crea_form_element_label($variables) {
	$element = $variables['element'];
	// This is also used in the installer, pre-database setup.
	$t = get_t();

	// If title and required marker are both empty, output no label.
	if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
		return '';
	}

	// If the element is required, a required marker is appended to the label.
	$required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

	$title = filter_xss_admin($element['#title']);

	$attributes = array();
	// Style the label as class option to display inline with the element.
	if ($element['#title_display'] == 'after') {
		$attributes['class'] = 'option';
	}
	// Show label only to screen readers to avoid disruption in visual flows.
	elseif ($element['#title_display'] == 'invisible') {
		$attributes['class'] = 'element-invisible';
	}

	if (!empty($element['#id'])) {
		$attributes['for'] = $element['#id'];
	}
	
	if (isset($element['#title_class'])) {
		$attributes['class'][] = $element['#title_class'];
	}

	// The leading whitespace helps visually separate fields from inline labels.
	return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required', array('!title' => $title, '!required' => $required)) . "</label>\n";
}

/**
 * Implements theme_field.
 */
function crea_field($variables){
    $content = '';
	if($variables['element']['#field_name'] == 'field_media') {

        $images = [];
        $videos = [];
        $files = [];
        
        // Regroupement des contenus
        foreach ($variables['element']['#items'] as $atom) {
			$atom = scald_atom_load($atom['sid']);
			$render = '';
			
            if($atom->type == 'image'){
                $images[] = $atom;
			}else if($atom->type == 'video'){
                $videos[] = $atom;
            }else if($atom->type == 'file'){
                $files[] = $atom;
            }
        }
        if(!empty($images)){
            // Rendu des images
            $content .= '	<div id="tab-images" class="tab-medias medium element-invisible">';
            $content .= '<h2>'.t('Related pics to the page').' "'.$variables['element']['#object']->title.'"</h2>';
            $content .= '       <ul class="example-orbit" data-orbit>';
            foreach ($images as $image) {
            	$image_title = isset($image->scald_thumbnail['und'][0]['title']) ? $image->scald_thumbnail['und'][0]['title'] : '';
            	$image_alt = isset($image->scald_thumbnail['und'][0]['alt']) ? $image->scald_thumbnail['und'][0]['alt'] : '';
            	
            	if ($image_title === $image_alt ) $image_alt = '';
                $image = theme('image', array(
                    'alt' => $image->title,
                    'path' => $image->file_source
                ));
                $content .= '<li class="active">
                		' . $image . '
                		<h3>' . $image_title . '</h3>
                		<p>' . $image_alt . '</p>
                </li>';
            }
            $content .= '           </ul>';
            //$content .= '		<a class="close-reveal-modal" aria-label="Close">&#215;</a>';
            $content .= '	</div>';
        }
        if(!empty($videos)){
            // Rendu des vidéos
            $content .= '	<div id="tab-videos" class="tab-medias medium element-invisible">';        

            $content .= '<h2>'.t('Related videos to the page').' "'.$variables['element']['#object']->title.'"</h2>';
            foreach ($videos as $video) {
                $content .= '<div class="video">';
                $content .=  $video->rendered->player;
                $content .= '</div>';
            }
            //$content .= '		<a class="close-reveal-modal" aria-label="Close">&#215;</a>';
            $content .= '	</div>';
        }
        if(!empty($files)){
            // Rendu des fichiers
            $content .= '	<div id="tab-files" class="tab-medias medium element-invisible">';

            $content .= '<h2>'.t('Related files to the page').' "'.$variables['element']['#object']->title.'"</h2>';
            foreach ($files as $file) {
                $content .= '<div class="file">';
                $content .= '<a href="'.$file->rendered->file_source_url.'" target="_blank" title="'.$file->rendered->title.'">';
                if(!empty($file->rendered->thumbnail_source_url)){
                    $content .= '<img src="'.$file->rendered->thumbnail_source_url.'" class="scald-file-icon" alt="file type icon" />';
                }
                $content .= $file->rendered->title.'</a>';
                $content .= '</div>';
            }
            //$content .= '		<a class="close-reveal-modal" aria-label="Close">&#215;</a>';
            $content .= '	</div>';
        }

	}

    if($variables['element']['#field_name'] == 'field_links') {
        // Rendu des liens
        $content .= '	<div id="tab-links" class="tab-medias medium element-invisible">';

        $content .= '<h2>'.t('Related links to the page').' "'.$variables['element']['#object']->title.'"</h2>';
        foreach($variables['element']['#items'] as $link){
            if(preg_match('/'.$_SERVER['HTTP_HOST'].'/',$link['display_url'])){
                $target = '';
            }else{
                $target = 'target="_blank"';
            }
            $content .= '<ul class="link">';
            $content .= '<li><a href="'.$link['display_url'].'" '.$target.' title="'.$link['title'].'">'.$link['title'].'</a></li>';
            $content .= '</ul>';
        }
        //$content .= '		<a class="close-reveal-modal" aria-label="Close">&#215;</a>';
        $content .= '	</div>';
    }

    return $content;
}

function crea_links__locale_block(&$vars) {
  foreach($vars['links'] as $language => $langInfo) {
    $vars['links'][$language]['title'] = substr($langInfo['language']->name,0,2);
  }
  $content = theme_links($vars);
  return $content;
}
function crea_links__topbar_main_menu($variables) {
  $links = menu_tree_output(menu_tree_all_data(variable_get('menu_main_links_source', 'main-menu')));
  $output = _zurb_foundation_links($links);
  $variables['attributes']['class'][] = 'right';

  return '<ul' . drupal_attributes($variables['attributes']) . '>' . $output . '</ul>';
}