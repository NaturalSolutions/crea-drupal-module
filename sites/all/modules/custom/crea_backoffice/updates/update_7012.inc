<?php 

module_enable(array('domain', 'domain_conf', 'domain_settings', 'domain_path'));

$managers_permissions = array(
	'publish from assigned domain' => TRUE,
	'publish from default domain' => TRUE,
	'publish to any assigned domain' => TRUE,
	'set domain access' => TRUE,
);

user_role_change_permissions(5, $managers_permissions);