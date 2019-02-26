jQuery(function($) {
    $(document).ready(function() {
        $('[data-toggle="popover"]').popover();
        // image map
        $('img[usemap]').rwdImageMaps();

        // si modules live on ne fait pas le iframe resize
        if(!$('#modulelive iframe').length) {
            $('iframe').iFrameResize(
                {
                    'checkOrigin': ['http://127.0.0.1:8000', 'https://backend.phenoclim.org', 'https://creamontblanc.shinyapps.io'], 
                    'heightCalculationMethod': 'documentElementOffset'
                }
            );
        }

        if($('#map_container #map').length) {
            // si on est sur les pages especes en live ou climat live
            iframeHeight = $('#map_container').height();
            window.parent.resizeModuleLive(iframeHeight);
        }
    });
});

function resizeModuleLive(hauteur){
    jQuery('#modulelive iframe').height(hauteur+30);
}