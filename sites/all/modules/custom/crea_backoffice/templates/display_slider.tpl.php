<?php

$f_slider = $element['#object']->field_slider['und'][0];
$slider_pics = $f_slider['node']->field_illustration;
if(isset($slider_pics['und']) && count($slider_pics['und']) == 2 ){
    $slider_title = $f_slider['node']->title;
    $pic_before = scald_atom_load($slider_pics['und'][0]['sid']);
    $larg_before = $pic_before->base_entity->metadata['width'];
    $style = image_style_load('slider_before_after');
    if($larg_before > $style['effects'][0]['data']['width']){
        $larg_container = '100%';
    }else{
        $larg_container = $larg_before.'px';
    }
    $long_before = $pic_before->base_entity->metadata['height'];
    $url_before = file_create_url($pic_before->base_entity->uri);
    $url_before = parse_url($url_before);
    $url_before = $url_before['path'];
    $pic_after = scald_atom_load($slider_pics['und'][1]['sid']);
    $larg_after = $pic_after->base_entity->metadata['width'];
    $long_after = $pic_after->base_entity->metadata['height'];
    $url_after = file_create_url($pic_after->base_entity->uri);
    $url_after = parse_url($url_after);
    $url_after = $url_after['path'];
?>
  <div class="container">
    <div id="slidercontainer-<?php print $f_slider['nid']; ?>" class='twentytwenty-container' style="width:<?php echo $larg_container; ?>;">
        <div><img alt="before" src="<?php echo $url_before; ?>" width="<?php echo $larg_before; ?>" height="<?php echo $long_before; ?>"/></div>
        <div><img alt="after" src="<?php echo $url_after; ?>" width="<?php echo $larg_after; ?>" height="<?php echo $long_after; ?>"/></div>
    </div>
  </div>
    <script type="text/javascript">
        (function ($) {
            $('#slidercontainer-<?php print $f_slider['nid']; ?>').twentytwenty();
        })(jQuery);
    </script>
<?php
}else{
    print '<!-- bad params for slider -->';
}
?>