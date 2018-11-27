<?php 

function crea_organism_autocomplete_callback($string){	
	$matches = array();
	if ($string !== ''){
		$string = strTolower($string);
		$db_data = Database::getConnection('usershubdb','default');
		
		$sql = 'SELECT nom_organisme
	            FROM "utilisateurs".bib_organismes
				WHERE LOWER(nom_organisme) LIKE \'%'.filter_xss($string).'%\';';
		$res = $db_data->query($sql);
		$results = $res->fetchAll();
		
		if (!empty($results)){
			foreach ($results AS $result){
				if (is_object($result)){
					$matches[$result->nom_organisme] = $result->nom_organisme;
				}
			}
		}
	}
	
	if(empty($matches)) $matches[] = '';
	// Return the result to the form in json
	db_set_active();
	drupal_json_output($matches);
}