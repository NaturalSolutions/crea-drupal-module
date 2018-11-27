<?php

// Suppréssion du cache
drupal_flush_all_caches();

// Action des modules
$enable_dependencies = TRUE;
module_enable(array('crea_design'), $enable_dependencies);

db_update('block')
->fields(array('region' => 'content', 'pages' => '<front>' , 'title' => '<none>','status' => '1'))
->condition('theme', 'crea', '=')
->condition('delta', 'crea_slideshow', '=')
->condition('module', 'crea_design', '=')
->execute();

db_update('block')
->fields(array('region' => 'header_sub', 'title' => '<none>','status' => '1'))
->condition('theme', 'crea', '=')
->condition('delta', 'crea_social', '=')
->condition('module', 'crea_design', '=')
->execute();

$blockSocial = '<ul><li><a href="https://fr-fr.facebook.com/creamontblanc" ><i class="fi-social-facebook"></i></a></li><li><a href="https://twitter.com/creamontblanc" ><i class="fi-social-twitter"></i></a></li><li><a href="https://www.youtube.com/user/creamontblanc1" ><i class="fi-social-youtube"></i></a></li><li><a href="mailto:contact@crea.fr" ><i class="fi-mail"></i></a></li></ul>';

variable_set('crea_block_social', $blockSocial);

//throw new DrupalUpdateException();