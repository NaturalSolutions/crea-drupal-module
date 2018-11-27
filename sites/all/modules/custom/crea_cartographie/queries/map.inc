<?php 

function crea_load_stations(){
	$nodes = array();
    global $language;
    $lng = $language->language;
	$query = db_select('node', 'n');
	//$query->addTag('node_access');
	$query->fields('n', array('nid'))
	->condition('n.type', 'station', '=')
       // ->condition('language', $lng, '=')
    ->orderBy('n.title');

	$results = $query->execute()->fetchAll();

	foreach ($results AS $result){
		$node = node_load($result->nid);
		$nodes[] = $node;
	}
	
	return $nodes;
}

function crea_load_station($id_station)
{
    $query = db_select('node', 'n');
    $query->join('field_data_field_id', 'f', 'f.entity_id = n.nid');
    $query->fields('n', array('title'))
        ->condition('f.field_id_value', $id_station, '=')
        ->condition('f.bundle', 'station', '=')
        ->orderBy('n.title');
    $station = $query->execute()->fetchAssoc();

    if (isset($station["title"])){
        return $station["title"];
    }else{
        return "";
    }
}

function crea_load_observations($pGroups = null, $pDate = null, $user = null, $pTaxon = null)
{
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $data = array();

  // recherche par groupes
  if($pTaxon == null) {
    // liste des groupes
    if (count($pGroups) > 0) {
      $groups = array_keys($pGroups);
    } else {
      $geonature_groups = array(variable_get('geonature_group_amphibien', 1), variable_get('geonature_group_mammiferes', 11), variable_get('geonature_group_oiseaux', 12), variable_get('geonature_group_reptiles', 14), variable_get('geonature_group_flore', 1003));
      $groups = $geonature_groups;
    }

    $sqlGroups = 'SELECT id_liste, nom_liste
              FROM "taxonomie".bib_listes
              WHERE id_liste IN (' . implode(',', $groups) . ') 
              ORDER BY nom_liste;';

    $resGroups = $db_data->query($sqlGroups);
    $groupsList = $resGroups->fetchAll();
  }

  if($pDate == null){
      $data['date_ff'] = 'year';
  }else{
      $data['date_ff'] = $pDate['choice'];
      $data['from'] = $pDate['from'];
      $data['to'] = $pDate['to'];
  }

    $nbObs = $nbRequest = 0;
    $listTaxons = "";


  $args = arg();
  $mesobs = false;
  if(isset($args[0]) && $args[0] == 'atlas' && isset($args[1]) && $args[1] == 'account'){
    $mesobs = true;
  }

  if($pTaxon == null) {

    foreach ($groupsList as $group) {
      $id_groupe = $group->id_liste;
      $nom_groupe = $group->nom_liste;
      $data[$id_groupe] = array();
      $data[$id_groupe]['name'] = $nom_groupe;
      // taxons associés
      $data[$id_groupe]['taxons'] = crea_gimmeTaxons($id_groupe);
      // puis les observations synthese
      $list_cd_nom = implode(",", array_keys($data[$id_groupe]['taxons']));
      // coché ou non ?
      if ($pGroups == null || in_array($id_groupe, $pGroups)) {
        $data[$id_groupe]['checked'] = 1;
        // on charge la liste globale des taxons
        if ($listTaxons == "") {
          $listTaxons .= $list_cd_nom;
        } else {
          $listTaxons .= "," . $list_cd_nom;
        }
      } else {
        $data[$id_groupe]['checked'] = 0;
      }
      $data[$id_groupe]['nbObs'] = crea_gimmeObservations($list_cd_nom, $pDate, true, $user, $mesobs);
      $nbObs += $data[$id_groupe]['nbObs'];
      if ($data[$id_groupe]['checked'] == 1) {
        $nbRequest += $data[$id_groupe]['nbObs'];
      }
    }
  }else{
    // recherche par taxons
    $data[$pTaxon] = array();
    $data[$pTaxon]['name'] = $pTaxon;
    $data[$pTaxon]['taxons'] = $pTaxon;
    $list_cd_nom = $pTaxon;
    $listTaxons = $pTaxon;
    $data[$pTaxon]['nbObs'] = crea_gimmeObservations($list_cd_nom, $pDate, true, $user, $mesobs);
    $nbObs += $data[$pTaxon]['nbObs'];
    $nbRequest += $data[$pTaxon]['nbObs'];
  }

    // nombre total d observations
    $data['nbtotal'] = $nbObs;
    $data['nbrequest'] = $nbRequest;
    $data['listtaxons'] = $listTaxons;
    $data['entries'] = crea_gimmeObservations($listTaxons, $pDate, false, $user, $mesobs);

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

function crea_gimmeGroups(){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $data = array();

  $geonature_groups = variable_get('geonature_group_amphibien', 1).','.variable_get('geonature_group_mammiferes', 11).','.variable_get('geonature_group_oiseaux', 12).','.variable_get('geonature_group_reptiles', 14).','.variable_get('geonature_group_flore', 1003);
    // liste des groupes
    $sqlGroups = 'SELECT id_liste, nom_liste
            FROM "taxonomie".bib_listes
            WHERE id_liste IN ('.$geonature_groups.') 
            ORDER BY nom_liste;';
    $resGroups = $db_data->query($sqlGroups);
    $groupsList = $resGroups->fetchAll();

    foreach ($groupsList as $group)
    {
      switch($group->id_liste){
        case variable_get('geonature_group_amphibien', 1):
          $iconLoad = 'amphibiens';
          break;
        case variable_get('geonature_group_mammiferes', 11):
          $iconLoad = 'mammiferes';
          break;
        case variable_get('geonature_group_oiseaux', 12):
          $iconLoad = 'oiseaux';
          break;
        case variable_get('geonature_group_reptiles', 14):
          $iconLoad = 'reptiles';
          break;
        case variable_get('geonature_group_flore', 1003):
          $iconLoad = 'flore';
          break;
      }

        $data[$group->id_liste] = $group->nom_liste.' <img src="/'.drupal_get_path('theme', 'crea').'/images/icon_'.$iconLoad.'.png" width="20" height="20" />';
    }
    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

function crea_gimmeGroupId($cd_nom){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $sqlGroup = 'SELECT taxo.id_nom, liste.id_liste
                FROM "taxonomie".bib_noms taxo, "taxonomie".cor_nom_liste cor, "taxonomie".bib_listes liste 
                WHERE cd_nom='.$cd_nom.'
                AND taxo.id_nom = cor.id_nom
                AND liste.id_liste = cor.id_liste';

    $resGroup = $db_data->query($sqlGroup);
    $group = $resGroup->fetchAssoc();

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $group['id_liste'];
}

function crea_gimmeGroupName($id_groupe){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $sqlGroup = 'SELECT nom_groupe
                FROM "taxonomie".bib_groupes
                WHERE id_groupe='.$id_groupe;

    $resGroup = $db_data->query($sqlGroup);
    $group = $resGroup->fetchAssoc();

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();
    
    $query = db_select('locales_target', 'lt');
    $query->join('locales_source', 'ls', 'ls.lid = lt.lid');
    $query->fields('ls', array('source'))
    ->condition('lt.translation', $group['nom_groupe'], '=')
    ->condition('lt.language', 'fr', '=')
    ->range(0, 1);
    
    $res = $query->execute()->fetchObject();
    
    if (is_object($res)){
    	$group['nom_groupe'] = t($res->source, array(), array('context' => 'CREA_LNG'));
    }

    return $group['nom_groupe'];
}

function crea_gimmeCdName($cd_nom){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');
    $sqlName = 'SELECT nom_francais
                FROM "taxonomie".bib_noms
                WHERE cd_nom='.$cd_nom;

    $resName = $db_data->query($sqlName);
    $name = $resName->fetchAssoc();

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $name['nom_francais'];
}

function crea_gimmeTaxons($id_groupe){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $data = array();

    $sqlTaxons = 'SELECT taxo.cd_nom, taxo.nom_francais
                FROM "taxonomie".bib_noms taxo, "taxonomie".cor_nom_liste cor, "taxonomie".bib_listes liste 
                WHERE liste.id_liste ='.$id_groupe.'
                AND taxo.id_nom = cor.id_nom
                AND liste.id_liste = cor.id_liste';

    $resTaxons = $db_data->query($sqlTaxons);
    $taxons = $resTaxons->fetchAll();

    foreach ($taxons as $taxon)
    {
      if($taxon->nom_francais != "NULL"){
        $data[$taxon->cd_nom] = $taxon->nom_francais;
      }else{
        $data[$taxon->cd_nom] = "";
      }
    }

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

function crea_gimmePseudo($observateur){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $sqlPseudo = 'SELECT identifiant
                FROM "utilisateurs".t_roles
                WHERE CONCAT_WS(\' \', nom_role, prenom_role) =\''.$observateur.'\'';

    $resPseudo = $db_data->query($sqlPseudo);
    $pseudo = $resPseudo->fetchAssoc();

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $pseudo["identifiant"];
}

function crea_gimmePic($id_fiche){
    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $prot_ffs = variable_get('geonature_protocole_ffs', 103);
    $sqlProt = 'SELECT db_schema, db_table, db_field
    FROM
    "synthese".syntheseff synth,
    "synthese".bib_sources bib
    WHERE synth.id_protocole = bib.id_source
    AND synth.id_fiche_source = \''.$id_fiche.'\'
    AND synth.id_protocole = \''.$prot_ffs.'\'';

    $resProt = $db_data->query($sqlProt);
    $protocole = $resProt->fetchAssoc();

    $db_schema = $protocole['db_schema'];
    $db_table = $protocole['db_table'];
    $db_field = $protocole['db_field'];

    $sqlPic = 'SELECT id_file
    FROM
    "'.$db_schema.'".'.$db_table.' releve
    WHERE releve.'.$db_field.' = '.$id_fiche;

    $resPic = $db_data->query($sqlPic);
    $pic = $resPic->fetchAssoc();

    if($pic['id_file'] != 0){
        $picture = file_load($pic['id_file']);
        $url = file_create_url($picture->uri);
        $img_link = '<a href="'.$url.'" target="_blank"><img src="'.$url.'" width="100%" /></a>';
    }else{
        $img_link = "";
    }

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $img_link;
}

function crea_gimmeObservations($list_cd_nom = '', $objDate = null, $count = false, $user = null, $mesobs = false){

    // on se pluggue sur la bdd geonature
    $db_data = Database::getConnection('geonaturedb','default');

    $data = array();

    if($objDate != null){
        switch($objDate['choice']){
            case 'full':
                $filterDate = '';
            break;
            case 'year':
                $filterDate = ' AND dateobs <= CURRENT_TIMESTAMP AND dateobs >= CURRENT_TIMESTAMP - INTERVAL \'1 year\'';
            break;
            case 'custom':
                $from = explode("/",$objDate['from']);
                $to = explode("/",$objDate['to']);
                $from = mktime(0,0,0,$from[1],$from[0],$from[2]);
                $from = date("Y-m-d", $from);
                $to = mktime(23,59,59,$to[1],$to[0],$to[2]);
                $to = date("Y-m-d", $to);
                $filterDate = ' AND dateobs <= \''.$to.'\' AND dateobs >= \''.$from.'\'';
                
            break;
        }
    }else{
        // par défaut sur l'année
        $filterDate = ' AND dateobs <= CURRENT_TIMESTAMP AND dateobs >= CURRENT_TIMESTAMP - INTERVAL \'1 year\'';
    }
    
    if ($user != null){
    	$filterUser = '';
    	$geonatuser = verifyIfUserExistsInExternalBDD('geonaturedb', $user->name, $user->mail);
    	if (is_array($geonatuser)
    	&& !empty($geonatuser)){
    		$geonatuser = current($geonatuser);
    		$geonatuser_name = $geonatuser->nom_role . ' ' . $geonatuser->prenom_role;
    		$filterUser = ' AND observateurs = \''.$geonatuser_name.'\'';
    	}
    }
    else{
    	$filterUser = '';
    }

  $prots = variable_get('geonature_protocole_chocard', 100).','.variable_get('geonature_protocole_grenouille', 101).','.variable_get('geonature_protocole_mesange', 102);
  if($mesobs == false){
      $mesobs = 'AND id_protocole NOT IN ('.$prots.')';
    }else{
      $mesobs = '';
    }

    $sqlObs = 'SELECT id_synthese, id_fiche_source, id_protocole, cd_nom, dateobs, observateurs, altitude_retenue,
                ST_X (ST_Transform (the_geom_2154, 4326)) AS pntx,
                ST_Y (ST_Transform (the_geom_2154, 4326)) AS pnty
                FROM "synthese".syntheseff
                WHERE cd_nom IN ('.$list_cd_nom.')'.$filterDate.$filterUser.' 
                AND supprime = FALSE
                '.$mesobs.' ORDER BY dateobs DESC';

  // AND id_protocole NOT IN ('.$prots.') ORDER BY dateobs DESC

    $resObs = $db_data->query($sqlObs);

    if($count === false) {
        $observations = $resObs->fetchAll();

        foreach ($observations as $obs) {
            // tabid permet de regroupe si on a plusieurs obs sur un meme point pour un meme groupe
            $tabid = $obs->cd_nom.'_'.$obs->pnty.'_'.$obs->pntx;

            if( !isset($data[$tabid])){
                // une seule observation pour un point
                $data[$tabid] = array();
                $data[$tabid]['id'] = $obs->id_synthese;
                $data[$tabid]['nom'] = crea_gimmeCdName($obs->cd_nom);
                $data[$tabid]['dateobs'] = $obs->dateobs;
                $data[$tabid]['groupe'] = crea_gimmeGroupId($obs->cd_nom);
                $data[$tabid]['obs'] = crea_gimmePseudo($obs->observateurs);
                $data[$tabid]['altitude'] = $obs->altitude_retenue;
                $data[$tabid]['lat'] = $obs->pnty;
                $data[$tabid]['long'] = $obs->pntx;
                $data[$tabid]['nbobs'] = 1;
                $data[$tabid]['prot'] = $obs->id_protocole;
                $data[$tabid]['picto'] = gimmePictoProt($data[$tabid]['prot'], $data[$tabid]['groupe']);
                $data[$tabid]['groupelibelle'] = gimmeProtocolAndList($data[$tabid]['prot'], $data[$tabid]['groupe']);
            }else{
                // plusieurs observations sur le point
                // on recupère la dernière date, altitude
                $data[$tabid]['dateobs'] = $obs->dateobs;
                $data[$tabid]['altitude'] = $obs->altitude_retenue;
                $data[$tabid]['nbobs'] += 1;
                $data[$tabid]['prot'] = t('Plusieurs observations');
            }

            // image faune flore
           $prot_ffs = variable_get('geonature_protocole_ffs', 103);
            if($obs->id_protocole == $prot_ffs){
                $data[$tabid]['pic'] = crea_gimmePic($obs->id_fiche_source);
            }else{
                $data[$tabid]['pic'] = "";
            }
        }
    }else{
        $data = $resObs->rowCount();
    }

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

function gimmeProtocolAndList($prot_id, $liste_id){
  // on se pluggue sur la bdd geonature
  $db_data = Database::getConnection('geonaturedb','default');

  $sqlProtocole = 'SELECT nom_protocole
                FROM "meta".t_protocoles
                WHERE id_protocole ='.$prot_id;

  $resProtocole = $db_data->query($sqlProtocole);
  $protocole = $resProtocole->fetchAssoc();

  $sqlListe = 'SELECT nom_liste
                FROM "taxonomie".bib_listes
                WHERE id_liste ='.$liste_id;

  $resListe = $db_data->query($sqlListe);
  $liste = $resListe->fetchAssoc();

  // on se repluggue sur la bdd par defaut (drupal)
  db_set_active();

  $mylist = '';
  switch($prot_id) {
    // contact faune ou faune flore smiplifiée
    case variable_get('geonature_protocole_contactfaune', 1):
    case variable_get('geonature_protocole_ffs', 103):
      $mylist = ' - '.$liste['nom_liste'];
      break;
  }

  return $protocole["nom_protocole"].$mylist;
}

function gimmePictoProt($prot_id, $liste_id){
  $img = '';
  switch($prot_id) {
    // chocard
    case variable_get('geonature_protocole_chocard', 100):
      $img = 'icon_chocard.png';
      break;
    // grenouille
    case variable_get('geonature_protocole_grenouille', 101):
      $img = 'icon_grenouille.png';
      break;
    // mesange
    case variable_get('geonature_protocole_mesange', 102):
      $img = 'icon_mesange.png';
      break;
    // contact faune ou faune flore smiplifiée
    case variable_get('geonature_protocole_contactfaune', 1):
    case variable_get('geonature_protocole_ffs', 103):
      if($liste_id == variable_get('geonature_group_amphibien', 1)) {
        $img = 'icon_amphibiens.png';
      }elseif ($liste_id == variable_get('geonature_group_mammiferes', 11)){
        $img = 'icon_mammiferes.png';
      }elseif ($liste_id == variable_get('geonature_group_oiseaux', 12)){
        $img = 'icon_oiseaux.png';
      }elseif ($liste_id == variable_get('geonature_group_reptiles', 14)){
        $img = 'icon_reptiles.png';
      }elseif ($liste_id == variable_get('geonature_group_flore', 1003)){
        $img = 'icon_flore.png';
      }
      break;
  }

  if($img != ''){
    $img = '<img src="/sites/all/themes/crea/images/'.$img.'" />';
  }

  return $img;
}

function gimmeObservationFiche($id){
  // on se pluggue sur la bdd geonature
  $db_data = Database::getConnection('geonaturedb','default');

  $sqlObs = 'SELECT remarques
                FROM "synthese".syntheseff
                WHERE id_synthese ='.$id;

  $resObs = $db_data->query($sqlObs);
  $obs = $resObs->fetchAssoc();

  // on se repluggue sur la bdd par defaut (drupal)
  db_set_active();

  return $obs["remarques"];
}