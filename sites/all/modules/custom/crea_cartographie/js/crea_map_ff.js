(function($, w, d){
    $(d).ready(function() {
    	var observations = Drupal.settings.CreaFauneFloreMap.observations;
      var crealng = Drupal.settings.CreaFauneFloreMap.crealng;
    	var mapOptions = Drupal.settings.CreaFauneFloreMap.mapOptions;
      var IGNkey = Drupal.settings.CreaFauneFloreMap.IGNkey;
        var group_amphibien = Drupal.settings.CreaFauneFloreMap.group_amphibien;
        var group_mammiferes = Drupal.settings.CreaFauneFloreMap.group_mammiferes;
        var group_oiseaux = Drupal.settings.CreaFauneFloreMap.group_oiseaux;
        var group_reptiles = Drupal.settings.CreaFauneFloreMap.group_reptiles;
        var group_flore = Drupal.settings.CreaFauneFloreMap.group_flore;
        var prot_chocard = Drupal.settings.CreaFauneFloreMap.prot_chocard;
        var prot_grenouille = Drupal.settings.CreaFauneFloreMap.prot_grenouille;
        var prot_mesange = Drupal.settings.CreaFauneFloreMap.prot_mesange;

    	// on cache ou non le datepicker
        typeDate = observations.date_ff;
        if(typeDate == 'custom'){
            $("#crea-contact-fauneflore-form .form-item-date-from").show();
            $("#crea-contact-fauneflore-form .form-item-date-to").show();
            $("#atlas-espaceperso-fauneflore-form .form-item-date-from").show();
            $("#atlas-espaceperso-fauneflore-form .form-item-date-to").show();

        }else{
            $("#crea-contact-fauneflore-form .form-item-date-from").hide();
            $("#crea-contact-fauneflore-form .form-item-date-to").hide();
            $("#atlas-espaceperso-fauneflore-form .form-item-date-from").hide();
            $("#atlas-espaceperso-fauneflore-form .form-item-date-to").hide();
        }

        $('input[name^="date_ff"]').click(function(){
            if($(this).val() == 'custom'){
                $("#crea-contact-fauneflore-form .form-item-date-from").show();
                $("#crea-contact-fauneflore-form .form-item-date-to").show();
                $("#atlas-espaceperso-fauneflore-form .form-item-date-from").show();
                $("#atlas-espaceperso-fauneflore-form .form-item-date-to").show();
            }else{
                $("#crea-contact-fauneflore-form .form-item-date-from").hide();
                $("#crea-contact-fauneflore-form .form-item-date-to").hide();
                $("#atlas-espaceperso-fauneflore-form .form-item-date-from").hide();
                $("#atlas-espaceperso-fauneflore-form .form-item-date-to").hide();
            }
        });

        //L.mapbox.accessToken = 'pk.eyJ1IjoiY2xlbWFkIiwiYSI6ImNpZnkzM2E5ZTAyOHh0bW03cThmYnlraGMifQ.sxu4Iy41LjEsfo34M5emiQ';

        // create the tile layer with correct attribution
        var mapOsm = new L.TileLayer('https://{s}.tile.thunderforest.com/landscape/{z}/{x}/{y}.png?apikey=851c476fad9743cca9b16af9c72ecc05', {
          attribution: 'Map data © <a href="http://openstreetmap.org">OpenStreetMap</a> contributors',
          minZoom: 4,
          maxZoom: 18,
	   accessToken: 'pk.eyJ1IjoiY2xlbWFkIiwiYSI6ImNpZnkzM2E5ZTAyOHh0bW03cThmYnlraGMifQ.sxu4Iy41LjEsfo34M5emiQ'
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

        var entries = observations.entries;

        // icons

        var iconAmphibien = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_amphibiens.png',
            iconSize:     [23, 23], // size of the icon
            iconAnchor:   [11, 11], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });
        var iconMammiferes = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_mammiferes.png',
            iconSize:     [23, 23], // size of the icon
            iconAnchor:   [11, 11], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });
        var iconOiseaux = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_oiseaux.png',
            iconSize:     [23, 23], // size of the icon
            iconAnchor:   [11, 11], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });
        var iconReptiles= L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_reptiles.png',
            iconSize:     [23, 23], // size of the icon
            iconAnchor:   [11, 11], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });
        var iconFlore = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_flore.png',
            iconSize:     [23, 23], // size of the icon
            iconAnchor:   [11, 11], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });

        var iconChocard = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_chocard.png',
            iconSize:     [15, 13], // size of the icon
            iconAnchor:   [7, 6], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });

        var iconGrenouille = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_grenouille.png',
            iconSize:     [15, 15], // size of the icon
            iconAnchor:   [7, 7], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });

        var iconMesange = L.icon({
            iconUrl: '/sites/all/themes/crea/images/icon_mesange.png',
            iconSize:     [23, 23], // size of the icon
            iconAnchor:   [11, 11], // point of the icon which will correspond to marker's location
            popupAnchor:  [0, -5] // point from which the popup should open relative to the iconAnchor
        });

        // creation map
        var map = L.map('map', 'mapbox.streets')
            .setView([mapOptions['map_lat'], mapOptions['map_long']], mapOptions['map_zoom']);

        map.addLayer(mapOsm);

        L.control.layers({
            "OSM satellite": mapOsmSat,
            "OpenStreetMap carte": mapOsm,
            "IGN satellite": mapIgnSat
        }).addTo(map);

        for (var entry in entries){
            // altitude
            alti = entries[entry]['altitude'];
            if(alti != '' && alti != 0){
                altitude = 'Altitude : '+entries[entry]['altitude']+'m<br/>';
            }else{
                altitude = '';
            }
            // date
            dateobs = entries[entry]['dateobs'];
            if(crealng.drupal_lng != "en"){
                dateobs = dateobs.substring(8,10)+"/"+dateobs.substring(5,7)+"/"+dateobs.substring(0,4)
            }
            var markerObject = {
                latlng:  [entries[entry].lat, entries[entry].long],
                content: '',
                title:entries[entry].nom,
                id_obs: entries[entry]['id'],
                nbobs: entries[entry]['nbobs'],
                groupe: entries[entry]['groupe']
            };

            // contenu popup

            if(markerObject.nbobs == 1){
                markerObject.content = '<h4 class="obsTitle">'+entries[entry].nom + '</h4>'+
                entries[entry]['pic']+
                '<div class="obsBody">'+
                altitude+
                crealng.author+' : '+entries[entry]['obs']+'<br/>'+
                crealng.view+' : '+dateobs +
                '</div>';
            }else{
                markerObject.content = '<h4 class="obsTitle">'+entries[entry].nom + '</h4>'+
                entries[entry]['pic']+
                '<div class="obsBody">'+
                altitude+
                crealng.nbobs+' : '+entries[entry]['nbobs']+'<br/>'+
                crealng.lastobs+' : '+dateobs +
                '</div>';
            }

            // icon marker
            switch(entries[entry]['prot']) {
                // chocard
                case prot_chocard:
                    iconLoad = iconChocard;
                    break;
                // grenouille
                case prot_grenouille:
                    iconLoad = iconGrenouille;
                    break;
                // mesange
                case prot_mesange:
                    iconLoad = iconMesange;
                    break;
                // contact faune ou faune flore smiplifiée
                default:
                    switch(markerObject.groupe){
                        case ''+group_amphibien:
                            iconLoad = iconAmphibien;
                            break;
                        case ''+group_mammiferes:
                            iconLoad = iconMammiferes;
                            break;
                        case ''+group_oiseaux:
                            iconLoad = iconOiseaux;
                            break;
                        case ''+group_reptiles:
                            iconLoad = iconReptiles;
                            break;
                        case ''+group_flore:
                            iconLoad = iconFlore;
                            break;
                    }
                    break;
            }

            if(!isNaN(entries[entry].lat) && !isNaN(entries[entry].long) &&
                entries[entry].lat != 0 && entries[entry].long != 0){
                var popup = L.popup({
                    minWidth: 150
                }).setLatLng(markerObject.latlng)
                    .setContent(markerObject.content);
                var marker = L.marker(new L.LatLng(markerObject.latlng[0], markerObject.latlng[1]), {
                    icon: iconLoad,
                    title: markerObject.title
                });
                marker.bindPopup(popup);
                marker.addTo(map);
            }
        }

        // colorbox quand on a des images
        $('#map').on('click', '.colorbox', function() {
            $(".colorbox").colorbox();
        });
    });
    
    
})(jQuery, window, document); 