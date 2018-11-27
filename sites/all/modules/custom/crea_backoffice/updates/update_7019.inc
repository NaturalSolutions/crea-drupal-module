<?php 
// installation de domain_xmlsitemap
module_enable(array('domain_xmlsitemap'));

// suppression des xmlsitemap existants
db_query("TRUNCATE TABLE xmlsitemap_sitemap");
// creation des xmlsitemap
$sitemap = new stdClass();
$sitemap->context = array();
$sitemap->context['domain'] = '1';
$sitemap->context['language'] = "en";
xmlsitemap_sitemap_save($sitemap);

$sitemap = new stdClass();
$sitemap->context = array();
$sitemap->context['domain'] = '1';
$sitemap->context['language'] = "fr";
xmlsitemap_sitemap_save($sitemap);

$sitemap = new stdClass();
$sitemap->context = array();
$sitemap->context['domain'] = '2';
$sitemap->context['language'] = "en";
xmlsitemap_sitemap_save($sitemap);

$sitemap = new stdClass();
$sitemap->context = array();
$sitemap->context['domain'] = '2';
$sitemap->context['language'] = "fr";
xmlsitemap_sitemap_save($sitemap);

// on inclut les pages dans le sitemap
$page = array();
$page['status'] = '1';
$page['priority'] = '0.5';
variable_set('xmlsitemap_settings_node_page', $page);
$lifetime = '86400'; // 1 an
variable_set('xmlsitemap_minimum_lifetime', $lifetime);

// activation de google analytics
module_enable(array('googleanalytics'));

// activation de scald video et scald_dailymotion
module_enable(array('scald_video'));
module_enable(array('scald_dailymotion'));
module_enable(array('scald_vimeo'));
module_enable(array('scald_youtube'));

//throw new DrupalUpdateException();