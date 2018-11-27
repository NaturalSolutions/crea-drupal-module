<div class="video-live">
  <img src="<?php print $live_image_src; ?>" alt="" />
</div>
<div class="stats-live">
  <?php if ($temperature_sol): ?>
    <span class="sol">
      <?php echo t('ground', array(), array('context' => 'CREA_LNG')); ?> : <?php print $temperature_sol; ?>°c
    </span>
  <?php endif; ?>
  <?php if ($temperature_air): ?>
    <span class="air">
    <?php echo t('air', array(), array('context' => 'CREA_LNG')); ?> : <?php print $temperature_air; ?>°c
    </span>
  <?php endif; ?>
  <?php if ($niveau_neige): ?>
    <span class="neige">
    <?php echo t('snow', array(), array('context' => 'CREA_LNG')); ?> : <?php print $niveau_neige; ?>
    </span>
  <?php endif; ?>
</div>