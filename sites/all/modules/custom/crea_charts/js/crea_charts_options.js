(function($, w, d){
/**
 * config globale Highcharts
 */
var crealng = Drupal.settings.CreaCartographieMap.crealng;

Highcharts.setOptions({
    lang: {
        contextButtonTitle: crealng.contextButtonTitle,
        downloadJPEG: crealng.downloadJPEG,
        downloadPDF: crealng.downloadPDF,
        downloadPNG: crealng.downloadPNG,
        downloadSVG: crealng.downloadSVG,
        printChart: crealng.printChart,
        loading: crealng.loading,
        resetZoom: crealng.resetZoom,
        resetZoomTitle: crealng.resetZoomTitle,
        shortMonths: [
            crealng.shortMonths[0],
            crealng.shortMonths[1],
            crealng.shortMonths[2],
            crealng.shortMonths[3],
            crealng.shortMonths[4],
            crealng.shortMonths[5],
            crealng.shortMonths[6],
            crealng.shortMonths[7],
            crealng.shortMonths[8],
            crealng.shortMonths[9],
            crealng.shortMonths[10],
            crealng.shortMonths[11]
        ],
        months: [
            crealng.months[0],
            crealng.months[1],
            crealng.months[2],
            crealng.months[3],
            crealng.months[4],
            crealng.months[5],
            crealng.months[6],
            crealng.months[7],
            crealng.months[8],
            crealng.months[9],
            crealng.months[10],
            crealng.months[11]
        ],
        weekdays: [
            crealng.weekdays[0],
            crealng.weekdays[1],
            crealng.weekdays[2],
            crealng.weekdays[3],
            crealng.weekdays[4],
            crealng.weekdays[5],
            crealng.weekdays[6]
        ],
        rangeSelectorFrom: crealng.rangeSelectorFrom,
        rangeSelectorTo: crealng.rangeSelectorTo,
        noData: crealng.noData
    },
    global: {
        useUTC: false
    },
    exporting: {
    	sourceWidth: 1400,
    	sourceHeight: 1000,
    	chartOptions:{
            title: {
                text:'aaaaa'
            }
        }
    }
});

})(jQuery, window, document);