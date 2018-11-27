<div class="col col-md-6 col-sm-12">
	<?php 
	//creaDump::debug($form);
	print render($form['account']['first_name']);
	print render($form['account']['last_name']);
	print render($form['account']['name']);
	print render($form['account']['mail']);
	print render($form['account']['pass']);
	?>
</div>
<div class="col col-md-6 col-sm-12">
	<?php 
	print render($form['account']['postal_code']);
	print render($form['account']['city']);
	print render($form['account']['organism']);
	print render($form['account']['user_type']);
	print render($form['account']['crea_member']);
	print render($form['account']['receive_newsletter']);
	?>
</div>
<div class="col col-md-12 col-sm-12">
    <?php
    if (isset($form['captcha'])){
      print render($form['captcha']);
    }
    print render($form['actions']['submit']);
    ?>
</div>
<?php print drupal_render_children($form); ?>