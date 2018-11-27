<script src="https://api.mapbox.com/mapbox.js/v2.2.3/mapbox.js"></script>
<script src="https://api.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/leaflet.markercluster.js"></script>
<link href="https://api.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.css" rel="stylesheet" />
<link href="https://api.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.Default.css" rel="stylesheet" />
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
#crea-contact-fauneflore-form{
	width: 29%;
	float: right;
}
</style>

<div id="map_container">
	<div id="map" class="map"></div>
	<?php if (isset($form)) print render($form); ?>
</div>