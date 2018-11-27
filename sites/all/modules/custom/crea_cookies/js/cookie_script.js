(function($, w, d){
  Drupal.behaviors.Cookies = {
    attach: function(context, settings) {
      // gestion des cookies
      tagAnalyticsCNIL.cookie_text = Drupal.settings.cookie_text;
      tagAnalyticsCNIL.cookie_accept_text = Drupal.settings.cookie_accept;
      tagAnalyticsCNIL.cookie_refuse_text = Drupal.settings.cookie_refuse;
      tagAnalyticsCNIL.CookieConsent.start();
    }
  }
})(jQuery, window, document);