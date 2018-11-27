<?php
//print_r($content_timeline);
$f_timeline = $element['#object']->field_time_machine['und'][0];
$timeline_pics = $f_timeline['node']->field_illustration;
if(isset($timeline_pics['und'])){
    $pics = array();
    foreach($timeline_pics['und'] as $scald_item){
        $pic = scald_atom_load($scald_item["sid"]);
        $style = image_style_load('timeline_pic');
        if($pic->base_entity->metadata['width'] > $style['effects'][0]['data']['width']){
            $larg_container = $style['effects'][0]['data']['width'].'px';
        }else{
            $larg_container = $pic->base_entity->metadata['width'].'px';
        }
        $pics[$scald_item["sid"]]['larg'] = $larg_container;
        $pics[$scald_item["sid"]]['long'] = $pic->base_entity->metadata['height'];
        $url = file_create_url($pic->base_entity->uri);
        $url = parse_url($url);
        $pics[$scald_item["sid"]]['url'] = $url['path'];
        $pics[$scald_item["sid"]]['date'] = $pic->scald_thumbnail['und'][0]['alt'];
        $pics[$scald_item["sid"]]['text'] = $pic->scald_thumbnail['und'][0]['title'];
    }
?>
  <div class="container">
    <div class="timeline" id="timeline-<?php print $f_timeline['nid']; ?>">
        <ul class="dates" id="dates-<?php print $f_timeline['nid']; ?>">
            <?php foreach($pics as $pic){ ?>
                <li><a href="#"><?php echo $pic['date']; ?></a></li>
            <?php } ?>
        </ul>
        <ul class="issues" id="issues-<?php print $f_timeline['nid']; ?>">
            <?php
            $i = 1;
            foreach($pics as $pic){ ?>
            <li id="date<?php echo $i; ?>" >
                <img src="<?php echo $pic['url']; ?>" width="<?php echo $pic['larg']; ?>" height="<?php echo $pic['long']; ?>"/>
                <div class="text">
                    <h1><?php echo $pic['date']; ?></h1>
                    <p><?php echo $pic['text']; ?></p>
                </div>
            </li>
            <?php
                $i++;
            }
            ?>
        </ul>
        <a href="#" class="next" id="next-<?php print $f_timeline['nid']; ?>">+</a> <!-- optional -->
        <a href="#" class="prev" id="prev-<?php print $f_timeline['nid']; ?>">-</a> <!-- optional -->
    </div>
  </div>
    <script type="text/javascript">
        (function ($) {
            $('#timeline-<?php print $f_timeline['nid']; ?>').timelinr({
              containerDiv: '#timeline-<?php print $f_timeline['nid']; ?>',
              datesDiv: '#dates-<?php print $f_timeline['nid']; ?>',
              issuesDiv: '#issues-<?php print $f_timeline['nid']; ?>',
              prevButton: '#prev-<?php print $f_timeline['nid']; ?>',
              nextButton: '#next-<?php print $f_timeline['nid']; ?>',
            });
        })(jQuery);
    </script>
<?php
}else{
    print '<!-- bad params for timeline -->';
}
?>