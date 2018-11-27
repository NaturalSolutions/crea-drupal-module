<div id="twitter_update_list" class="widget-twitter">
	<div class="block-title">
		<h2>
			<span class="icon tweet"> </span>
			<span class="title">tweets</span>
		</h2>
		<a href="http://twitter.com/<?php print $settings['widget_twitter_username']; ?>" class="twitter-link hidden-xs" title="<?php echo t('Follow us on Twitter', array(), array('context' => 'CREA_LNG'));?> →"><?php echo t('Follow us on Twitter', array(), array('context' => 'CREA_LNG'));?> →</a>
	</div>
	<ul>
	 <?php foreach ((array)$tweets as $item) {?>
		 <li>
			 <div class="row">
				<?php if(isset($item->user->profile_image_url) && $item->user->profile_image_url):?>
				<div class="avata col col-md-2"><img src="<?php print $item->user->profile_image_url; ?>" alt="avata" /></div>
				<?php endif; ?>
				<div class="description col col-md-10">
          <?php if (isset($item->user->screen_name)): ?>
            <span><a href="https://twitter.com/<?php print $item->user->screen_name; ?>" title="" target="_blank"><?php print '@'. (isset($item->user->name) ?$item->user->name : '') ; ?>: </a></span>
          <?php else: ?>
            <span><?php print '@'. (isset($item->user->name) ?$item->user->name : '') ; ?>: </span>
          <?php endif; ?>

					<div><?php echo (isset($item->text) ? check_markup($item->text, 'full_html') : ''); ?></div>
					<div class="date">
						<span><?php print (isset($item->created_at) ? getAgo(strtotime($item->created_at)):''); ?> </span>
					</div>
				</div>
			 </div>
		 </li>
	 <?php } ?>
	</ul>
</div>
  