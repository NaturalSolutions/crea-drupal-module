<?php
// TITRE PAGE
drupal_set_title(t('Les études scientifiques', array(), array('context' => 'CREA_LNG')));
// BREADCRUMBS
$breadcrumb = array();
$breadcrumb[] = l('Home', '<front>');
$breadcrumb[] = l(t('Les études scientifiques', array(), array('context' => 'CREA_LNG')), '/listing-programs');
?>
<div class="bdd_etudes">

    <h2><? echo $titre; ?></h2>
    <h3><?php echo cleanBDDEtudes($soustitre); ?></h3>
    <p><?php echo cleanBDDEtudes($description); ?></p>
    <?php if($responsable != ''){ ?>
        <p><b><?php echo t('Responsable', array(), array('context' => 'CREA_LNG')); ?></b> : <?php echo $responsable; ?></p>
    <?php } ?>
    <?php if(count($labos) > 0){ ?>
        <p><b><?php echo t('Laboratoires', array(), array('context' => 'CREA_LNG')); ?></b> : </p>
        <ul>
        <?php foreach($labos  as $l){
                $infos = array();
                if($l['sigle'] != ''){
                    array_push($infos, $l['sigle']);
                }
                if($l['lab'] != ''){
                    array_push($infos, $l['lab']);
                }
                if($l['town'] != ''){
                    array_push($infos, $l['town']);
                }
                if($l['country'] != ''){
                    array_push($infos, $l['country']);
                }
                if($l['web'] != ''){
                    $web = '<a href="'.$l['web'].'" target="_blank">'.t('Site Web', array(), array('context' => 'CREA_LNG')).'</a>';
                    array_push($infos, $web);
                }
                $infos = implode(' / ', $infos);
            ?>
            <li>
                <?php echo $infos; ?>
            </li>
    <?php } ?>
        </ul>
    <?php } ?>
    <p><b><?php echo t('Domaines', array(), array('context' => 'CREA_LNG')); ?></b> : <?php echo $domaines; ?></p>
    <p><b><?php echo t('Sous domaines', array(), array('context' => 'CREA_LNG')); ?></b> : <?php echo $sousdomaines; ?></p>

    <?php if($partenaires != ''){ ?>
    <p class="partners">
        <b><?php echo t('Partenaires', array(), array('context' => 'CREA_LNG')); ?></b> : <?php echo $partenaires; ?>
    </p>
    <?php } ?>
    <?php if(count($but) > 0){ ?>
        <p><b><?php echo t('Buts', array(), array('context' => 'CREA_LNG')); ?></b> : </p>
        <ul>
            <?php foreach($but  as $b){
                if($b != ''){
                ?>
                <li>
                    <?php echo cleanBDDEtudes($b); ?>
                </li>
            <?php }} ?>
        </ul>
    <?php } ?>
    <?php if(count($methode) > 0){ ?>
        <p><b><?php echo t('Méthodes', array(), array('context' => 'CREA_LNG')); ?></b> : </p>
        <ul>
            <?php foreach($methode  as $m){
                if($m != ''){
                    ?>
                    <li>
                        <?php echo cleanBDDEtudes($m); ?>
                    </li>
                <?php }} ?>
        </ul>
    <?php } ?>
    <?php if(count($parametre) > 0){ ?>
        <p><b><?php echo t('Paramètres', array(), array('context' => 'CREA_LNG')); ?></b> : </p>
        <ul>
            <?php foreach($parametre  as $p){
                if($p != ''){
                    ?>
                    <li>
                        <?php echo cleanBDDEtudes($p); ?>
                    </li>
                <?php }} ?>
        </ul>
    <?php } ?>
    <?php if($start != ''){ ?>
        <p class="start">
            <b><?php echo t('Débuté le', array(), array('context' => 'CREA_LNG')); ?></b> : <?php echo $start; ?>
        </p>
    <?php } ?>

    <?php if($siteweb != ''){ ?>
        <p siteweb="start">
            <b><?php echo t('Site web', array(), array('context' => 'CREA_LNG')); ?></b> : <a href="<?php echo $siteweb; ?>" target="_blank"><?php echo $siteweb; ?></a>
        </p>
    <?php } ?>

    <?php if(count($location) > 0){ ?>
        <p><b><?php echo t('Localisation', array(), array('context' => 'CREA_LNG')); ?></b> : </p>
        <ul>
            <?php foreach($location  as $l){
                if($l['loc'] != ''){
                    ?>
                    <li>
                        <?php echo cleanBDDEtudes($l['loc']).' ('.$l['commune'].')'; ?>
                    </li>
                <?php }} ?>
        </ul>
    <?php } ?>

    <a href="/listing-programs"><button class="crea-button orange-button-link nosubmit"><?php echo t('Retour à la liste', array(), array('context' => 'CREA_LNG')); ?></button></a>
</div>