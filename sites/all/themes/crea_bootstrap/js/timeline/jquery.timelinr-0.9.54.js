/* ----------------------------------
jQuery Timelinr 0.9.54
tested with jQuery v1.6+

Copyright 2011, CSSLab.cl
Free under the MIT license.
http://www.opensource.org/licenses/mit-license.php

instructions: http://www.csslab.cl/2011/08/18/jquery-timelinr/
---------------------------------- */
(function($){
jQuery.fn.timelinr = function(options){
	// default plugin settings
	settings = jQuery.extend({
		orientation: 				'horizontal',		// value: horizontal | vertical, default to horizontal
		containerDiv: 				'#timeline',		// value: any HTML tag or #id, default to #timeline
		datesDiv: 					'#dates',			// value: any HTML tag or #id, default to #dates
		datesSelectedClass: 		'selected',			// value: any class, default to selected
		datesSpeed: 				'normal',			// value: integer between 100 and 1000 (recommended) or 'slow', 'normal' or 'fast'; default to normal
		issuesDiv: 					'#issues',			// value: any HTML tag or #id, default to #issues
		issuesSelectedClass: 		'selected',			// value: any class, default to selected
		issuesSpeed: 				'fast',				// value: integer between 100 and 1000 (recommended) or 'slow', 'normal' or 'fast'; default to fast
		issuesTransparency: 		0.2,				// value: integer between 0 and 1 (recommended), default to 0.2
		issuesTransparencySpeed: 	500,				// value: integer between 100 and 1000 (recommended), default to 500 (normal)
		prevButton: 				'#prev',			// value: any HTML tag or #id, default to #prev
		nextButton: 				'#next',			// value: any HTML tag or #id, default to #next
		arrowKeys: 					'false',			// value: true | false, default to false
		startAt: 					1,					// value: integer, default to 1 (first)
		autoPlay: 					'false',			// value: true | false, default to false
		autoPlayDirection: 			'forward',			// value: forward | backward, default to forward
		autoPlayPause: 				2000				// value: integer (1000 = 1 seg), default to 2000 (2segs)
	}, options);

    this.each(function () {
      // setting variables... many of them
      var container = $(this);
      var containerDiv = '#' + container.attr('id');
      var datesDiv = settings.datesDiv;
      var issuesDiv = settings.issuesDiv;
      var prevButton = settings.prevButton;
      var nextButton = settings.nextButton;

      var howManyDates = $(datesDiv+' li').length;
      var howManyIssues = $(issuesDiv+' li').length;
      var currentDate = $(datesDiv).find('a.'+settings.datesSelectedClass);
      var currentIssue = $(issuesDiv).find('li.'+settings.issuesSelectedClass);
      var widthContainer = $(containerDiv).width();
      var heightContainer = $(containerDiv).height();
      var widthIssues = $(issuesDiv).width();
      var heightIssues = $(issuesDiv).height();
      var widthIssue = $(issuesDiv+' li').width();
      var heightIssue = $(issuesDiv+' li').height();
      var widthDates = $(datesDiv).width();
      var heightDates = $(datesDiv).height();
      var widthDate = $(datesDiv+' li').width();
      var heightDate = $(datesDiv+' li').height();
      // set positions!
      if(settings.orientation == 'horizontal') {
        $(issuesDiv).width(widthIssue*howManyIssues);
        $(datesDiv).width(widthDate*howManyDates).css('marginLeft',widthContainer/2-widthDate/2);
        var defaultPositionDates = parseInt($(datesDiv).css('marginLeft').substring(0,$(datesDiv).css('marginLeft').indexOf('px')));
      } else if(settings.orientation == 'vertical') {
        $(issuesDiv).height(heightIssue*howManyIssues);
        $(datesDiv).height(heightDate*howManyDates).css('marginTop',heightContainer/2-heightDate/2);
        var defaultPositionDates = parseInt($(datesDiv).css('marginTop').substring(0,$(datesDiv).css('marginTop').indexOf('px')));
      }

      $(datesDiv+' a').click(function(event){
        event.preventDefault();
        // first vars
        var whichIssue = $(this).text();
        var currentIndex = $(this).parent().prevAll().length;
        // moving the elements
        if(settings.orientation == 'horizontal') {
          $(issuesDiv).animate({'marginLeft':-widthIssue*currentIndex},{queue:false, duration:settings.issuesSpeed});
        } else if(settings.orientation == 'vertical') {
          $(issuesDiv).animate({'marginTop':-heightIssue*currentIndex},{queue:false, duration:settings.issuesSpeed});
        }
        $(issuesDiv+' li').animate({'opacity':settings.issuesTransparency},{queue:false, duration:settings.issuesSpeed}).removeClass(settings.issuesSelectedClass).eq(currentIndex).addClass(settings.issuesSelectedClass).fadeTo(settings.issuesTransparencySpeed,1);
        // prev/next buttons now disappears on first/last issue | bugfix from 0.9.51: lower than 1 issue hide the arrows | bugfixed: arrows not showing when jumping from first to last date
        if(howManyDates == 1) {
          $(prevButton+','+nextButton).fadeOut('fast');
        } else if(howManyDates == 2) {
          if($(issuesDiv+' li:first-child').hasClass(settings.issuesSelectedClass)) {
            $(prevButton).fadeOut('fast');
            $(nextButton).fadeIn('fast');
          }
          else if($(issuesDiv+' li:last-child').hasClass(settings.issuesSelectedClass)) {
            $(nextButton).fadeOut('fast');
            $(prevButton).fadeIn('fast');
          }
        } else {
          if( $(issuesDiv+' li:first-child').hasClass(settings.issuesSelectedClass) ) {
            $(nextButton).fadeIn('fast');
            $(prevButton).fadeOut('fast');
          }
          else if( $(issuesDiv+' li:last-child').hasClass(settings.issuesSelectedClass) ) {
            $(prevButton).fadeIn('fast');
            $(nextButton).fadeOut('fast');
          }
          else {
            $(nextButton+','+prevButton).fadeIn('slow');
          }
        }
        // now moving the dates
        $(datesDiv+' a').removeClass(settings.datesSelectedClass);
        $(this).addClass(settings.datesSelectedClass);
        if(settings.orientation == 'horizontal') {
          $(datesDiv).animate({'marginLeft':defaultPositionDates-(widthDate*currentIndex)},{queue:false, duration:'settings.datesSpeed'});
        } else if(settings.orientation == 'vertical') {
          $(datesDiv).animate({'marginTop':defaultPositionDates-(heightDate*currentIndex)},{queue:false, duration:'settings.datesSpeed'});
        }
      });

      $(nextButton).bind('click', function(event){
        event.preventDefault();
        // bugixed from 0.9.54: now the dates gets centered when there's too much dates.
        var currentIndex = $(issuesDiv).find('li.'+settings.issuesSelectedClass).index();
        if(settings.orientation == 'horizontal') {
          var currentPositionIssues = parseInt($(issuesDiv).css('marginLeft').substring(0,$(issuesDiv).css('marginLeft').indexOf('px')));
          var currentIssueIndex = currentPositionIssues/widthIssue;
          var currentPositionDates = parseInt($(datesDiv).css('marginLeft').substring(0,$(datesDiv).css('marginLeft').indexOf('px')));
          var currentIssueDate = currentPositionDates-widthDate;
          if(currentPositionIssues <= -(widthIssue*howManyIssues-(widthIssue))) {
            $(issuesDiv).stop();
            $(datesDiv+' li:last-child a').click();
          } else {
            if (!$(issuesDiv).is(':animated')) {
              // bugixed from 0.9.52: now the dates gets centered when there's too much dates.
              $(datesDiv+' li').eq(currentIndex+1).find('a').trigger('click');
            }
          }
        } else if(settings.orientation == 'vertical') {
          var currentPositionIssues = parseInt($(issuesDiv).css('marginTop').substring(0,$(issuesDiv).css('marginTop').indexOf('px')));
          var currentIssueIndex = currentPositionIssues/heightIssue;
          var currentPositionDates = parseInt($(datesDiv).css('marginTop').substring(0,$(datesDiv).css('marginTop').indexOf('px')));
          var currentIssueDate = currentPositionDates-heightDate;
          if(currentPositionIssues <= -(heightIssue*howManyIssues-(heightIssue))) {
            $(issuesDiv).stop();
            $(datesDiv+' li:last-child a').click();
          } else {
            if (!$(issuesDiv).is(':animated')) {
              // bugixed from 0.9.54: now the dates gets centered when there's too much dates.
              $(datesDiv+' li').eq(currentIndex+1).find('a').trigger('click');
            }
          }
        }
        // prev/next buttons now disappears on first/last issue | bugfix from 0.9.51: lower than 1 issue hide the arrows
        if(howManyDates == 1) {
          $(prevButton+','+nextButton).fadeOut('fast');
        } else if(howManyDates == 2) {
          if($(issuesDiv+' li:first-child').hasClass(settings.issuesSelectedClass)) {
            $(prevButton).fadeOut('fast');
            $(nextButton).fadeIn('fast');
          }
          else if($(issuesDiv+' li:last-child').hasClass(settings.issuesSelectedClass)) {
            $(nextButton).fadeOut('fast');
            $(prevButton).fadeIn('fast');
          }
        } else {
          if( $(issuesDiv+' li:first-child').hasClass(settings.issuesSelectedClass) ) {
            $(prevButton).fadeOut('fast');
          }
          else if( $(issuesDiv+' li:last-child').hasClass(settings.issuesSelectedClass) ) {
            $(nextButton).fadeOut('fast');
          }
          else {
            $(nextButton+','+prevButton).fadeIn('slow');
          }
        }
      });

      $(prevButton).click(function(event){
        event.preventDefault();
        // bugixed from 0.9.54: now the dates gets centered when there's too much dates.
        var currentIndex = $(issuesDiv).find('li.'+settings.issuesSelectedClass).index();
        if(settings.orientation == 'horizontal') {
          var currentPositionIssues = parseInt($(issuesDiv).css('marginLeft').substring(0,$(issuesDiv).css('marginLeft').indexOf('px')));
          var currentIssueIndex = currentPositionIssues/widthIssue;
          var currentPositionDates = parseInt($(datesDiv).css('marginLeft').substring(0,$(datesDiv).css('marginLeft').indexOf('px')));
          var currentIssueDate = currentPositionDates+widthDate;
          if(currentPositionIssues >= 0) {
            $(issuesDiv).stop();
            $(datesDiv+' li:first-child a').click();
          } else {
            if (!$(issuesDiv).is(':animated')) {
              // bugixed from 0.9.54: now the dates gets centered when there's too much dates.
              $(datesDiv+' li').eq(currentIndex-1).find('a').trigger('click');
            }
          }
        } else if(settings.orientation == 'vertical') {
          var currentPositionIssues = parseInt($(issuesDiv).css('marginTop').substring(0,$(issuesDiv).css('marginTop').indexOf('px')));
          var currentIssueIndex = currentPositionIssues/heightIssue;
          var currentPositionDates = parseInt($(datesDiv).css('marginTop').substring(0,$(datesDiv).css('marginTop').indexOf('px')));
          var currentIssueDate = currentPositionDates+heightDate;
          if(currentPositionIssues >= 0) {
            $(issuesDiv).stop();
            $(datesDiv+' li:first-child a').click();
          } else {
            if (!$(issuesDiv).is(':animated')) {
              // bugixed from 0.9.54: now the dates gets centered when there's too much dates.
              $(datesDiv+' li').eq(currentIndex-1).find('a').trigger('click');
            }
          }
        }
        // prev/next buttons now disappears on first/last issue | bugfix from 0.9.51: lower than 1 issue hide the arrows
        if(howManyDates == 1) {
          $(prevButton+','+nextButton).fadeOut('fast');
        } else if(howManyDates == 2) {
          if($(issuesDiv+' li:first-child').hasClass(settings.issuesSelectedClass)) {
            $(prevButton).fadeOut('fast');
            $(nextButton).fadeIn('fast');
          }
          else if($(issuesDiv+' li:last-child').hasClass(settings.issuesSelectedClass)) {
            $(nextButton).fadeOut('fast');
            $(prevButton).fadeIn('fast');
          }
        } else {
          if( $(issuesDiv+' li:first-child').hasClass(settings.issuesSelectedClass) ) {
            $(prevButton).fadeOut('fast');
          }
          else if( $(issuesDiv+' li:last-child').hasClass(settings.issuesSelectedClass) ) {
            $(nextButton).fadeOut('fast');
          }
          else {
            $(nextButton+','+prevButton).fadeIn('slow');
          }
        }
      });
      // keyboard navigation, added since 0.9.1
      if(settings.arrowKeys=='true') {
        if(settings.orientation=='horizontal') {
          $(document).keydown(function(event){
            if (event.keyCode == 39) {
              $(nextButton).click();
            }
            if (event.keyCode == 37) {
              $(prevButton).click();
            }
          });
        } else if(settings.orientation=='vertical') {
          $(document).keydown(function(event){
            if (event.keyCode == 40) {
              $(nextButton).click();
            }
            if (event.keyCode == 38) {
              $(prevButton).click();
            }
          });
        }
      }
      // default position startAt, added since 0.9.3
      $(datesDiv+' li').eq(settings.startAt-1).find('a').trigger('click');
      // autoPlay, added since 0.9.4
      if(settings.autoPlay == 'true') {
        setInterval("autoPlay()", settings.autoPlayPause);
      }
    });
};

// autoPlay, added since 0.9.4
function autoPlay(){
	var currentDate = $(datesDiv).find('a.'+settings.datesSelectedClass);
	if(settings.autoPlayDirection == 'forward') {
		if(currentDate.parent().is('li:last-child')) {
			$(datesDiv+' li:first-child').find('a').trigger('click');
		} else {
			currentDate.parent().next().find('a').trigger('click');
		}
	} else if(settings.autoPlayDirection == 'backward') {
		if(currentDate.parent().is('li:first-child')) {
			$(datesDiv+' li:last-child').find('a').trigger('click');
		} else {
			currentDate.parent().prev().find('a').trigger('click');
		}
	}
}
})(jQuery);