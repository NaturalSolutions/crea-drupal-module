<!--.page -->
<div role="document" class="page">

  <!--.l-header -->
  <header role="banner" class="l-header">

      <!--.l-header-region -->
      <section class="l-header-region row">
        <div class="columns medium-3 small-12">
          <div class="logo-wrapper">
            <?php if ($linked_logo): print $linked_logo; endif; ?>
          </div>
        </div>
        <?php if (!empty($page['header'])): ?>
          <div class="columns medium-9">
	      	<section class="block block-locale contextual-links-region block-top-links header">
	      	<?php
	            global $user;
	            if($user->uid): ?>
	          	<div class="profile">
	          		<?php 
	          		print l(_(t('Make a Fauna / Flora observation')), 'fauna_flora_protocol_interface');
	          		?>
	          	</div>
	          	<div class="profile">
	          		<?php 
	          		print l(_(t('View my observations')), 'user/' . $user->uid .'/fauna_flora_synthesis');
	          		?>
	          	</div>
	          	<div class="logout">
	          		<?php 
	          		print l(_(t('Logout')), 'user/logout');
	          		?>
	          	</div>
	          	<?php endif; ?>
	          	<section class="block block-locale contextual-links-region block-locale-language header">
		          	<ul class="language-switcher-locale-url">
		          		<li class="en first"><a xml:lang="en" class="language-link" href="/en">En</a></li>
						<li class="fr last active"><a xml:lang="fr" class="language-link active" href="/fr">Fr</a></li>
					</ul>
				</section>
				<div class="clear"></div>
	      	
	      	</section>
	      	<div class="social-search">
          		<?php print render($page['header']); ?>
          	</div>
          </div>
        <?php endif; ?>
      </section>
      <!--/.l-header-region -->
      
      <?php if ($top_bar): ?>
      <!--.top-bar -->
      <?php if ($top_bar_classes): ?>
        <div class="<?php print $top_bar_classes; ?>">
      <?php endif; ?>
      <nav class="top-bar row" data-topbar <?php print $top_bar_options; ?>>
        <ul class="title-area">
          <li class="name"></li>
          <li class="toggle-topbar menu-icon">
            <a href="#"><span><?php print $top_bar_menu_text; ?></span></a></li>
        </ul>
        <section class="top-bar-section">
          <?php if ($top_bar_main_menu) : ?>
            <?php print $top_bar_main_menu; ?>
          <?php endif; ?>
          <?php if ($top_bar_secondary_menu) : ?>
            <?php print $top_bar_secondary_menu; ?>
          <?php endif; ?>
        </section>
      </nav>
      <?php if ($top_bar_classes): ?>
        </div>
      <?php endif; ?>
      <!--/.top-bar -->
    <?php endif; ?>    

    <!-- Title, slogan and menu -->
    <?php if ($alt_header): ?>
      <section class="row <?php print $alt_header_classes; ?>">

        <?php if ($linked_logo): print $linked_logo; endif; ?>

        <?php if ($site_name): ?>
          <?php if ($title): ?>
            <div id="site-name" class="element-invisible">
              <strong>
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </strong>
            </div>
          <?php else: /* Use h1 when the content title is empty */ ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if ($site_slogan): ?>
          <h2 title="<?php print $site_slogan; ?>" class="site-slogan"><?php print $site_slogan; ?></h2>
        <?php endif; ?>

        <?php if ($alt_main_menu): ?>
          <nav id="main-menu" class="navigation" role="navigation">
            <?php print ($alt_main_menu); ?>
          </nav> <!-- /#main-menu -->
        <?php endif; ?>

        <?php if ($alt_secondary_menu): ?>
          <nav id="secondary-menu" class="navigation" role="navigation">
            <?php print $alt_secondary_menu; ?>
          </nav> <!-- /#secondary-menu -->
        <?php endif; ?>

      </section>
    <?php endif; ?>
    <!-- End title, slogan and menu -->

  </header>
  <!--/.l-header -->
  
  <!--.l-header-sub-region -->
  <section class="l-header-sub-region">
    <?php if (!empty($page['header_sub'])): ?>
    <div class="medium-12">
      <?php print render($page['header_sub']); ?>
    </div>
    <?php endif; ?>
  </section>
  <!--/.l-header-sub-region -->
  
  <!--.l-content -->
  <div class="l-content row">
    <?php if ($messages && !$zurb_foundation_messages_modal): ?>
      <!--.l-messages -->
      <section class="l-messages row">
        <div class="columns">
          <?php if ($messages): print $messages; endif; ?>
        </div>
      </section>
      <!--/.l-messages -->
    <?php endif; ?>

    <?php if (!empty($page['help'])): ?>
      <!--.l-help -->
      <section class="l-help row">
        <div class="columns">
          <?php print render($page['help']); ?>
        </div>
      </section>
      <!--/.l-help -->
    <?php endif; ?>

    <!--.l-main -->
    <main role="main" class="row l-main">
      <!-- .l-main region -->
      <div class="<?php print $main_grid; ?> main">

        <a id="main-content"></a>

        <?php if ($breadcrumb): print $breadcrumb; endif; ?>

        <?php if ($title): ?>
          <?php print render($title_prefix); ?>
          <h1 id="page-title" class="title"><?php print $title; ?></h1>
          <?php print render($title_suffix); ?>
        <?php endif; ?>

        <?php if (!empty($tabs)): ?>
          <?php print render($tabs); ?>
          <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
        <?php endif; ?>

        <?php if ($action_links): ?>
          <ul class="action-links">
            <?php print render($action_links); ?>
          </ul>
        <?php endif; ?>

        <?php print render($page['content']); ?>
      </div>
      <!--/.l-main region -->
    </main>
    <!--/.l-main -->

  </div>
  <!--/.l-content -->

  <!--.l-footer -->
  <footer class="l-footer panel" role="contentinfo">
    <?php if (!empty($page['footer'])): ?>
      <div class="footer columns">
        <?php print render($page['footer']); ?>
      </div>
    <?php endif; ?>

  </footer>
  <!--/.l-footer -->

  <?php if ($messages && $zurb_foundation_messages_modal): print $messages; endif; ?>
</div>
<!--/.page -->