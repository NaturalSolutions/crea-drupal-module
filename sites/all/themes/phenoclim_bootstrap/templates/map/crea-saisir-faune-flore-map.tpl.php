<style>
#map_container{
	position: relative;
}
#map{
	height:800px;
	overflow: hidden;
}
@media (max-width: 1024px) {
	#map{
		height: 350px;
	}
}
</style>

<div class="container">
	<div id="map_container">
		<div id="map" class="map col-md-8"></div>
		<div class="col-md-4">
			<?php if (isset($form)) print render($form); ?>
			</div>
	</div>
</div>