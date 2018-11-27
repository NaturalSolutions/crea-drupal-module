jQuery(function($) {
	var hash = $(location).attr('hash').replace(/^#/, "");

	$('.side-page a').each(function(){
		var link_anchor = $(this).attr('href');
		
		$('.l-main .tab-medias .orbit-timer').click();
		
		$('a[href="' + link_anchor + '"').on('click', function(){
			$('.l-main .tab-medias').addClass('element-invisible');
			$('.side-page a').removeClass('active');
			$('.l-main .tab-medias .orbit-timer').click();
			
	    	if ($(link_anchor).hasClass('element-invisible')){
	    		$(link_anchor).removeClass('element-invisible');
	    	}
	    	else{
	    		$(link_anchor).toggle();
	    	}
	    	
	    	if ($(link_anchor + ':hidden').is(':hidden')){
	    		$(link_anchor + ' .orbit-timer').click();
	    		$(this).removeClass('active');
	    		window.location.hash = '';
	    		$(location).attr('hash').replace(/^#/, "");
	    		return false;
	    	}
	    	else{
		    	$('html,body').animate({
			    	scrollTop: $(link_anchor).offset().top -10
			    }, 'fast', function(){
			    	$(link_anchor + ' .orbit-timer.paused').click();
			    	
			    	$(document).foundation();
			    	$(document).foundation('orbit', 'reflow');
			    });
		    	
		    	$(this).addClass('active');
	    	}
	    });
	});
    
    // on cache le titre si on est sur la HP
    if(jQuery.trim( jQuery('.l-header-sub-region').html() ).length !== 0){
        $("#page-title").hide();
    }
    
    if ($('.l-main .side-page').length){
		$('.l-main .side-page').css('top', $('#page-title').offset().top);
	}
    
    $(window).resize(function() {
    	if ($('.l-main .side-page').length && $(window).scrollTop() > $('#page-title').offset().top){
    		$('.l-main .side-page').css('top', '5%');
    	}
    	else{
    		$('.l-main .side-page').css('top', $('#page-title').offset().top);
    	}
    });
    $(window).scroll(function() {
    	if ($('.l-main .side-page').length && $(window).scrollTop() > $('#page-title').offset().top){
    		$('.l-main .side-page').css('top', '5%');
    	}
    	else{
    		if(jQuery.trim( jQuery('.l-header-sub-region').html() ).length !== 0){
    			$('.l-main .side-page').css('top', '5%');
    		}
    		else{
    			$('.l-main .side-page').css('top', $('#page-title').offset().top);
    		}
    	}
    });
    
    $(document).ready(function() {
    	$(document).foundation();
    	
	    if (hash !== '' && $('#' + hash).length){
	    	$('#' + hash).removeClass('element-invisible');
	    	$('html,body').animate({
		    	scrollTop: $('#' + hash).offset().top -10
		    }, 'fast', function(){
		    	$('#' + hash + ' .orbit-timer.paused').click();
		    });
	    	$('a[href="#' + hash + '"').addClass('active');
	    }
    });
});