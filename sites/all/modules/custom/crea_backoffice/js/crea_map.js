(function($, w, d){
    $(d).ready(function() {
    	var mapOptions = Drupal.settings.CreaCartographieMap.mapOptions;
    	var mapMarkers = Drupal.settings.CreaCartographieMap.mapMarkers;
    	var mapIcon = Drupal.settings.CreaCartographieMap.mapIcon;
    	var mapIconShadow = Drupal.settings.CreaCartographieMap.mapIconShadow;
      var IGNkey = Drupal.settings.CreaCartographieMap.IGNkey;
            
    	var map;
    	var numMarkers = 0;
    	var markers = [];

        var ajaxRequest;
        var plotlist;
        var plotlayers=[];
        
        var greenIcon = L.icon({
            iconUrl: mapIcon,
            iconSize:     [25, 41], // size of the icon
            iconAnchor:   [12, 41], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -41] // point from which the popup should open relative to the iconAnchor
        });
        
        var greenIconHover = L.icon({
            iconUrl: mapIcon,
            iconSize:     [25, 41], // size of the icon
            iconAnchor:   [12, 41], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -41], // point from which the popup should open relative to the iconAnchor
        	shadowUrl: mapIconShadow,
        	shadowSize: [27, 48],
        	shadowAnchor: [13, 41]
        });

        map = new L.Map('map');
        
        // create the tile layer with correct attribution
        var mapRelief = new L.TileLayer('https://{s}.tile.thunderforest.com/landscape/{z}/{x}/{y}.png?apikey=851c476fad9743cca9b16af9c72ecc05', {
          attribution: 'Map data © <a href="http://openstreetmap.org">OpenStreetMap</a> contributors',
          minZoom: 4,
          maxZoom: 18
        });
        var mapHybrid = new L.TileLayer('http://gpp3-wxs.ign.fr/{accessToken}/geoportail/wmts?LAYER=ORTHOIMAGERY.ORTHOPHOTOS&EXCEPTIONS=text/xml&FORMAT=image/jpeg&SERVICE=WMTS&VERSION=1.0.0&REQUEST=GetTile&STYLE=normal&TILEMATRIXSET=PM&TILEMATRIX={z}&TILEROW={y}&TILECOL={x}', {
          attribution: "<a href='http://www.mapbox.com/about/maps/' target='_blank'>&copy; Mapbox &copy; OpenStreetMap</a> <a class='mapbox-improve-map' href='https://www.mapbox.com/map-feedback/' target='_blank'>Improve this map</a>",
          minZoom: 4,
          maxZoom: 18,
          //id: 'mapbox.streets-satellite',
          accessToken: IGNkey
        });

        /*var mapHybrid = new L.TileLayer('https://api.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={accessToken}', {
         attribution: "<a href='http://www.mapbox.com/about/maps/' target='_blank'>&copy; Mapbox &copy; OpenStreetMap</a> <a class='mapbox-improve-map' href='https://www.mapbox.com/map-feedback/' target='_blank'>Improve this map</a>",
         minZoom: 4,
         maxZoom: 18,
         id: 'mapbox.streets-satellite',
         accessToken: 'pk.eyJ1IjoiY2xlbWFkIiwiYSI6ImNpZnkzM2E5ZTAyOHh0bW03cThmYnlraGMifQ.sxu4Iy41LjEsfo34M5emiQ'
         });*/
        
        map.setView(new L.LatLng(mapOptions['map_lat'], mapOptions['map_long']), mapOptions['map_zoom']);
        map.addLayer(mapRelief);
        
        L.control.layers({
            "Relief": mapRelief,
            "Satellite": mapHybrid
        }).addTo(map);
        
        $.each(mapMarkers, function(key, value){
        	addMarker({latlng: new L.LatLng(value.lat, value.long)});
        });

        function addMarker(e){        	
            var newMarker = new L.marker(e.latlng, {icon: greenIcon}).addTo(map);
            markers.push(newMarker);
            var currentNumMarker = numMarkers;
            
            newMarker.on('mouseover', function(e) {
            	cleanAllMarkers();

            	$('#crea-backoffice-validate-pffs-submissions-form .table-select-processed tbody tr:eq(' + currentNumMarker + ')').addClass("selected");
                newMarker.setIcon(greenIconHover);
            });
            
            numMarkers++;
        }
        
        $('#crea-backoffice-validate-pffs-submissions-form .table-select-processed tbody tr').on('mouseover', function(e) {
        	
        	var selectedRow = $(this).index();
        	cleanAllMarkers();
        	
        	$('#crea-backoffice-validate-pffs-submissions-form .table-select-processed tbody tr:eq(' + selectedRow + ')').addClass("selected");
        	markers[selectedRow].setIcon(greenIconHover);
        	
        	map.setZoom(map.getZoom());
            map.setView(markers[selectedRow].getLatLng());
        });
        
        function cleanAllMarkers(){
        	$.each(markers, function(key, value){
        		$('#crea-backoffice-validate-pffs-submissions-form .table-select-processed tbody tr').removeClass("selected");
        		markers[key].setIcon(greenIcon);
        	});
        }

    });	
    
    
})(jQuery, window, document); 