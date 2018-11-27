(function($, w, d){
    $(d).ready(function() {
    	var stations = Drupal.settings.CreaCartographieMap.stations;
    	var crealng = Drupal.settings.CreaCartographieMap.crealng;
    	var mapOptions = Drupal.settings.CreaCartographieMap.mapOptions;
      var IGNkey = Drupal.settings.CreaCartographieMap.IGNkey;

    	var dateYear = new Date();
    	var selectedYear = dateYear.getFullYear();
            
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
        Drupal.settings.CreaCartographieMap.objetMap = map;

        var markerOff = L.icon({
            iconUrl: '/sites/all/themes/crea/images/marker-icon-off.png',
            iconSize:     [31, 31], // size of the icon
            iconAnchor:   [15, 15], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -10] // point from which the popup should open relative to the iconAnchor
        });

        var markerOn = L.icon({
            iconUrl: '/sites/all/themes/crea/images/marker-icon.png',
            iconSize:     [29, 29], // size of the icon
            iconAnchor:   [14, 14], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -10] // point from which the popup should open relative to the iconAnchor
        });

        var markers = [];

        for (var i=0; i < stations.length; i++){
            var marker = {
                latlng:  [stations[i]['latitude'], stations[i]['longitude']],
                content: '<h4 class="stationTitle">'+stations[i]['title'] + ' (n°'+stations[i]['id_station']+')</h4>'+
                        '<div class="stationBody">'+stations[i]['body']+'</div>',
                id_station: stations[i]['id_station']
            };
            markers.push(marker);
        }

        var selected_id_station = 231; // chamonix
        for (var i=0; i < markers.length; i++){
            if(selected_id_station == markers[i].id_station){
                markerDisplay = markerOn;
            }else{
                markerDisplay = markerOff;
            }
            var marker = L.marker(markers[i].latlng, {icon: markerDisplay, id_station: markers[i].id_station}).addTo(map);
            var popup = L.popup({
                    minWidth: 150
            })
            .setLatLng(markers[i].latlng)
            .setContent(markers[i].content
            + '<input type="hidden" class="marker_id_station" value="' + markers[i].id_station+'" />'); // input hidden avec id_station
            
            marker.on('click', function(e) {
                urlBuilding = '/' + mapOptions['page_language'] + '/buildcharts/week/'+this.options.id_station;
                $( "#graph" ).load( urlBuilding, function() {
                    $('#diagram').show();
                });
                // changement d icone
                for (var i=0; i < markers.length; i++){
                    markers[i].setIcon(markerOff);
                }
                e.target.setIcon(markerOn);
            });
            
            marker.id_station = markers[i].id_station;
            marker.bindPopup(popup);
            markers[i] = marker;
        }

        $('#diagram').append('<div id="graph"></div>');
        
        urlBuilding = '/' + mapOptions['page_language'] + '/buildcharts/week/231';
        $( "#graph" ).load( urlBuilding, function() {
            $('#diagram').show();
            $("#switchLive").addClass('active');
            
            $("#creaChartsForm #edit-submit").click( function() {
            	// http://stackoverflow.com/questions/17632359/how-to-open-leaflet-marker-popup-from-link-outside-of-map
            	var selected_id_station = $("#creaChartsForm #edit-id-station").val();
            	for (var i=0; i < markers.length; i++){
                    // changement d icone
                    markers[i].setIcon(markerOff);
            		if (markers[i].id_station == selected_id_station){
            			markers[i].openPopup();
                        markers[i].setIcon(markerOn);
            			map.panTo(markers[i].getLatLng());
            		}
            	}
            });
        });

    });	
    
    
})(jQuery, window, document); 