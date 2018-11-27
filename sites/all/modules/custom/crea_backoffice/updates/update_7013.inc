<?php 
// activation du module d'import protocole CSV
module_enable(array('crea_gn_protocols'));

// gestion des permissions pour le manager
// création et accès au raccourci CREA
$shortcut = shortcut_set_load('shortcut-set-1');
$exist = false;
foreach($shortcut->links as $link){
    if($link["link_title"] == "CREA"){
        $exist = true;
        break;
    }
}
if($exist === false){
    // on créé le raccourci
    $crea_link = array(
        'menu_name' => 'shortcut-set-1',
        'link_path' => 'admin/crea_backoffice',
        'router_path' => 'admin',
        'link_title' => 'CREA'
    );
    array_push($shortcut->links, $crea_link);
    shortcut_set_save($shortcut);
}

$date_format_short = array();
$date_format_short['type'] = 'short';
$date_format_short['format'] = 'd/m/Y - H:i';
$date_format_short['locked'] = true;
$date_format_short['locales'] = array('fr');
system_date_format_save($date_format_short);

$date_format_medium = array();
$date_format_medium['type'] = 'medium';
$date_format_medium['format'] = 'D, d/m/Y - H:i';
$date_format_medium['locked'] = true;
$date_format_medium['locales'] = array('fr');
system_date_format_save($date_format_medium);

$date_format_long = array();
$date_format_long['type'] = 'long';
$date_format_long['format'] = 'l, j. F Y - G:i';
$date_format_long['locked'] = true;
$date_format_long['locales'] = array('fr');
system_date_format_save($date_format_long);