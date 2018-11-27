<section id="<?php if (isset($block_html_id)) print $block_html_id; ?>" class="<?php if (isset($classes)) print $classes; ?> clearfix"<?php if(isset($attributes)) print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2 class="block-title">
      <span class="icon loupe">&nbsp;</span>
      <span class="title"><?php print $title; ?></span>
    </h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <?php if (isset($nbr_obs)
  && is_array($nbr_obs)
  && !empty($nbr_obs)): ?>
    <div class="nbr_obs">
      <?php foreach ($nbr_obs AS $nbr): ?>
        <span class="nbr"><?php print $nbr; ?></span>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>
</section>