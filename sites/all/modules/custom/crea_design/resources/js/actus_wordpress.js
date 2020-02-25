(function($) {
    Drupal.behaviors.crea_design = {
      attach: function (context, settings) {
        var self = this;
        this.myData = [];
        this.dfd = [];
        var urlwp = settings.crea_design.url
        if(settings.crea_design.feed && settings.crea_design.feed.length > 0) {
            settings.crea_design.feed.forEach(feed => {
            if(feed.featured_media) {
                self.dfd.push($.ajax({
                    url: urlwp + 'media/' + feed.featured_media,
                    type: 'get',
                    dataType: 'json',
                    success: function (data) {
                        data['feed_id'] = feed.id;
                        if ( data ) {
                            self.myData.push(data);
                        }
                    }
                }));
            }

            });
            $.when.apply($, self.dfd).then(function() {
                var data = self.myData;
                $('.domain-crea #article-carousel', context).bind('slid.bs.carousel', function (e) {
                    var $id = $('#article-carousel .active').attr('id');
                    var current = data.find( function(x) {
                        return x.post === Number($id) || x.feed_id === Number($id);
                    });

                    if(current) {
                        $('.domain-crea #article-carousel .active img', context).attr('src', current.source_url);
                        $('.domain-crea #article-carousel .active img', context).attr('alt', current.alt_text);
                        $('.domain-crea #article-carousel .active img', context).attr('alt', current.title.rendered);
                    }

                    $('.domain-crea #article-carousel .active #carousel_spinner').fadeOut(800);

                    var done = true;
                    $(".domain-crea #article-carousel img", context).each(function() {
                        var element = $(this);
                        if (element.attr('src') == "") {
                            done = false;
                        }
                    });

                    if(done)
                        $('.domain-crea #article-carousel', context).unbind('slid.bs.carousel');
                });

            })
        }
      }
    };
    })(jQuery);