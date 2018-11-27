<?php 

function insertUserInExternalBDD($bdd = '', $last_name = '', $first_name = '', $name = '', $mail = '', $pass = '', $id_organisme = 99, $nom_organisme = 'Autre', $id_unite = 5){
	// id du group "CREA" : 1000000
	// id du group "observateurs" : 1000009
	
	$db_data = Database::getConnection($bdd,'default');

	$sql = "INSERT INTO utilisateurs.t_roles (groupe, nom_role, prenom_role, identifiant, email, pass, id_organisme, organisme, id_unite)
	            VALUES('false', :last_name, :first_name, :name, :mail, :pass, :id_organisme, :nom_organisme, :id_unite)";
	$res = $db_data->query($sql, array(
			':last_name' => filter_xss($last_name),
			':first_name' => filter_xss($first_name),
			':name' => filter_xss($name),
			':mail' => filter_xss($mail),
			':pass' => filter_xss($pass),
			':id_organisme' => filter_xss($id_organisme),
			':nom_organisme' => filter_xss($nom_organisme),
			':id_unite' => filter_xss($id_unite),
	));
	db_set_active();
}

function updateUserInExternalBDD($bdd = '', $old_login = '', $old_email = '', $options = array(), $is_blocked = false){
  if (isset($old_login) && $old_login !== ''
  && isset($old_email) && $old_email !== ''
  && is_array($options) && !empty($options)) {

    $db_data = Database::getConnection($bdd, 'default');

    $user_found = verifyIfUserExistsInExternalBDD($bdd, $old_login, $old_email);

    if (is_array($user_found)
    && !empty($user_found)) {
      $user_found = current($user_found);
      $valuesToUpdate = array();
      $valuesStringAlias = '';
      end($options);
      $lastKey = key($options);
      reset($options);
      foreach($options AS $key => $value){
        if ($key === 'id_role'){
          unset($options[$key]);
          break;
        }
        if ($key === 'pass'
        && $value == ''){
          unset($options[$key]);
          break;
        }
        $valuesToUpdate[':' . $key] = filter_xss($value);
        $valuesStringAlias .= $key . ' = :' . $key;
        if ($key !== $lastKey){
          $valuesStringAlias .= ', ';
        }
      }

      $valuesToUpdate[':id_role'] = $user_found->id_role;

      $sql = "UPDATE utilisateurs.t_roles SET " . filter_xss($valuesStringAlias) . " WHERE id_role = :id_role";
      $res = $db_data->query($sql, $valuesToUpdate);

      if ($is_blocked){
        $sql = "UPDATE utilisateurs.cor_role_droit_application SET id_droit = 0  WHERE id_role = :id_role";
        $res = $db_data->query($sql, array(':id_role' => $user_found->id_role));
      }
      db_set_active();
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

function deleteUserInExternalBDD($bdd = '', $id_role = ''){
	$db_data = Database::getConnection($bdd,'default');

	$sql = "DELETE FROM utilisateurs.t_roles WHERE id_role = ".$id_role.";";
	$res = $db_data->query($sql);
	
	$sql = "DELETE FROM utilisateurs.cor_roles WHERE id_role_utilisateur = ".$id_role.";";
	$res = $db_data->query($sql);

	$sql = "DELETE FROM utilisateurs.cor_role_droit_application WHERE id_role = ".$id_role.";";
	$res = $db_data->query($sql);
	db_set_active();
}


function verifyIfUserExistsInExternalBDD($bdd = '', $login = '', $email = ''){
	$db_data = Database::getConnection($bdd,'default');

	$sql = 'SELECT *
            FROM "utilisateurs".t_roles
            WHERE identifiant LIKE \''.$login.'\'
            AND email = \''.$email.'\'
            LIMIT 1;';
	$res = $db_data->query($sql);
	$results = $res->fetchAll();

	db_set_active();
	return $results;
}

function verifyIfOrganismExistsInExternalBDD($bdd = '', $string = ''){
	$results = array();
	if ($string !== ''){
		$string = strToLower($string);
		$db_data = Database::getConnection($bdd,'default');

		$sql = 'SELECT *
	            FROM "utilisateurs".bib_organismes
	            WHERE LOWER(nom_organisme) LIKE \'%'.filter_xss($string).'%\'
	            LIMIT 1;';
		$res = $db_data->query($sql);
		$results = $res->fetchAll();
	}

	db_set_active();
	return $results;
}

function verifyIfUnitExistsInExternalBDD($bdd = '', $id = ''){
	$results = array();
	if ($id !== ''){
		$db_data = Database::getConnection($bdd,'default');

		$sql = 'SELECT *
	            FROM "utilisateurs".bib_unites
	            WHERE id_unite = '.filter_xss($id).'
	            LIMIT 1;';
		$res = $db_data->query($sql);
		$results = $res->fetchAll();
	}

	db_set_active();
	return $results;
}

function canUserInsertObs($bdd = '', $name= ''){
	$can = false;
	if ($name !== ''){
		$db_data = Database::getConnection($bdd,'default');

		$sql = 'SELECT date_insert
	            FROM "synthese".syntheseff
	            WHERE observateurs LIKE \'%'.filter_xss($name).'%\'
	            AND date_insert >= CURRENT_TIMESTAMP - INTERVAL \'10 seconds\'
	            ORDER BY date_insert DESC
	            LIMIT 1;';
		$res = $db_data->query($sql);
		$lastobs = $res->fetchAll();
		if(!$lastobs[0]->date_insert){
			$can = true;
		}
	}

	db_set_active();
	return $can;
}