<style>
#map_container{
	position: relative;
}
#map{
	width:45%;
	height:100%;
	overflow: hidden;
	float: right;
}

#diagram{
	padding: 0 0 0 10px;
	background-color: white; 
	width: 55%;
	display: block;
	position: relative;
	float: right;
}
#graph-close{
	position: absolute;
	right: 20px;
	top: 0;
	z-index: 1;
}
#switchLive,
#switchAverage{
	font-size: 0.7rem;
}
</style>

<div id="map_container">
	<div id="diagram" class="diagram"></div>
	<div id="map" class="map"></div>
	<div class="clear"></div>
</div>
