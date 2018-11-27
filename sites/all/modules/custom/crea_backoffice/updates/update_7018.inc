<?php 
// installation de addthis
module_enable(array('addthis', 'addthis_displays'));

variable_set('addthis_bookmark_url', '//www.addthis.com/bookmark.php?v=300');
variable_set('addthis_services_css_url', '//cache.addthiscdn.com/icons/v1/sprites/services.css');
variable_set('addthis_services_json_url', '//cache.addthiscdn.com/services/v1/sharing.en.json');
variable_set('addthis_widget_js_url', '//s7.addthis.com/js/300/addthis_widget.js');
variable_set('addthis_custom_configuration_code_enabled', 0);
variable_set('addthis_custom_configuration_code', 'var addthis_config = {}');
variable_set('addthis_widget_load_domready', 1);
variable_set('addthis_widget_load_async', 0);
variable_set('addthis_widget_include', '1');
variable_set('addthis_co_brand', '');
variable_set('addthis_ui_header_color', '');
variable_set('addthis_ui_header_background_color', '');
variable_set('addthis_click_to_open_compact_menu_enabled', 0);
variable_set('addthis_open_windows_enabled', 0);
variable_set('addthis_ui_delay', '0');
variable_set('addthis_enabled_services', array());
variable_set('addthis_standard_css_enabled', 1);
variable_set('addthis_508_compliant', 0);
variable_set('addthis_addressbook_enabled', 0);
variable_set('addthis_excluded_services', array());
variable_set('addthis_profile_id', 'ra-5638c717be0d98bd');
variable_set('addthis_clickback_tracking_enabled', 1);
variable_set('addthis_facebook_like_count_support_enabled', 1);
variable_set('addthis_google_analytics_tracking_enabled', false);
variable_set('addthis_google_analytics_social_tracking_enabled', false);
variable_set('addthis_twitter_via', 'AddThis');
variable_set('addthis_twitter_template', '{{title}} {{url}} via @ATLASMontBlanc');

$manager_permissions = array(
	'administer addthis' => true,
	'administer advanced addthis' => true
);

user_role_change_permissions(5, $manager_permissions);