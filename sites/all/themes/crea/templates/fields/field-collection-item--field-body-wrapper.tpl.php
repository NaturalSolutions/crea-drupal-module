<?php

/**
 * @file
 * Default theme implementation for field collection items.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) field collection item label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-field-collection-item
 *   - field-collection-item-{field_name}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
$classes = array();
if (isset($content['field_zone_fluid']['#items'][0]['value'])){
  if ($content['field_zone_fluid']['#items'][0]['value'] == 1){
    array_push($classes, 'container-fluid');
  }
  else{
    array_push($classes, 'container');
  }
}
else{
  array_push($classes, 'container');
}

if (isset($content['field_background']['#items'][0]['value'])){
  array_push($classes, $content['field_background']['#items'][0]['value']);
}
?>
<div class="<?php print implode(" ", $classes); ?> clearfix">
  <?php if (in_array('container-fluid', $classes)) : ?> <div class="container"> <?php endif; ?>
  <div class="content"<?php print $content_attributes; ?>>
    <?php
      hide($content['field_zone_fluid']);
      hide($content['field_background']);
      print render($content);
    ?>
  </div>
  <?php if (in_array('container-fluid', $classes)) : ?> </div> <?php endif; ?>
</div>
