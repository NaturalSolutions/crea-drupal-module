<style>
#map_container{
	position: relative;
}
#map{
	width:70%;
	height:800px;
	overflow: hidden;
	float: left;
}
#crea-users-saisir-faune-flore-form{
	width: 29%;
	float: right;
}
</style>

<div id="map_container">
	<div id="map" class="map"></div>
	<?php if (isset($form)) print render($form); ?>
</div>