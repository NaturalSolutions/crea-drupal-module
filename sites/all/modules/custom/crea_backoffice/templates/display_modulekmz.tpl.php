<?php
global $base_url;
$modulekmz = $element['#object']->field_module_kmz['und'];
$nid = $content_modulekmz['#items'][0]['nid'];

if(count($modulekmz) > 0){
    // on parcourt le tableau de modules (tabs)
    $kmz = array();
    foreach($modulekmz as $key => $modkmz){
        $kmz[$key] = array();
        $kmz[$key]['title'] = $modkmz['node']->title;
        $kmz[$key]['body'] = $modkmz['node']->body;
        $list_kmz = $modkmz['node']->scald_file;
        $kmz[$key]['kmz'] = array();
        foreach($list_kmz['und'] as $k){
            $kmz[$key]['kmz'][$k['fid']] = array();
            $url = file_create_url($k['uri']);
            $url = parse_url($url);
            $kmz[$key]['kmz'][$k['fid']]['url'] = $url['scheme'].'://'.$url['host'].$url['path'];
           //$kmz[$key]['kmz'][$k['fid']]['url'] = 'http://vps144491.ovh.net'.str_replace('default/files','all/themes/crea/kmz', $url['path']);
            $kmz[$key]['kmz'][$k['fid']]['desc'] = $k['description'];
        }
    }
    //print_r($kmz);
?>
    <link rel="stylesheet" href="//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css">
    <link rel="stylesheet" type="text/css" href="<?php echo $base_url . '/' . drupal_get_path('theme', 'crea_bootstrap'); ?>/js/leaflet/leaflet.css">
    <script src="//code.jquery.com/ui/1.11.4/jquery-ui.js"></script>
    <script>
        /* jquery slider pips plugin, version 0.1 */

        (function($) {

            var extensionMethods = {

                pips: function( settings ) {

                    options = {

                        first: 	"number", 	// "pip" , false
                        last: 	"number", 	// "pip" , false
                        rest: 	"pip" 		// "number" , false

                    };

                    $.extend( options, settings );

                    // get rid of all pips that might already exist.
                    this.element.addClass('ui-slider-pips').find( '.ui-slider-pip' ).remove();

                    // we need teh amount of pips to create.
                    var pips = this.options.max - this.options.min;

                    // for every stop in the slider, we create a pip.
                    for( i=0; i<=pips; i++ ) {

                        // hold a span element for the pip
                        var s = $('<span class="ui-slider-pip"><span class="ui-slider-line"></span><span class="ui-slider-number">'+tabShortLegend[i]+'</span></span>');

                        // add a class so css can handle the display
                        // we'll hide numbers by default in CSS, and show them if set.
                        // we'll also use CSS to hide the pip altogether.
                        if( 0 == i ) {
                            s.addClass('ui-slider-pip-first');
                            if( "number" == options.first ) { s.addClass('ui-slider-pip-number'); }
                            if( false == options.first ) { s.addClass('ui-slider-pip-hide'); }
                        } else if ( pips == i ) {
                            s.addClass('ui-slider-pip-last');
                            if( "number" == options.last ) { s.addClass('ui-slider-pip-number'); }
                            if( false == options.last ) { s.addClass('ui-slider-pip-hide'); }
                        } else {
                            if( "number" == options.rest ) { s.addClass('ui-slider-pip-number'); }
                            if( false == options.rest ) { s.addClass('ui-slider-pip-hide'); }
                        }


                        // if it's a horizontal slider we'll set the left offset,
                        // and the top if it's vertical.
                        if( this.options.orientation == "horizontal" )
                            s.css({ left: '' + (100/pips)*i + '%'  });
                        else
                            s.css({ top: '' + (100/pips)*i + '%'  });


                        // append the span to the slider.
                        this.element.append( s );

                    }

                }


            };

            $.extend(true, $['ui']['slider'].prototype, extensionMethods);


        })(jQuery);

        (function($) {

            var extensionMethods = {

                float: function( settings ) {

                    options = {};
                    $.extend( options, settings );

                    // add a class for the CSS
                    this.element.addClass('ui-slider-float');


                    // if this is a range slider
                    if( this.options.values ) {

                        var $tip = [
                            $('<span class="ui-slider-tip">'+ this.options.values[0]+'</span>'),
                            $('<span class="ui-slider-tip">'+ this.options.values[1]+'</span>')
                        ];


                        // else if its just a normal slider
                    } else {

                        // create a tip element
                        var $tip = $('<span class="ui-slider-tip">'+ this.options.value+'</span>');

                    }

                    // now we append it to all the handles
                    this.element.find('.ui-slider-handle').each( function(k,v) {
                        $(v).append($tip[k]);
                    })

                    // if this slider also has numbers, we'll make those into tips, too; by cloning and changing class.
                    this.element.find('.ui-slider-number').each(function(k,v) {
                        var $e = $(v).clone().removeClass('ui-slider-number').addClass('ui-slider-tip-number');
                        $e.insertAfter($(v));
                    });

                    // when slider changes, update handle tip value.
                    this.element.on('slidechange slide', function(e,ui) {
                        $(ui.handle).find('.ui-slider-tip').text( ui.value );
                    });

                }


            };

            $.extend(true, $['ui']['slider'].prototype, extensionMethods);


        })(jQuery);
    </script>
    <style>
        @import url('http://fonts.googleapis.com/css?family=Bitter:400,700,400italic');

        /* ui slider pips */

        .ui-slider-horizontal.ui-slider-pips { margin-bottom: 2.8em; }
        .ui-slider-pips .ui-slider-number,
        .ui-slider-pips .ui-slider-pip-hide { display: none; }
        .ui-slider-pips .ui-slider-pip-number .ui-slider-number { display: block; }

        .ui-slider-pips .ui-slider-pip {
            width: 2em; height: 1em; line-height: 1em; position: absolute;
            font-size: 0.8em; color: #999; overflow: visible; text-align: center;
            top: 20px; left: 20px; margin-left: -1em; cursor: pointer;
        }
        .ui-slider-pips .ui-slider-line { background: #999; width: 1px; height: 3px; position: absolute; left: 50%; }
        .ui-slider-pips .ui-slider-number { position: absolute; top: 5px; left: 50%; font-size: 12px; margin-left: -6em;  width: 12em; 'Klavika-Light', 'Tahoma', sans-serif !important}
        .ui-slider-pip:hover .ui-slider-number { font-weight: bold; }

        .ui-slider-vertical.ui-slider-pips { margin-bottom: 0; margin-right: 2em; }
        .ui-slider-vertical.ui-slider-pips .ui-slider-pip {
            text-align: left; top: 20px; left: 20px; margin-left: 0; margin-top: -0.5em;
        }
        .ui-slider-vertical.ui-slider-pips .ui-slider-line { width: 3px; height: 1px; position: absolute; top: 50%; left: 0; }
        .ui-slider-vertical.ui-slider-pips .ui-slider-number { top: 50%; left: 0.5em; margin-left: 0; margin-top: -0.5em; width: 2em; }
        .ui-slider-vertical.ui-slider-pip:hover .ui-slider-number { color: white; font-weight: bold; }



        .ui-slider-float .ui-slider-handle {

        }

        .ui-slider-float .ui-slider-tip,
        .ui-slider-float .ui-slider-tip-number {
            position: absolute; visibility: hidden;
            top: -40px; display: block;
            width: 34px; margin-left: -17px; left: 50%;
            height: 20px; line-height: 20px;
            background: white; border-radius: 3px;
            box-shadow: 0 0 3px rgba(0,0,0,0.4);
            text-align: center;
            font-size: 12px;
            opacity: -1; transition: all 0.4s ease;
            color: #333;
        }

        .ui-slider-float .ui-slider-handle:hover .ui-slider-tip,
        .ui-slider-float .ui-slider-handle:focus .ui-slider-tip,
        .ui-slider-float .ui-slider-pip:hover .ui-slider-tip-number{ opacity: 0.9; top: -30px; color: #333; visibility: visible; }

        .ui-slider-float .ui-slider-pip .ui-slider-tip-number { top: 15px; }
        .ui-slider-float .ui-slider-pip:hover .ui-slider-tip-number { top: 5px; font-weight: normal; }

        .ui-slider-float .ui-slider-tip:after,
        .ui-slider-float .ui-slider-pip .ui-slider-tip-number:after {
            content: " ";
            width: 0; height: 0;
            border: 5px solid rgba(255,255,255,0);
            border-top-color: rgba(255,255,255,1);
            position: absolute;
            bottom: -10px; left: 50%; margin-left: -5px;
        }

        .ui-slider-float .ui-slider-pip .ui-slider-tip-number:after {
            border: 5px solid rgba(255,255,255,0);
            border-bottom-color: rgba(255,255,255,1);
            top: -10px;
        }

        /* demo stuff */
        .ui-slider-horizontal { height: 10px; background: #ddd; }
        .ui-slider-horizontal .ui-slider-handle { height: 18px; width: 14px; background: #fbb900; border: 1px solid rgba(0,0,0,0.6); margin-left: -8px; cursor: pointer; }
        .ui-slider-horizontal.green .ui-slider-handle { background: #fbb900;}

        @media (max-width: 700px) {
            .ui-slider-pip:nth-child(odd) .ui-slider-number { display: none; }
        }

        @media (max-width: 400px) {
            .ui-slider-pip:nth-child(2n+1) .ui-slider-number { display: none; }
            .ui-slider-pip:nth-child(4n) .ui-slider-number { display: none; }
        }

    </style>
    <script>
        var tabKMZ = [];
        <?php for($i = 0; $i < count($modulekmz); $i++){ ?>
        tabKMZ[<?php print $i; ?>] = [];
        <?php
            foreach($kmz[$i]['kmz'] as $k){
        ?>
        tabKMZ[<?php print $i; ?>].push({url:"<?php echo $k['url']; ?>", desc:"<?php echo $k['desc']; ?>"});
        <?php
            }
        ?>
        <?php } ?>

        var map;
        var kmzLayer;
        var tabShortLegend;

        var historicalOverlay;

        // fonction appelée au changement de tab
        function loadTab(id){
            if(id == undefined){
                tabSelected = jQuery( "#modulekmz-<?php print $nid; ?> li.ui-state-active").attr('aria-controls').substring(5);
                id = tabSelected-1;
            }else{
                id = id-1;
            }

            map = new google.maps.Map(jQuery("#modulekmz-<?php print $nid; ?> .map").get(0), {
                scaleControl: true,
                mapTypeId: google.maps.MapTypeId.HYBRID,
                zoom: 10,
                center:{lat:45.9, lng: 6.90}
            });

            tabLayers = [];

            // on supprime les layers
            while(tabLayers[0]){
                tabLayers.pop().setMap(null);
            }
            // premier kmz
            kmzLayer = new google.maps.KmlLayer({
                url: tabKMZ[id][0].url,
                preserveViewport: true
            });
            kmzLayer.setMap(map);
            tabLayers.push(kmzLayer);

            // gestion transparence quand on change de zoom
            map.addListener('zoom_changed', function() {
                console.log('Zoom: ' + map.getZoom()+" - "+jQuery(".map-kmz").find("img[src*='kmz']").css("opacity"));
                jQuery(".map-kmz").find("img[src*='kmz']").css("opacity","0.6");
            });
            jQuery(".map-kmz").find("img[src*='kmz']").css("opacity","0.6");

            // légende pour le slider
            tabShortLegend = [];
            for(i=0; i < tabKMZ[id].length; i++){
                tabShortLegend.push(tabKMZ[id][i].desc);
            }

            // creation du slider
            jQuery( "#tabs-"+(id+1)+" .slider" ).slider({
                animate: true,
                range: "min",
                value: 0,
                min: 0,
                max: tabKMZ[id].length-1,
                slide: function( event, ui ) {
                    // on supprime les layers
                    while(tabLayers[0]){
                        tabLayers.pop().setMap(null);
                    }
                    kmzLayer = new google.maps.KmlLayer({
                        url: tabKMZ[id][ui.value].url,
                        preserveViewport: true
                    });
                    kmzLayer.setMap(map);
                    tabLayers.push(kmzLayer);
                }
            }).slider('pips', {rest:'number'});
        }
    </script>
    <style type="text/css">
        html, body { height: 100%; margin: 0; padding: 0; }
        .map { height: 600px; }
        .modkmz{
            float: left;
            width:49%;
        }
        .map-kmz, .body-kmz{
            float:left;
        }
        .body-kmz{
            width:100%;
        }
        .map-kmz{
            margin-right:1%;
            margin-top:1%;
            width:49%;
        }
        .ui-tabs .ui-tabs-panel{
            padding: 0.3em 0em;
        }
        img[src*="kmz"]{
            opacity:.6;
        }
    </style>
  <div class="container">
    <div class="modulekmz" id="modulekmz-<?php print $nid; ?>">
        <ul>
            <?php
            $i = 1;
            foreach($kmz as $k){
                ?>
                <li><a href="#tabs-<?php print $nid; ?>-<?php echo $i; ?>"><?php echo $k['title']; ?></a></li>
                <?php
                $i++;
            }
            ?>
        </ul>
        <div class="map-kmz">
            <div class="map"></div>
        </div>
        <?php
        $i = 1;
        foreach($kmz as $k){
            ?>
            <div id="tabs-<?php print $nid; ?>-<?php echo $i; ?>" class="modkmz">
                <div class="body-kmz">
                    <?php
                    if(count($k['kmz']) > 1){
                        // affichage avec slider
                        ?>
                        <div class="slider" class="yellow"></div>
                    <?php
                    }
                    ?>
                    <?php echo $k['body']['und'][0]['value']; ?>
                </div>
            </div>
            <?php
            $i++;
        }
        ?>
    </div>
  </div>
    <script type="text/javascript">
        var tabSelected;
        (function ($) {
            // init
            $( "#modulekmz-<?php print $nid; ?>" ).tabs({
                activate: function(event, ui) {
                    window.location.hash=ui.newPanel.selector;
                    loadTab(ui.newPanel.selector.substring(6));
                }
            });
        })(jQuery);
    </script>
    <script async defer
            src="https://maps.googleapis.com/maps/api/js?key=AIzaSyB5iHFGsoZLbBJz3X6e6Ja5AhikHOcy9BM&callback=loadTab">
    </script>
<?php
}
?>