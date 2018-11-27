<?php 
/*
 * Renvoie un tableau avec les statistiques globales de Geonature
 * Combien de fiches par protocole
 */
function gimmeStatsGeonature(){
    // on se pluggue sur la bdd crea-data
    $db_data = Database::getConnection('geonaturedb','default');

    // init data
    $data = array();

    // on recupère les différents protocoles
    $sqlProtocoles = 'SELECT id_protocole, nom_protocole
                FROM "meta".t_protocoles
                ORDER BY id_protocole';
    $resProtocoles = $db_data->query($sqlProtocoles);
    $protocoles = $resProtocoles->fetchAll();
    foreach ($protocoles as $prot)
    {
        // on va chercher combien on a d'entrées dans la table synthèse
        $sqlProt = 'SELECT COUNT(*) as nbfiches
                FROM "synthese".syntheseff
                WHERE id_protocole='.$prot->id_protocole;
        $resProt = $db_data->query($sqlProt);
        $protocole = $resProt->fetchAssoc();
        $data[$prot->id_protocole] = array('name' => $prot->nom_protocole, 'nbfiches' => $protocole['nbfiches']);
    }

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

/*
 * Renvoie un tableau avec les statistiques de Geonature suivant une liste de protocoles
 *
 * @param $protocoles_id
 */
function gimmeStatsGeonatureProtocoles(array $protocoles_id){
  // init data
  $data = array();

  if (is_array($protocoles_id)
  && !empty($protocoles_id)){
    // on se pluggue sur la bdd crea-data
    $db_data = Database::getConnection('geonaturedb','default');

    foreach ($protocoles_id AS $protocole_id){
      // on va chercher combien on a d'entrées dans la table synthèse
      $sqlProt = 'SELECT COUNT(*) as nbfiches
                FROM "synthese".syntheseff
                WHERE id_protocole='.$protocole_id;
      $resProt = $db_data->query($sqlProt);
      $protocole = $resProt->fetchAssoc();
      $data[$protocole_id] = array('nbfiches' => $protocole['nbfiches']);
    }

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();
  }

  return $data;
}