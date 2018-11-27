<?php if (isset($articles) && !empty($articles)): ?>
  <div id="article-carousel" class="carousel slide" data-ride="carousel">
    <div class="carousel-inner" role="listbox">
      <?php $count_article = 0; ?>
      <?php foreach ($articles AS $article): ?>
        <?php if ($count_article == 0) $item_classes = 'row item active'; else $item_classes = 'row item'; ?>
        <div class="<?php print $item_classes; ?>">
          <div class="col col-md-4 article">
            <h2><a href="<?php print $article['know_more']; ?>" target="_blank"><?php print $article['title']; ?></a></h2>
            <div class="date">> Date <?php print $article['date']; ?></div>
            <div class="description">
              <?php print $article['content']; ?>
            </div>
            <div class="know_more">
              <a href="<?php print $article['know_more']; ?>" target="_blank">En savoir +</a>
            </div>
          </div>
          <div class="col col-md-8 photo">
            <a href="<?php print $article['know_more']; ?>" target="_blank"><img src="<?php print $article['image_src']; ?>" alt="<?php print $article['image_alt']; ?>" title="<?php print $article['image_title']; ?>" /></a>
              <a class="left carousel-control" href="#article-carousel" role="button" data-slide="prev">
                  <span class="fa fa-chevron-left" aria-hidden="true"></span>
                  <span class="sr-only">Previous</span>
              </a>
              <a class="right carousel-control" href="#article-carousel" role="button" data-slide="next">
                  <span class="fa fa-chevron-right" aria-hidden="true"></span>
                  <span class="sr-only">Next</span>
              </a>
          </div>
        </div>
        <?php $count_article ++; ?>
      <?php endforeach; ?>
    </div>
  </div>
<?php endif; ?>