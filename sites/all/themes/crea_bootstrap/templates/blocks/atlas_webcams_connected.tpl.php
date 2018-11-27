<section id="<?php if(isset($block_html_id)) print $block_html_id; ?>" class="<?php if (isset($classes)) print $classes; ?> clearfix"<?php if(isset($attributes)) print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2 class="block-title">
      <span class="icon video">&nbsp;</span>
      <span class="title"><?php print $title; ?></span>
    </h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php if (isset($webcams_connected_form)): ?>
    <div class="webcams_data">
      <?php print render($webcams_connected_form); ?>
    </div>
  <?php endif; ?>
</section>
