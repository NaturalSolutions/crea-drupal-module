(function($) {
    Drupal.behaviors.phenoclim_design = {
      attach: function (context, settings) {
        var self = this;
        this.myData = [];
        this.dfd = [];
        var urlwp = settings.phenoclim_design.url
        if(settings.phenoclim_design.feed && settings.phenoclim_design.feed.length > 0) {
            settings.phenoclim_design.feed.forEach(feed => {
            if(feed.featured_media) {
                self.dfd.push($.ajax({
                    url: urlwp + 'media/' + feed.featured_media,
                    type: 'get',
                    dataType: 'json',
                    success: function (data) {
                        if ( data ) {
                            self.myData.push(data);
                        }
                    }
                }));
            }
 
            });
            $.when.apply($, self.dfd).then(function() {
                var data = self.myData;
                $('#article-carousel', context).bind('slid.bs.carousel', function (e) {
                    var $id = $('#article-carousel .active').attr('id');
                    var current = data.find( function(x) {
                        return x.post === Number($id);
                    });
                    $('#article-carousel .active img', context).attr('src', current.source_url);
                    $('#article-carousel .active img', context).attr('alt', current.alt_text);
                    $('#article-carousel .active img', context).attr('alt', current.title.rendered);

                    $('#article-carousel .active #carousel_spinner').fadeOut(800);

                    var done = true;
                    $("#article-carousel img", context).each(function() {
                    var element = $(this);
                    if (element.attr('src') == "") {
                        done = false;
                    }
                    });

                    if(done)
                        $('#article-carousel', context).unbind('slid.bs.carousel');
                });

            })
        }
      }
    };
    })(jQuery);