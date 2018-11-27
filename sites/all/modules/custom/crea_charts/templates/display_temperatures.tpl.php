<div id="temperatures-bloc">
  <h2 class="block-title temp">
    <span class="icon montagne">&nbsp;</span>
    <span class="title"> &nbsp;<?php echo t('Les températures par station', array(), array('context' => 'CREA_LNG')); ?></span>
  </h2>
  <div class="content">
    <div id="switchCharts">
      <?php
      if(!$standalone){ ?>
        <button id="switchLive" class="active crea-button no-icon orange-button-link"><?php print $switchType; ?></button>
        <button id="switchAverage" class="crea-button no-icon orange-button-link"><?php print $switchType; ?></button>
        <input type="hidden" id="notstandalone" value="1" />
      <?php } ?>
      <input type="hidden" id="typeGraph" value="<?php print $type; ?>" />
    </div>
    <div id="creaChartsForm">
      <?php
      // affichage du formulaire
      print render($charts_form);
      ?>
    </div>
    <div id="containerCharts"></div>
    <div class="content">&nbsp;</div>
  </div>
</div>