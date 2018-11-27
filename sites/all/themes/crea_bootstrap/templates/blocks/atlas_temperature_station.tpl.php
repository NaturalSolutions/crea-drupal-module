<section id="<?php if(isset($block_html_id)) print $block_html_id; ?>" class="<?php if (isset($classes)) print $classes; ?> clearfix"<?php if(isset($attributes)) print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2 class="block-title">
      <span class="icon montagne">&nbsp;</span>
      <span class="title"><?php print $title; ?></span>
    </h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php if (isset($stations_temperature_form)): ?>
    <div class="station_data">
      <?php print render($stations_temperature_form); ?>
    </div>
  <?php endif; ?>
</section>