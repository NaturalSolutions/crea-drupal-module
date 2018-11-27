<style>
#map_container{
	position: relative;
}
#map{
	width:60%;
	height:100%;
	overflow: hidden;
	float: right;
}

#diagram{
	padding: 10px 10px 0;
	background-color: white; 
	width: 40%;
	display: block;
	position: relative;
	float: right;
}
</style>
<div id="page-title"></div>
<div id="map_container">
	<div id="diagram" class="diagram">
        <h1><?php echo t('Fauna and flora observations', array(), array('context' => 'CREA_LNG')); ?></h1>
        <p><?php echo variable_get('help_text_ff'); ?></p>
        <?php
        // affichage du formulaire
        print render($faunaflora_form);
        ?>
        <div>
            <?php echo t('Total observations', array(), array('context' => 'CREA_LNG')).' : '.$observations['nbrequest']; ?></span>
            <br/>&nbsp;
        </div>
        <div>
            <?php 
            global $user;
            if($user->uid!=0){
            	echo l('<button type="button" class="form-submit">'.t('I contribute', array(), array('context' => 'CREA_LNG')).'</button>', 'fauna_flora_protocol_interface', array('html' => TRUE, 'attributes' => array('target'=>'_top'))); 
			}
			else{
				echo l('<button type="button" class="form-submit">'.t('I contribute', array(), array('context' => 'CREA_LNG')).'</button>', 'user', array('html' => TRUE, 'attributes' => array('target'=>'_top'), 'query' => array('destination' => 'fauna_flora_protocol_interface')));
			}
			?>
            </a>
        </div>
    </div>
	<div id="map" class="map"></div>
	<div class="clear"></div>
</div>
