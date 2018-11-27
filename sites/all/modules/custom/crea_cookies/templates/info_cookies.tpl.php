<?php
global $base_url;
$info_cookies = $settings['info_cookies'];
$privacy_cookies = $settings['privacy_cookies'];

?>

<div id="cookie_container" class="cookie_container">
  <div class="privacy_wrap">
    <input type="hidden" name="cookieName" id="cookieName" value="CookieCnil">
    <div class="fl">
      <?php echo $info_cookies; ?>
    </div>
    <button id="AutoriseCookie" type="button" class="button-classical fl">
      <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
      <?php print t('Autoriser tous les cookies'); ?>
    </button>

    <button id="showbanParameters" type="button" class="button-classical fl">
      <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
        <?php print t('Paramétrer vos cookies'); ?>
    </button>&nbsp;
    <i id="closeCnil" class="fa fa-close" title="Fermer le bandeau">&nbsp;</i>
  </div>
  <div class="cb"></div>
  <div id="privacy_details" class="privacy_details noindex" style="display: none;">
    <div class="privacy_wrap privacy_wrap_detail">
      <div><?php echo $privacy_cookies; ?></div>
      <div class="parent_details">
        <div>
          <div class="cookie_lastblock">
            <label><?php print t('Analyse du site web'); ?></label>
            <button id="btnActiverAnalyse" class="button-red">
              <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
                <?php print t('Activer'); ?>
            </button>
            <button id="btnDesactiverAnalyse" class="button-classical">
              <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
              <?php print t('Désactiver'); ?>
            </button>
          </div>
        </div>
        <div>
          <div class="cookie_lastblock">
            <label><?php print t('Réseaux sociaux'); ?></label>
            <button id="btnActiverSocialNetwork" class="button-red">
              <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
              <?php print t('Activer'); ?>
            </button>
            <button id="btnDesactiverSocialNetwork" class="button-classical">
              <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
              <?php print t('Désactiver'); ?>
            </button>
          </div>
        </div>
        <div>
          <label>&nbsp;</label>
          <button id="btnSaveParameter" class="button-classical">
            <img alt="" src="<?php echo $base_url . '/' . drupal_get_path('module', 'crea_cookies') . '/images/white-arrow.png'; ?>">
            <?php print t('Enregistrer'); ?>
          </button>
        </div>
      </div>
    </div>
    <div class="cb"></div>
  </div>
</div>
