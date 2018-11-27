<?php
// TITRE PAGE
drupal_set_title(t('Les études scientifiques', array(), array('context' => 'CREA_LNG')));
// BREADCRUMBS
$breadcrumb = array();
$breadcrumb[] = l('Home', '<front>');
?>
<div class="bdd_etudes">
    <div class="formulaire">
        <?php print render($formulaire); ?>
    </div>
    <?php if(count($data_programmes) > 0){ ?>
    <div class="header col col-lg-12">
        <div class="col col-lg-2"><?php echo t('PROGRAMME', array(), array('context' => 'CREA_LNG')); ?></div>
        <div class="col col-lg-4"><?php echo t('DESCRIPTION', array(), array('context' => 'CREA_LNG')); ?></div>
        <div class="col col-lg-2"><?php echo t('DISCIPLINE', array(), array('context' => 'CREA_LNG')); ?></div>
        <div class="col col-lg-2"><?php echo t('SOUS DISCIPLINE', array(), array('context' => 'CREA_LNG')); ?></div>
        <div class="col col-lg-2""><?php echo t('ACCES FICHES', array(), array('context' => 'CREA_LNG')); ?></div>
    </div>
        <?php
        $i = 0;
        foreach($data_programmes as $p){
            if($p->name_study != '' && ($p->etude_fr != '' || $p->etude_uk != '')){
                if($i % 2 == 0){
                    $line = 'dark';
                }else{
                    $line = 'light';
                }
                // traitement des domaines
                $domaines = explode(';', $p->dis);
                $tabDomaines = array();
                foreach($domaines as $d){
                    if($d != ''){
                       array_push($tabDomaines, $d);
                    }
                }
                $sousDomaines = explode(';', $p->ssdis);
                $tabSousDomaines = array();
                foreach($sousDomaines as $d){
                    if($d != ''){
                        array_push($tabSousDomaines, $d);
                    }
                }
            ?>
        <div class="programme col col-lg-12 <?php echo $line; ?>">
            <div class="col col-lg-2"><?php echo $p->name_study; ?></div>
            <div class="col col-lg-4"><?php echo $p->etude_fr; ?></div>
            <div class="col col-lg-2"><?php echo implode(', ', $tabDomaines); ?></div>
            <div class="col col-lg-2"><?php echo implode(', ', $tabSousDomaines); ?></div>
            <div class="col col-lg-2"><a href="/listing-programs/detail/<?php echo $p->idprog; ?>/fr">FR</a> / <a href="/listing-programs/detail/<?php echo $p->idprog; ?>/uk">EN</a></div>
        </div>
                <?php
            $i++;
            } ?>
        <?php } ?>
    <?php }else{ ?>
        <div class="col col-lg-12"><?php echo t('Pas de programmes correspondants à votre recherche', array(), array('context' => 'CREA_LNG')); ?></div>
    <?php }?>
</div>