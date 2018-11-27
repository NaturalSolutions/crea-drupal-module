<?php if(isset($articles)
&& !empty($articles)): ?>
<div class="content">
  <ul class="odd">
    <?php $count_article = 0; ?>
    <?php foreach ($articles AS $article): ?>
      <?php if ($count_article%2 == 0) $item_class = "odd"; else $item_class = "even"; ?>
      <li class="<?php print $item_class; ?>">
          <?php print $article; ?>
      </li>
      <?php $count_article++ ; ?>
    <?php endforeach; ?>
  </ul>
</div>
<?php endif; ?>