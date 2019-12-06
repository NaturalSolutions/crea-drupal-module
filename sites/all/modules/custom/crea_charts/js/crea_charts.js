(function($, w, d){

    var crealng = Drupal.settings.CreaCartographieMap.crealng;
    var mymap = Drupal.settings.CreaCartographieMap.objetMap;

    Highcharts.setOptions({
        lang: {
            loading: crealng.loading_charts
        }
    });
    /**
     * fonction appelée pour construire le graphique
     * @param {string} typeGraph type chart : week|year
     */
     function loadCharts(typeGraph){
        $("#typeGraph").attr("value",typeGraph);

        // recuperation du JSON
        id_station = $("#creaChartsForm #edit-id-station").val();

        if (window.chart)
            window.chart.showLoading()

        urlRebuild = '/fr/gimmechartsdata/'+ typeGraph +'/'+ id_station ;
        $.getJSON(urlRebuild, function (data) {
            if (window.chart)
                window.chart.hideLoading();

            $('#switchCharts').show();
            $('#creaChartsForm').show();
            // ajout pour pin jaune
            var selected_id_station = $("#creaChartsForm #edit-id-station").val();
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
            mymap.eachLayer(function(marker) {
                if(marker instanceof L.Marker){
                    if(selected_id_station == marker.id_station){
                        markerDisplay = markerOn;
                        marker.openPopup();
                        mymap.panTo(marker.getLatLng());
                    }else{
                        markerDisplay = markerOff;
                    }
                    marker.setIcon(markerDisplay);
                }
            });

            // variables spécifiques au format de date
            if(crealng.drupal_lng == "fr"){
                var date_inputDateFormat = '%d-%m-%Y';
                var date_xDateFormat = "%d/%m/%Y";
                var date_xDateFormatPlus = "%d/%m/%Y %H:%M";
                var date_timeLabelFormats = {
                    millisecond:"%A %e/%b %H:%M:%S.%L",
                    second:"%A %e/%b %H:%M:%S",
                    minute:"%A %e/%b %H:%M",
                    hour:"%A %e/%b %H:%M",
                    day:"%A %e/%b/%Y",
                    week:crealng.weekfrom+" %A %e/%b/%Y",
                    month:"%B %Y",
                    year:"%Y"
                };
                var date_dateTimeLabelFormats = {
                    millisecond: ['%A %e/%b %H:%M:%S.%L', '%A %e/%b %H:%M:%S.%L', '-%H:%M:%S.%L'],
                    second: ['%A %e/%b %H:%M:%S', '%A %e/%b %H:%M:%S', '-%H:%M:%S'],
                    minute: ['%A %e/%b %H:%M', '%A %e/%b %H:%M', '-%H:%M'],
                    hour: ['%A %e/%b %H:%M', '%A %e/%b %H:%M', '-%H:%M'],
                    day: ['%A %e/%b/%Y', '%A %e/%b', '-%A %e/%b/%Y'],
                    week: [crealng.weekfrom+' %A %e/%b/%Y', '%A %e/%b', '-%A %e/%b/%Y'],
                    month: ['%B %Y', '%B', '-%B %Y'],
                    year: ['%Y', '%Y', '-%Y']
                };
                var pickerdateFormat = 'dd-mm-yy';
                var date_val1 = 2;
                var date_val2 = 1;
                var date_val3 = 0;
            }else{
                var date_inputDateFormat = '%Y-%m-%d';
                var date_xDateFormat = "%Y/%m/%d";
                var date_xDateFormatPlus = "%Y/%m/%d %H:%M";
                var date_timeLabelFormats = {
                    millisecond:"%A %b/%e %H:%M:%S.%L",
                    second:"%A %b/%e %H:%M:%S",
                    minute:"%A %b/%e %H:%M",
                    hour:"%A %b/%e %H:%M",
                    day:"%A %Y/%b/%e",
                    week:crealng.weekfrom+" %A %Y/%b/%e",
                    month:"%B %Y",
                    year:"%Y"
                };
                var date_dateTimeLabelFormats = {
                    millisecond: ['%A %b/%e %H:%M:%S.%L', '%A %b/%e %H:%M:%S.%L', '-%H:%M:%S.%L'],
                        second: ['%A %b/%e %H:%M:%S', '%A %b/%e %H:%M:%S', '-%H:%M:%S'],
                        minute: ['%A %b/%e %H:%M', '%A %b/%e %H:%M', '-%H:%M'],
                        hour: ['%A %b/%e %H:%M', '%A %b/%e %H:%M', '-%H:%M'],
                        day: ['%A %b/%e/%Y', '%A %b/%e', '-%A %Y/%b/%e'],
                        week: [crealng.weekfrom+' %A %Y/%b/%e', '%A %b/%e', '-%A %Y/%b/%e'],
                        month: ['%B %Y', '%B', '-%B %Y'],
                        year: ['%Y', '%Y', '-%Y']
                };
                var pickerdateFormat = 'yy-mm-dd';
                var date_val1 = 0;
                var date_val2 = 1;
                var date_val3 = 2;
            }
            // chargement graphe
            if(typeGraph == "year"){
                window.chart = new Highcharts.StockChart({
                    chart: {
                        renderTo: 'containerCharts',
                        ignoreHiddenSeries: false,
                        zoomType: 'x',
                        type: 'spline',
                        animation: false,
                        events: {
                            load: function() {
                                $("#containerCharts input[type='checkbox']").each(function( index ) {

                                });
                            }
                        },
                    },
                    rangeSelector: {
                        inputDateFormat: date_inputDateFormat,
                        inputEditDateFormat: date_inputDateFormat,
                        inputDateParser: function (value) {
                            value = value.split(/[-\.]/);
                            return Date.UTC(
                                value[date_val1],
                                value[date_val2]-1,
                                value[date_val3]
                            );
                        },
                        buttons: [{
                            type: 'month',
                            count: 1,
                            text: crealng.onemonth
                        }, {
                            type: 'month',
                            count: 3,
                            text: crealng.threemonth
                        }, {
                            type: 'year',
                            count: 1,
                            text: crealng.oneyear
                        }],
                        buttonTheme: {
                            width: 60
                        },
                        selected: 2
                    },
                    colors: ['#000000', '#9a9a9a', '#ffbf00', '#e74a00'],
                    credits: {
                        enabled: false
                    },
                    title: {
                        text: ''
                    },
                    subtitle: {
                        text: document.ontouchstart === undefined ?
                            crealng.select_range_time :
                            crealng.select_range_time
                    },
                    tooltip: {
                        backgroundColor: 'rgba(255, 255, 255, 1)',
                        borderColor: '#FFF',
                        headerFormat: '<span style="font-size: 12px; font-weight:bold">{point.key}</span><br/>',
                        valueSuffix: ' °C',
                        shared: true,
                        xDateFormat: date_xDateFormat,
                        dateTimeLabelFormats:date_timeLabelFormats,
                        valueDecimals: 2
                    },
                    xAxis: {
                        type: 'datetime',
                        ordinal : false,
                        minRange:  24 * 3600000 // 1 jour
                    },
                    yAxis: {
                        title: {
                            text: crealng.temperatures
                        }
                    },
                    legend: {
                        enabled: true,
                        align : 'center',
                        rtl: false
                    },
                    plotOptions: {
                        series: {
                            marker: {
                                enabled: false
                            },
                            lineWidth: 1,
                            /*showCheckbox : true,*/
                            pointInterval: 24 * 3600 * 1000,
                            events: {
                                checkboxClick: function (event) {
                                    if (event.checked) {
                                        this.show();
                                    } else {
                                        this.hide();
                                    }
                                    event.preventDefault();
                                },
                                legendItemClick: function(event) {
                                    $("#containerCharts input[type='checkbox']").each(function( index ) {
                                        if(index == event.currentTarget._i){
                                            if( $(this).is(':checked') ){
                                                $(this).prop( "checked", false );
                                            }else{
                                                $(this).prop( "checked", true );
                                            }
                                        }
                                    });
                                }
                            }
                        }
                    },

                    series: [
                        {
                            selected: true,
                            dataGrouping:{
                                dateTimeLabelFormats:date_dateTimeLabelFormats
                            },
                            name: crealng.capteur1,
                            data: data[0]
                        },
                        {
                            dataGrouping:{
                                dateTimeLabelFormats:date_dateTimeLabelFormats
                            },
                            name: crealng.capteur2,
                            data: data[1]
                        },
                        {
                            dataGrouping:{
                                dateTimeLabelFormats:date_dateTimeLabelFormats
                            },
                            name: crealng.capteur3,
                            data: data[2]
                        },
                        {
                            selected: true,
                            dataGrouping:{
                                dateTimeLabelFormats:date_dateTimeLabelFormats
                            },
                            name: crealng.capteur4,
                            data: data[3]
                        },
                    ],
                    noData: {
                        style: {
                            fontWeight: 'bold',
                            fontSize: '15px',
                            color: '#303030'
                        }
                    },
                    loading: {
                        labelStyle: {
                            color: 'white'
                        },
                        style: {
                            backgroundColor: 'gray'
                        }
                    }
                }, function (chart) {
                    // apply the date pickers
                    setTimeout(function () {
                        if(chart.options != undefined) {
                            $('input.highcharts-range-selector', $('#' + chart.options.chart.renderTo)).datepicker()
                        }
                    }, 500);
                    var series = chart.series;
                    if( series[0].checkbox) {
                        series[0].checkbox.style.marginLeft = '-205px';
                    }
                    if( series[1].checkbox) {
                        series[1].checkbox.style.marginLeft = '-150px';
                    }
                    if( series[2].checkbox) {
                        series[2].checkbox.style.marginLeft = '-200px';
                    }
                    if( series[3].checkbox) {
                        series[3].checkbox.style.marginLeft = '-185px';
                    }
                });
                if($("#notstandalone").length){
                    $("#switchLive").html(crealng.access_week);
                    $("#switchAverage").html(crealng.access_year);
                }else{
                }
            }else{
                window.chart = new Highcharts.Chart({
                    chart: {
                        renderTo: 'containerCharts',
                        ignoreHiddenSeries: false,
                        zoomType: 'x',
                        type: 'spline',
                        animation: false
                    },
                    colors: ['#000000', '#9a9a9a', '#ffbf00', '#e74a00'],
                    credits: {
                        enabled: false
                    },
                    title: {
                        text: ''
                    },
                    subtitle: {
                        text: document.ontouchstart === undefined ?
                            crealng.zoom :
                            crealng.release
                    },
                    tooltip: {
                        backgroundColor: 'rgba(255, 255, 255, 1)',
                        borderColor: '#FFF',
                        headerFormat: '<span style="font-size: 12px; font-weight:bold">{point.key}</span><br/>',
                        valueSuffix: ' °C',
                        shared: true,
                        xDateFormat: date_xDateFormatPlus
                    },
                    xAxis: {
                        type: 'datetime',
                        minRange:  90000 // 15mn
                    },
                    yAxis: {
                        title: {
                            text: crealng.temperatures
                        }
                    },
                    legend: {
                        enabled: true,
                        align : 'center',
                        rtl: false
                    },
                    plotOptions: {
                        series: {
                            marker: {
                                enabled: false
                            },
                            lineWidth: 1,
                            /*showCheckbox : true,*/
                            pointInterval: 900 * 1000,
                            events: {
                                checkboxClick: function (event) {
                                    if (event.checked) {
                                        this.show();
                                    } else {
                                        this.hide();
                                    }
                                    event.preventDefault();
                                },
                                legendItemClick: function(event) {
                                    $("#containerCharts input[type='checkbox']").each(function( index ) {
                                        if(index == event.currentTarget._i){
                                            if( $(this).is(':checked') ){
                                                $(this).prop( "checked", false );
                                            }else{
                                                $(this).prop( "checked", true );
                                            }
                                        }
                                    });
                                }
                            }
                        }
                    },

                    series: [
                        {
                            selected: true,
                            name: crealng.capteur1,
                            data: data[0]
                        },
                        {
                            name: crealng.capteur2,
                            data: data[1]
                        },
                        {
                            name: crealng.capteur3,
                            data: data[2]
                        },
                        {
                            selected: true,
                            name: crealng.capteur4,
                            data: data[3]
                        }
                    ],
                    noData: {
                        style: {
                            fontWeight: 'bold',
                            fontSize: '15px',
                            color: '#303030'
                        }
                    },
                    loading: {
                        labelStyle: {
                            color: 'white'
                        },
                        style: {
                            backgroundColor: 'gray'
                        }
                    }
                }, function (chart) {
                    // apply the date pickers
                    setTimeout(function (){
                        if(chart.options != undefined){
                            $('input.highcharts-range-selector', $('#' + chart.options.chart.renderTo)).datepicker()
                        }
                    }, 0);
                    var series = chart.series;
                    if( series[0].checkbox) {
                        series[0].checkbox.style.marginLeft = '-205px';
                    }
                    if( series[1].checkbox) {
                        series[1].checkbox.style.marginLeft = '-150px';
                    }
                    if( series[2].checkbox) {
                        series[2].checkbox.style.marginLeft = '-200px';
                    }
                    if( series[3].checkbox) {
                        series[3].checkbox.style.marginLeft = '-185px';
                    }
                });
                if($("#notstandalone").length){
                    $("#switchLive").html(crealng.access_week);
                    $("#switchAverage").html(crealng.access_year);
                }else{
                }
            }
            // on cache par défaut les temperatures 1 et 2
            window.chart.series[0].show();
            window.chart.series[1].hide();
            window.chart.series[2].hide();
            window.chart.series[3].show();
            // affichage du message nodata si besoin
            if (data[0] || data[1] || data[2] || data[3]) {
                window.chart.hideNoData();
            } else {
                window.chart.showNoData();
            }

            width = $("#diagram").width()-20;

            // cas du responsive où la map est au dessus du formulaire
            if($('#map').height() == 350){
                height = 400;
                iframeHeight = 1000;
            }else{
                height = $('#map').height() - $('#graph #page-title').outerHeight() - $('#graph #creaChartsForm').outerHeight() - $('#graph #switchCharts').outerHeight() - 50;
                iframeHeight = 700;
            }

            window.chart.setSize(width, height, doAnimation = false);
            window.parent.resizeModuleLive(iframeHeight);

            // suppression des boutons d'export
            window.chart.options.exporting.buttons.contextButton.menuItems[0] = null; // print
            window.chart.options.exporting.buttons.contextButton.menuItems[1] = null; // spacer
            window.chart.options.exporting.buttons.contextButton.menuItems[2] = null; // PNG
            window.chart.options.exporting.buttons.contextButton.menuItems[5] = null; // SVG
            window.chart.options.exporting.chartOptions.title.text = 'station n° ' + id_station;
            //window.chart.id_station = id_station;
        });

        // Set the datepicker's date format

        if($("#notstandalone").length) {
            if(crealng.drupal_lng == "fr"){
                $.datepicker.setDefaults({
                    dateFormat: 'dd-mm-yy',
                    onSelect: function (dateText) {
                        this.onchange();
                        this.onblur();
                    }
                });
            }else{
                $.datepicker.setDefaults({
                    dateFormat: 'yy-mm-dd',
                    onSelect: function (dateText) {
                        this.onchange();
                        this.onblur();
                    }
                });
            }
        }
     }

    $(d).ready(function() {
        /**
         * action bouton submit
         */
        $("#creaChartsForm #edit-submit").click( function() {
            if($("#typeGraph").val() == "year"){
                loadCharts("year");
            }else{
                loadCharts("week");
            }

        });

        /**
         * action bouton switch
         */

        $("#switchLive").click( function() {
            if($("#typeGraph").val() != "week"){
                loadCharts("week");
                $(this).addClass('active');
                $("#switchAverage").removeClass('active');
            }

        });
        $("#switchAverage").click( function() {
            if($("#typeGraph").val() != "year"){
                loadCharts("year");
                $(this).addClass('active');
                $("#switchLive").removeClass('active');
            }
        });

        $(window).resize(function() {
            // cas du responsive où la map est au dessus du formulaire
            if($('#map').height() == 350){
                height = 400;
                iframeHeight = 1000;
            }else{
                height = $('#map').height() - $('#graph #page-title').outerHeight() - $('#graph #creaChartsForm').outerHeight() - $('#graph #switchCharts').outerHeight() - 50;
                iframeHeight = 700;
            }
            width = $("#diagram").width() - 20;
            window.chart.setSize(width, height, doAnimation = true);
            window.parent.resizeModuleLive(iframeHeight);
        });

        // recuperation des données au premier passage
        loadCharts($("#typeGraph").val());

    });

})(jQuery, window, document);