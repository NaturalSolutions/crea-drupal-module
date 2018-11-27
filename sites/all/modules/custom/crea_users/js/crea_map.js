(function($, w, d){
    $(d).ready(function() {
    	var mapOptions = Drupal.settings.CreaCartographieMap.mapOptions;
      var IGNkey = Drupal.settings.CreaCartographieMap.IGNkey;
            
    	var map;

        var ajaxRequest;
        var plotlist;
        var plotlayers=[];

        map = new L.Map('map');

        // create the tile layer with correct attribution
        var mapOsm = new L.TileLayer('https://{s}.tile.thunderforest.com/landscape/{z}/{x}/{y}.png?apikey=851c476fad9743cca9b16af9c72ecc05', {
          attribution: 'Map data © <a href="http://openstreetmap.org">OpenStreetMap</a> contributors',
          minZoom: 4,
          maxZoom: 18
        });
        var mapOsmSat = new L.TileLayer('https://api.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={accessToken}', {
          attribution: "<a href='http://www.mapbox.com/about/maps/' target='_blank'>&copy; Mapbox &copy; OpenStreetMap</a> <a class='mapbox-improve-map' href='https://www.mapbox.com/map-feedback/' target='_blank'>Improve this map</a>",
          minZoom: 4,
          maxZoom: 18,
          id: 'mapbox.streets-satellite',
          accessToken: 'pk.eyJ1IjoiY2xlbWFkIiwiYSI6ImNpZnkzM2E5ZTAyOHh0bW03cThmYnlraGMifQ.sxu4Iy41LjEsfo34M5emiQ'
        });

        var mapIgnSat = new L.TileLayer('http://gpp3-wxs.ign.fr/{accessToken}/geoportail/wmts?LAYER=ORTHOIMAGERY.ORTHOPHOTOS&EXCEPTIONS=text/xml&FORMAT=image/jpeg&SERVICE=WMTS&VERSION=1.0.0&REQUEST=GetTile&STYLE=normal&TILEMATRIXSET=PM&TILEMATRIX={z}&TILEROW={y}&TILECOL={x}', {
          attribution: "<a href='http://www.mapbox.com/about/maps/' target='_blank'>&copy; Mapbox &copy; OpenStreetMap</a> <a class='mapbox-improve-map' href='https://www.mapbox.com/map-feedback/' target='_blank'>Improve this map</a>",
          minZoom: 4,
          maxZoom: 18,
          //id: 'mapbox.streets-satellite',
          accessToken: IGNkey
        });
        
        map.setView(new L.LatLng(mapOptions['map_lat'], mapOptions['map_long']), mapOptions['map_zoom']);
        map.addLayer(mapOsm);

        L.control.layers({
          "OSM satellite": mapOsmSat,
          "OpenStreetMap carte": mapOsm,
          "IGN satellite": mapIgnSat
        }).addTo(map);

        var greenIcon = L.icon({
            iconUrl: '/sites/all/themes/crea/images/marker-icon.png',
            iconSize:     [29, 29], // size of the icon
            iconAnchor:   [14, 14], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -10] // point from which the popup should open relative to the iconAnchor
        });
        
        if ($('#edit-latitude').val() !== ''
        && $('#edit-longitude').val() !== ''){
        	addMarker({latlng: new L.LatLng(parseFloat($('#edit-latitude').val()), parseFloat($('#edit-longitude').val()))});
        }
        
        map.on('click', addMarker);
        
        $('#edit-latitude').on('keyup keypress', function(e){
        	var code = e.keyCode || e.which;
        	if (code == 13) { 
        		checkLatitudeLongitude();
        	}
        });
        
        $('#edit-longitude').on('keyup keypress', function(e){
        	var code = e.keyCode || e.which;
        	if (code == 13) { 
        		checkLatitudeLongitude();
        	}
        });
        
        $('#crea-users-saisir-faune-flore-form').on('keyup keypress', function(e) {
        	var code = e.keyCode || e.which;
        	if (code == 13) { 
        		e.preventDefault();
        		return false;
        	}
    	});
        
        function checkLatitudeLongitude(){
        	$('#edit-latitude').val(parseFloat($('#edit-latitude').val()));
    		$('#edit-longitude').val(parseFloat($('#edit-longitude').val()));
    		
    		if (isNaN($('#edit-latitude').val())) $('#edit-latitude').val(0);
    		if (isNaN($('#edit-longitude').val())) $('#edit-longitude').val(0);
    		
    		if (!isNaN($('#edit-latitude').val())
    		&& !isNaN($('#edit-longitude').val())){
    			removeAllMarkers(map);
	        	
	        	var newLatLng = new L.LatLng(parseFloat($('#edit-latitude').val()), parseFloat($('#edit-longitude').val()));
	        	var e = {latlng: newLatLng};
	        	addMarker(e);
    		}
        }
        
        function addMarker(e){
        	removeAllMarkers(map);
        	
            var newMarker = new L.marker(e.latlng, {icon: greenIcon, draggable:'true'}).addTo(map);
            
            $('#edit-latitude').val(e.latlng.lat);
            $('#edit-longitude').val(e.latlng.lng);
            
            var altitude = getAltitude(e.latlng.lat, e.latlng.lng);
            $('#edit-altitude').val(altitude);
            
            map.setZoom(map.getZoom());
            map.setView(newMarker.getLatLng());

            // ajout drag and drop
            newMarker.on('dragend', function(event){
                var marker = event.target;
                var position = marker.getLatLng();
                $('#edit-latitude').val(position.lat);
                $('#edit-longitude').val(position.lng);
            });
        }

        function dndMarker(){
            console.log('Drag and drop');
        }
        
        function removeAllMarkers(map){
        	$.each(map._layers, function (ml) {
        		if (map._layers[ml]._icon) {
        			map.removeLayer(this);
        		}
        	});
        }
        
        function getAltitude(lat, lng){
        	var altitude = 0;
        	var elevator = new google.maps.ElevationService;
        	var lctn = new google.maps.LatLng(lat, lng);
        	var positionalRequest = {locations:[lctn]};
        	
        	elevator.getElevationForLocations(positionalRequest, function(results, status) {
                if (status == google.maps.ElevationStatus.OK) {
                    if (results[0].elevation) {
                    	altitude = Math.round(results[0].elevation);
                    }
                }
                $('#edit-altitude').val(altitude);
            });
        }

    });	
    
    
})(jQuery, window, document); 