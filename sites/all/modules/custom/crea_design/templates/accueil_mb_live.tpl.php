<?php
// TITRE PAGE
drupal_set_title(t('Accueil MB Live', array(), array('context' => 'CREA_LNG')));
// BREADCRUMBS
$breadcrumb = array();
$breadcrumb[] = l('Home', '<front>');
$breadcrumb[] = l(t('Mont-Blanc Live'), 'node/53');
drupal_set_breadcrumb($breadcrumb);
?>
<div class="row accueil_mb_live">
    <div class="columns medium-12">
        <div class="row">
            <div class="columns medium-6" id="temperatures">
                <h3><?php echo t('Temperatures on the "refuge du Couvercle"', array(), array('context' => 'CREA_LNG')); ?></h3>
                <?php echo $data_temp; ?>
                <div class="access_link right"><a href="<?php echo url('node/14'); ?>"><?php echo t('Go to Climate map', array(), array('context' => 'CREA_LNG')); ?></a></div>
            </div>
            <div class="columns medium-6" id="presentation">
                <h3><?php echo t('Presentation', array(), array('context' => 'CREA_LNG')); ?></h3>
                <?php echo variable_get('accueil_mb_live_txt'); ?>
            </div>
        </div>
        <div class="row">
            <div class="columns medium-6" id="webcam">
                <h3><?php echo t('Mont Blanc images from Montroc (1400m)', array(), array('context' => 'CREA_LNG')); ?></h3>
                <img src="<?php echo variable_get('accueil_mb_live_webcam_url'); ?>" width="100%" alt="CREA Webcam" />
            </div>
            <div class="columns medium-6" id="synthese">
                <h3><?php echo t('Observations', array(), array('context' => 'CREA_LNG')); ?></h3>
                <ul>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_frog.png'); ?>" /></span><?php echo t('Wildlife contact', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[1]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_frog.png'); ?>" /></span><?php echo t('Invertebrates contact', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[2]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_frog.png'); ?>" /></span><?php echo t('Mortality', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[3]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_plant.png'); ?>" /></span><?php echo t('Priority flora', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[4]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_plant.png'); ?>" /></span><?php echo t('Station flora', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[5]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_plant.png'); ?>" /></span><?php echo t('Bryophytes', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[6]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_bird.png'); ?>" /></span><?php echo t('Chocard protocol', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[7]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_frog.png'); ?>" /></span><?php echo t('Frog protocol', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[8]['nbfiches']; ?></li>
                    <li><span><img src="<?php echo file_create_url(drupal_get_path('theme', 'crea').'/images/icon_bird.png'); ?>" /></span><?php echo t('Mesange protocol', array(), array('context' => 'CREA_LNG'))." : ".$data_geonature[9]['nbfiches']; ?></li>
                </ul>
                <div class="access_link right"><a href="/geonature/web" target="_blank"><?php echo t('Go to Geonature', array(), array('context' => 'CREA_LNG')); ?></a></div>
            </div>
        </div>
    </div>
</div>