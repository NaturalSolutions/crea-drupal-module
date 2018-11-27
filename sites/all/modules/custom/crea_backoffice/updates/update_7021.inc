<?php

$page_menu = array(
  'main-menu' => 'main-menu',
  'devel' => 0,
  'menu-footer' => 0,
  'management' => 0,
  'navigation' => 0,
  'user-menu' => 0
);
variable_set('menu_options_news', $page_menu);
$domain_conf = domain_conf_variable_get(1, 'menu_options_news');
$domain_conf['main-menu'] = 'main-menu';
domain_conf_variable_set(1, 'menu_options_news', $domain_conf);

$domain_conf = domain_conf_variable_get(2, 'menu_options_news');
$domain_conf['main-menu'] = 'main-menu';
domain_conf_variable_set(2, 'menu_options_news', $domain_conf);