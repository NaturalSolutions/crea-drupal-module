<?php

// BREADCRUMBS
$breadcrumb = array();
$breadcrumb[] = l('Home', '<front>');
$breadcrumb[] = l(t('Atlas interactif'), 'atlas/account');

drupal_set_breadcrumb($breadcrumb);
// image
if(intval($user->picture) != 0){
    $img = file_load($user->picture);
    $imgsrc = file_create_url($img->uri);
}else{
    $imgsrc = '/sites/all/themes/atlas_bootstrap/images/nopicprofile.png';
}
?>
<script language="Javascript">
    function downloadObs(){
        var observations = Drupal.settings.CreaFauneFloreMap.observations;
        jQuery('#downloadObs #download_date_ff').val(observations.date_ff);
        jQuery('#downloadObs #download_date_from').val(observations.from);
        jQuery('#downloadObs #download_date_to').val(observations.to);
        jQuery('#downloadObs').submit();
    }
</script>
<div class="container">
<div class="col espaceperso">
    <div class="col col-md-3 colgauche">
        <div id="hellouser" class="col-md-12">
            <div id="profilpic" class="col-md-4">
                <img src="<?php echo $imgsrc; ?>" />
            </div>
            <div class="col-md-8">
                <div class="hello"><?php echo t('Bonjour'); ?></div>
                <div class="username"><?php echo $user->name; ?></div>
                <div class="actions"><?php echo l(t('Modifier mes informations'), '/user/'.$user->uid.'/edit'); ?></div>
                <div class="actions"><?php echo l(t('Déconnexion'), '/user/logout'); ?></div>
            </div>
        </div>
        <div id="flashinfo" class="col-md-12">
            <h3 class="title"><?php echo crea_backoffice_block_get_title('atlas_flash_info'); ?></h3>
            <div class="content">
                <?php
                $block = module_invoke('crea_design', 'block_view', 'atlas_flash_info');
                print render($block['content']);
                ?>
            </div>
        </div>
        <div id="othersprotocols" class="col-md-12">
            <h3 class="title"><?php echo crea_backoffice_block_get_title('atlas_others_protocols'); ?></h3>
            <?php
            $block = module_invoke('crea_design', 'block_view', 'atlas_others_protocols');
            print render($block['content']);
            ?>
        </div>
    </div>
    <div class="col col-md-9 coldroite">
        <div id="newobs">
           <h2><?php echo t('Saisir une observation'); ?></h2>
            <div id="chooseobs">
                <img src="/<?php echo drupal_get_path('theme', 'atlas_bootstrap'); ?>/images/obs_ff.png" />
                <?php echo l(t('Espèces en live'), 'fauna_flora_protocol_interface'); ?>
            </div>
        </div>
        <div id="mesobs">
            <h2><?php echo t('Mes observations'); ?></h2>
            <div id="map_container">
                <div id="map" class="map"></div>
                <div class="actions">
                    <div class="nbObs col-md-3"><?php echo $nbObs.' '.t('observations'); ?></div>
                    <div class="filter col-md-9"><?php if (isset($form)) print render($form); ?></div>
                </div>
            </div>
            <?php if(isset($observations['entries'])) { ?>
            <div id="tabResults" class="col-md-12">
                <div class="header col-md-12">
                    <div class="col col-md-2">
                        <?php echo t('DATE'); ?>
                    </div>
                    <div class="col col-md-4">
                        <?php echo t('PROTOCOLES'); ?>
                    </div>
                    <div class="col col-md-2">
                        <?php echo t('ESPECES'); ?>
                    </div>
                    <div class="col col-md-2">
                        <?php echo t('OBSERVATION'); ?>
                    </div>
                    <div class="col col-md-2">
                        <?php echo t('ACTIONS'); ?>
                    </div>
                </div>
                <div class="lines">
                    <?php
                    $i = 0;
                        foreach ($observations['entries'] as $obs) {
                            $dateobs = strftime('%d-%m-%Y', strtotime($obs['dateobs']));
                            $protocole = $obs['prot'];
                            ?>
                            <div class="obs col-md-12 <?php if ($i % 2 == 0) {
                                echo 'dark';
                            }
                            else {
                                echo 'light';
                            } ?>" id="lineObs<?php echo $i; ?>">
                                <div class="col col-md-2">
                                    <?php echo str_replace('-', '/', $dateobs); ?>
                                </div>
                                <div class="col col-md-4">
                                    <?php
                                    echo $obs['picto'] . $obs['groupelibelle'];
                                    ?>
                                </div>
                                <div class="col col-md-2">
                                    <?php echo $obs['nom']; ?>
                                </div>
                                <div class="col col-md-2">
                                    <?php
                                    echo gimmeObservationFiche($obs['id']);
                                    ?>
                                </div>
                                <div class="col col-md-2">
                                    <?php
                                    $prot_ffs = variable_get('geonature_protocole_ffs', 103);
                                    if($obs['prot'] == $prot_ffs){
                                        echo l(t('Modifier'), '/fauna_flora_protocol_interface/edit/'.$obs['id']);
                                    }
                                    ?>
                                </div>
                            </div>
                            <?php
                            $i++;
                        }
                    ?>
                </div>
            </div>
            <?php }else{ ?>
            Pas de résultats pour votre requête
            <?php } ?>
            <?php if($nbObs > 0){ ?>
            <form name="downloadObs" id="downloadObs" method="POST" action="/<?php echo $lang; ?>/atlas/account/download">
                <div id="download">
                    <input type="hidden" name="download_date_ff" id="download_date_ff" />
                    <input type="hidden" name="download_date_from" id="download_date_from" />
                    <input type="hidden" name="download_date_to" id="download_date_to" />
                    <a href="javascript:downloadObs();" class="crea-button no-icon orange-button-link">Télécharger</a>
                </div>
            </form>
            <?php } ?>
        </div>
    </div>
</div>
</div>