<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div id="questionsReponses" class="articles carousel slide" data-ride="carousel">
  <div class="carousel-inner" role="listbox">
    <?php foreach ($rows as $id => $row): ?>
      <?php if (preg_match('@views-row-first@', $classes_array[$id])) $classes_array[$id] .= ' active'; ?>
      <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
        <?php print $row; ?>
      </div>
    <?php endforeach; ?>
  </div>
</div>
<?php if (count($rows) > 1): ?>
  <div class="pager">
    <a href="#questionsReponses" class="left carousel-control" role="button" data-slide="prev">
      <span class="glyphicon glyphicon-triangle-left" aria-hidden="true"></span>
      <span class="sr-only">Previous</span>
    </a>
    <a href="#questionsReponses" class="right carousel-control" role="button" data-slide="next">
      <span class="glyphicon glyphicon-triangle-right" aria-hidden="true"></span>
      <span class="sr-only">Next</span>
    </a>
  </div>
<?php endif; ?>

