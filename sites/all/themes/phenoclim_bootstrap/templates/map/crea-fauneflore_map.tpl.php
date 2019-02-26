<style>
#map_container{
	position: relative;
}
#map{
	height:725px;
	overflow: hidden;
}
@media (max-width: 1024px) {
  #map{
    height: 350px;
  }
}

#diagram{
	/*padding: 0 0 0 30px;*/
	background-color: white;
	display: block;
	position: relative;
}
</style>
<div id="page-title"></div>
<div id="map_container" class="col-md-12">
  <div id="map" class="map col-md-9"></div>
  <div id="diagram" class="diagram col-md-3">
    <div id="faunefloreblock">
      <h2 class="block-title contactfaune">
        <span class="icon loupe">&nbsp;</span>
        <span class="title"> &nbsp;<?php echo t('Fauna and flora observations', array(), array('context' => 'CREA_LNG')); ?></span>
      </h2>
      <div class="content">
        <p><?php echo variable_get('help_text_ff'); ?></p>
        <?php
          // affichage du formulaire
          print render($faunaflora_form);
        ?>
        <div class="panel-pane pane-block pane-crea-design-atlas-compteur-obs atlas_compteur_obs pane-crea-design">
          <div class="pane-content">
            <section id="" class=" clearfix">
              <h2 class="block-title">
                <span class="title"><?php echo t('Total observations', array(), array('context' => 'CREA_LNG')); ?></span>
              </h2>
              <?php

              $nbr_obs = $observations['nbrequest'];

              if ($nbr_obs > 10000000) $nbr_obs = 9999999;
              $nbr_obs = str_split((string)$nbr_obs);
              $max_item = 7;
              if (count($nbr_obs) < $max_item){
                for ($i = count($nbr_obs); $i < $max_item ; $i++){
                  array_unshift($nbr_obs, '0');
                }
              }
              if (isset($nbr_obs)
                && is_array($nbr_obs)
                && !empty($nbr_obs)){
              ?>
                <div class="nbr_obs">
                  <?php foreach ($nbr_obs AS $nbr){ ?>
                    <span class="nbr"><?php print $nbr; ?></span>
                  <?php } ?>
                </div>
              <?php } ?>

            </section>
          </div>
        </div>
      </div>
    </div>
    <div>
      <?php
      global $user;
      if($user->uid!=0){
        echo l('<button type="button" class="crea-button no-icon orange-button-link">'.t('I contribute', array(), array('context' => 'CREA_LNG')).'</button>', 'fauna_flora_protocol_interface', array('html' => TRUE, 'attributes' => array('target'=>'_top')));
      }
      else{
        echo l('<button type="button" class="crea-button no-icon orange-button-link">'.t('I contribute', array(), array('context' => 'CREA_LNG')).'</button>', 'user', array('html' => TRUE, 'attributes' => array('target'=>'_top'), 'query' => array('destination' => 'fauna_flora_protocol_interface')));
      }
      ?>
    </div>
  </div>
  <div class="clear"></div>
</div>

<script language="JavaScript">
  jQuery('#containerCharts').ready(function() {
   hauteur = jQuery('#map_container').height();
   window.parent.resizeModuleLive(hauteur);
   });
</script>