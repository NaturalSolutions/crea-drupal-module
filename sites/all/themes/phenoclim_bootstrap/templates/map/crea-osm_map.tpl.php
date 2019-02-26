<style>
#map_container{
	position: relative;
}
#map{
	height:660px;
	overflow: hidden;
	/*float: right;*/
}

#diagram{
	padding: 0 0 0 10px;
	background-color: white;
	display: block;
	position: relative;
	/*float: right;*/
}
@media (max-width: 1024px) {
	#map{
		height: 350px;
	}
}
#graph-close{
	position: absolute;
	right: 20px;
	top: 0;
	z-index: 1;
}
	#temperatures-bloc .content .content{
		display: none;
	}
</style>
<div id="map_container">
	<div id="map" class="map col-md-6"></div>
	<div id="diagram" class="diagram col-md-6"></div>
	<div class="clear"></div>
</div>
