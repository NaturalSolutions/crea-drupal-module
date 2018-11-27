<section id="<?php print $block_html_id; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>>
      <span class="icon live">&nbsp;</span>
      <span class="title"><?php print $title; ?></span>
    </h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php print $content ?>

</section>