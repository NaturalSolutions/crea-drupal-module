<script src="https://api.mapbox.com/mapbox.js/v2.2.3/mapbox.js"></script>
<script src="https://api.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/leaflet.markercluster.js"></script>
<link href="https://api.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.css" rel="stylesheet" />
<link href="https://api.mapbox.com/mapbox.js/plugins/leaflet-markercluster/v0.4.0/MarkerCluster.Default.css" rel="stylesheet" />
<style>
#map_container{
	position: relative;
}
#map{
	height:800px;
	overflow: hidden;
	float: left;
}
@media (max-width: 1024px) {
	#map{
		height: 350px;
	}
}

</style>
<div class="container">
	<div id="map_container">
		<div id="map" class="map"></div>
		<div class="col-md-4">
			<?php if (isset($form)) print render($form); ?>
			</div>
	</div>
</div>