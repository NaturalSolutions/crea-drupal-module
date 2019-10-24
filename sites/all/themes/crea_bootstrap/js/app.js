jQuery(function($) {
    $(document).ready(function() {
        $('[data-toggle="popover"]').popover();
        // image map
        $('img[usemap]').rwdImageMaps();

        // si modules live on ne fait pas le iframe resize
        if(!$('#modulelive iframe').length) {
            $('iframe').iFrameResize(
                {
                    //log: true,
                    enablePublicMethods: true,
                    'checkOrigin': ['http://devback.phenoclim.org', 'https://devback.phenoclim.org', 'http://127.0.0.1:8000', 'https://backend.phenoclim.org', 'https://creamontblanc.shinyapps.io'], 
                    'heightCalculationMethod': 'documentElementOffset',
                    messageCallback : function(messageData) {
                        console.log('messagefrom Iframe messageCallback: ', messageData.message);
                        console.log('messagefrom Iframe messageData.iframe.offsetTop: ', messageData.iframe.offsetTop)

                        if (messageData.message && messageData.message.positionScroll) {
                            scrollTo(0,messageData.iframe.offsetTop + messageData.message.positionScroll);
                        } else {
                            scrollTo(0,( messageData.iframe.offsetTop - 40) + 0);
                        }
                    }
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
