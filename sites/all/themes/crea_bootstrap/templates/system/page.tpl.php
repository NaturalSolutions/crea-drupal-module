<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup templates
 */
?>
<?php
// si on est sur changement climatique on affiche pas le menu
$type_page = '';
if(isset($variables['node']->field_type_page['und'][0]['value'])){
    $type_page = $variables['node']->field_type_page['und'][0]['value'];
}
?>
<?php if (!empty($page['sur_header'])): ?>
<header id="topbar" role="banner" class="container-fluid">
  <div class="container main-container">
    <?php print render($page['sur_header']); ?>
  </div>
</header>
<?php endif; ?>

<?php if (!empty($page['header'])): ?>
<header id="header" role="banner" class="container main-container <?php echo $type_page; ?>">
  <div class="col col-md-6 col-sm-12 col-xs-12">
  <?php if ($logo): ?>
      <?php if($type_page == 'changement_climatique'){
          $logo = '/'.drupal_get_path('theme', 'crea_bootstrap') . '/logo-climato.png';
      }
      ?>
    <a class="logo navbar-btn pull-left <?php echo $type_page; ?>" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
      <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
    </a>
  <?php endif; ?>
    <?php
    if($type_page != 'changement_climatique') {
        $site_slogan = 'Centre de Recherches<br/>sur les Écosystèmes d\'Altitude';
        global $language;
        if ($language->language != 'fr') {
            $site_slogan = 'Research Center<br/>for Alpine Ecosystems';
        }
    }else {
        $site_slogan = '10 minutes pour comprendre';
        global $language;
        if ($language->language != 'fr') {
            $site_slogan = '10 minutes to understand';
        }
    }
    ?>
    <a class="name navbar-brand <?php echo $type_page; ?>" href="<?php print $front_page; ?>" title="<?php print t($site_slogan, array(), array('context' => 'domain')); ?>"><?php print t($site_slogan, array(), array('context' => 'domain')); ?></a>
  </div>

  <div class="col col-md-4 col-md-offset-2 right-column col-sm-12 col-xs-12">
      <?php if($type_page == 'changement_climatique') { ?>
      <div class="region region-header">
          <section id="block-block-10" class="block block-block clearfix">
              <p class="rteright"><a href="/"><img alt="aller au site CREA Mont Blanc" src="/sites/all/themes/crea_bootstrap/logo.png" style="height: 80px;"></a></p>
          </section>
      </div>
      <?php }else{ ?>
          <?php print render($page['header']); ?>
     <?php } ?>
  </div>
</header>
<?php endif; ?>

<?php if (!empty($page['navigation'])): ?>
<header id="navbar" role="banner" class="container main-container">
  <nav class="navbar">
    <?php print render($page['navigation']); ?>
  </nav>
</header>
<?php endif; ?>

<div class="main-container <?php print $container_class; ?> <?php print $type_page; ?>">
  <?php if (!empty($page['sur_content'])): ?>
    <div class="row sur_content">
      <div role="complementary">
        <?php print render($page['sur_content']); ?>
      </div>
    </div>
    <?php endif; ?>

  <section>
    <?php if (!drupal_is_front_page()): ?>
      <?php if (!empty($breadcrumb)): ?>

        <div class="container">
            <?php if($type_page != 'changement_climatique'){ ?>
          <?php print $breadcrumb; ?>
            <?php } ?>
        </div>

      <?php endif;?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <h1 class="page-header container"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
    <?php endif; ?>

    <?php print $messages; ?>
    <?php if (!empty($tabs)): ?>
      <div class="tabs-container container">
        <?php print render($tabs); ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($page['help'])): ?>
      <?php print render($page['help']); ?>
    <?php endif; ?>
    <?php if (!empty($action_links)): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>

    <?php
    if (drupal_is_front_page()
    && isset($page['content']['system_main'])){
      unset($page['content']['system_main']);
    }
    ?>

    <?php print render($page['content']); ?>
  </section>

  <?php if (!empty($page['sub_content'])): ?>
    <div class="sub_content container-fluid">
      <div role="complementary" class="container">
        <?php print render($page['sub_content']); ?>
      </div>
    </div>
    <?php endif; ?>
</div>

<?php if (!empty($page['footer'])): ?>
<footer id="footer" class="container-fluid">
  <div class="container main-container">
	 <?php print render($page['footer']); ?>
  </div>
</footer>
<?php endif; ?>

<?php if (!empty($page['sub_footer'])): ?>
<footer id="sub-footer" class="container-fluid">
  <div class="container main-container">
    <?php print render($page['sub_footer']); ?>
  </div>
</footer>
<?php endif; ?>
