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
            $.when(self.dfd).done(function() {
                var data = self.myData;
                var count = 0;
                $('#article-carousel').bind('slid.bs.carousel', function (e) {
                    var $id = $('#article-carousel .active').attr('id');
                    var current = data.find( function(x) {
                        return x.post === Number($id);
                    });
                    if(current)
                        count=+1;
                    $('#article-carousel .active img').attr('src', current.source_url);
                    $('#article-carousel .active img').attr('alt', current.alt_text);
                    $('#article-carousel .active img').attr('alt', current.title.rendered);
                });
                if(count == data.length)
                    $('#article-carousel').unbind('slid.bs.carousel');
            })
        }
        //code ends
      }
    };
    })(jQuery);