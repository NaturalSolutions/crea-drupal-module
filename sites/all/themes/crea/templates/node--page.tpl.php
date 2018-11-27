<div class="row">
    <article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <?php if (!$page): ?>
          <h2<?php print $title_attributes; ?>>
            <a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
        <?php endif; ?>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
        <div class="posted">
          <?php if ($user_picture): ?>
            <?php print $user_picture; ?>
          <?php endif; ?>
          <?php print $submitted; ?>
        </div>
      <?php endif; ?>
      
      <?php
      // on cache le slider si il existe
      if (isset($content['field_slider'])) {
          hide($content['field_slider']);
      }
      // on cache la timeline si elle existe
      if (isset($content['field_time_machine'])) {
          hide($content['field_time_machine']);
      }
      // on cache le module kmz si il existe
      if (isset($content['field_module_kmz'])) {
          hide($content['field_module_kmz']);
      }
      ?>
        
      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_tags']);
      hide($content['field_media']);
      hide($content['field_links']);

      // on cache le langage
      hide($content['language']);
      // affichage du résumé
      if(isset($content['body']['#object']->body['und'][0]['summary']) && $content['body']['#object']->body['und'][0]['summary'] != ""){
        print "<b><i>".$content['body']['#object']->body['und'][0]['summary']."</i></b>";
      }
      ?>
      
      <?php
       // on affiche le slider before after
       if (!empty($content['field_slider'])) {
           $output = theme('crea_slider_before_after', array('content_slider' => $content['field_slider']));
           print $output;
       }
       ?>
      

      <?php
      print render($content);
      ?>
      
        <?php
        // on affiche le timeline
        if (!empty($content['field_time_machine'])) {
            $output = theme('crea_timeline', array('content_timeline' => $content['field_time_machine']));
            print $output;
        }
        ?>

        <?php
        // on affiche le module kmz
        if (!empty($content['field_module_kmz'])) {
            $output = theme('crea_modulekmz', array('content_modulekmz' => $content['field_module_kmz']));
            print $output;
        }
        ?>

      <?php if (!empty($content['field_tags']) && !$is_front): ?>
        <?php print render($content['field_tags']) ?>
      <?php endif; ?>

      <?php print render($content['links']); ?>
      <?php print render($content['comments']); ?>
    </article>
  </div>
  <div class="medium-1 side-page">
  <?php if (isset($media_images)
  && $media_images === true): ?>
    <div class="row">
      <a href="#tab-images" class="icon" title="<?php print t('Pics'); ?>"><i class="fi-photo"></i></a>
    </div>
  <?php endif; ?>
  
  <?php if (isset($media_videos)
  && $media_videos === true): ?>
    <div class="row">
      <a href="#tab-videos" class="icon" data-reveal-id="reveal-atom-videos" title="<?php print t('Videos'); ?>"><i class="fi-video"></i></a>
    </div>
  <?php endif; ?>
  
  <?php if (isset($media_files)
  && $media_files === true): ?>
    <div class="row">
      <a href="#tab-files" class="icon" data-reveal-id="reveal-atom-files" title="<?php print t('Files'); ?>"><i class="fi-page"></i></a>
    </div>
  <?php endif; ?>
  
  <?php if (isset($media_links)
  && $media_links === true): ?>
    <div class="row">
      <a href="#tab-links" class="icon" data-reveal-id="reveal-atom-links" title="<?php print t('Links'); ?>"><i class="fi-link"></i></a>
    </div>
  <?php endif; ?>
  </div>
      
</div>
<?php if (!empty($content['field_media'])): ?>
	<?php print render($content['field_media']); ?>
<?php endif; ?>

<?php if (!empty($content['field_links'])): ?>
    <?php print render($content['field_links']); ?>
<?php endif; ?>