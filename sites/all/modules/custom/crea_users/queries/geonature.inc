<?php 

$geonature_group_amphibien = variable_get('geonature_group_amphibien',1);
$geonature_group_mammiferes = variable_get('geonature_group_mammiferes',11);
$geonature_group_oiseaux = variable_get('geonature_group_oiseaux',12);
$geonature_group_reptiles = variable_get('geonature_group_reptiles',14);
$geonature_group_flore = variable_get('geonature_group_flore',1003);

define('TAXONS_GROUPS', serialize(array(
	$geonature_group_amphibien => t("Amphibiens"),
	$geonature_group_mammiferes => t("Mammifères"),
	$geonature_group_oiseaux => t("Oiseaux"),
	$geonature_group_reptiles => t("Reptiles"),
	$geonature_group_flore => t("Plantes vasculaires"),
)));

function getGeonatureAvailableTaxons($protocols = array()){
	$results = array();
	$db_data = Database::getConnection('geonaturedb','default');
	if (is_array($protocols)){
		if (empty($protocols)){
			$sql = 'SELECT id_nom, cd_nom, nom_francais FROM "taxonomie".bib_noms ORDER BY nom_francais';
			
			$res = $db_data->query($sql);
			$results['all'] = $res->fetchAll();
		}
		else{
			foreach ($protocols AS $key_protocol => $groups){
				foreach ($groups AS $group){
					$sql = 'SELECT t.id_nom, t.cd_nom, t.nom_francais
					FROM "taxonomie".bib_noms t, "taxonomie".bib_listes l, "taxonomie".cor_nom_liste ctl 
					WHERE t.id_nom = ctl.id_nom
					AND ctl.id_liste = l.id_liste
					AND l.id_liste = '.$group.'
					ORDER BY nom_francais';
					$res = $db_data->query($sql);
					$results[$key_protocol][$group] = $res->fetchAll();
				}
			}
		}
	}
	
	db_set_active();
	return $results;            
}

function crea_save_protocole_faune_flore_observation($observation = array()){	
	$db_data = Database::getConnection('geonaturedb','default');
	
	$res_ids = $db_data->query('SELECT max(id_pffs) as maxid FROM "prot_faune_flore_simple".t_fiches_pffs WHERE id_pffs < 10000000');
	foreach ($res_ids as $key => $id){
		$maxid = $id->maxid;
	}
	$maxid = $maxid + 1;
	
	// table t_fiches_cf
	$sql_fiche = 'INSERT INTO "prot_faune_flore_simple".t_fiches_pffs (id_pffs, dateobs, date_insert, date_update, altitude, x, y, id_protocole, id_lot, id_organisme)
			VALUES(:id_pffs, :dateobs, :date_insert, :date_update, :altitude, :x, :y, :id_protocole, :id_lot, :id_organisme)';

	$prot_ffs = variable_get('geonature_protocole_ffs', 103);
	$res_fiche = $db_data->query($sql_fiche, array(
		':id_pffs' => $maxid,
		':dateobs' => date('Y-m-d H:i:s', strtotime($observation['date_obs'])),
		':date_insert' => date('Y-m-d H:i:s'),
		':date_update' => date('Y-m-d H:i:s'),
		':x' => $observation['longitude'],
		':y' => $observation['latitude'],
		':altitude' => $observation['altitude'],
		':id_protocole' => $prot_ffs,
		':id_lot' => $prot_ffs,
		':id_organisme' => 99
	));
	
	// table t_releves_cf
	$sql_releve = 'INSERT INTO "prot_faune_flore_simple".t_releves_pffs (id_pffs, id_nom, commentaire, cd_ref_origine, nom_taxon_saisi, status, id_file)
			VALUES(:id_pffs, :id_nom, :commentaire, :cd_ref_origine, :nom_taxon_saisi, :status, :id_file)';
	
	$res_releve = $db_data->query($sql_releve, array(
		':id_pffs' => $maxid,
		':id_nom' => $observation['taxon_id'],
		':commentaire' => $observation['remarques'],
		':cd_ref_origine' => $observation['taxon_cd_nom'],
		':nom_taxon_saisi' => $observation['nom_francais'],
    ':status' => FALSE,
		':id_file' => $observation['id_file'],
	));
	
	
	// table cor_role_fiche_cf
	$sql_role = 'INSERT INTO "prot_faune_flore_simple".cor_role_fiche_pffs (id_pffs, id_role)
			VALUES(:id_pffs, :id_role)';
	
	$res_role = $db_data->query($sql_role, array(
		':id_pffs' => $maxid,
		':id_role' => $observation['id_role']
	));

  $sql_releve = 'UPDATE "prot_faune_flore_simple".t_releves_pffs SET status = :status
		WHERE id_pffs IN (:id_pffs)';

  $res_releve = $db_data->query($sql_releve, array(
    ':status' => true,
    ':id_pffs' => $maxid,
  ));

	db_set_active();
}

function crea_modify_protocole_faune_flore_observation($observation = array()){
    $db_data = Database::getConnection('geonaturedb','default');

    $idObs = $observation['idObs'];
    $idReleve = $idFiche = null;

    // on recupere l id fiche et releve pour pouvoir modifier derriere
    $sql = 'SELECT id_fiche_source FROM "synthese".syntheseff WHERE id_synthese='.$idObs;
    $res_sql = $db_data->query($sql)->fetchAssoc();
    if(count($res_sql) > 0){
        $idReleve = $res_sql['id_fiche_source'];
        $sql = 'SELECT id_pffs FROM "prot_faune_flore_simple".t_releves_pffs WHERE id_releve_pffs='.$idReleve;
        $res_sql = $db_data->query($sql)->fetchAssoc();
        $idFiche = $res_sql['id_pffs'];
    }

    if($idFiche != null && $idReleve != null) {

        // table t_fiches_cf
        $sql_fiche = 'UPDATE "prot_faune_flore_simple".t_fiches_pffs 
        SET 
        dateobs = :dateobs, 
        date_update = :date_update, 
        altitude = :altitude, 
        the_geom_2154 = ST_Transform(ST_SetSRID(ST_Point(:x, :y), 4326), 2154), the_geom_3857 = ST_Transform(ST_SetSRID(ST_Point(:x, :y), 4326), 3857), x = null, y = null,
        id_protocole = :id_protocole, 
        id_lot = :id_lot, 
        id_organisme = :id_organisme
        WHERE id_pffs = :id_pffs';

        $prot_ffs = variable_get('geonature_protocole_ffs', 103);
        $res_fiche = $db_data->query($sql_fiche, array(
            ':dateobs' => date('Y-m-d H:i:s', strtotime($observation['date_obs'])),
            ':date_update' => date('Y-m-d H:i:s'),
            ':altitude' => $observation['altitude'],
            ':x' => $observation['longitude'],
            ':y' => $observation['latitude'],
            ':id_protocole' => $prot_ffs,
            ':id_lot' => $prot_ffs,
            ':id_organisme' => 99,
            ':id_pffs' => $idFiche
        ));

        // table t_releves_cf
        $sql_releve = 'UPDATE "prot_faune_flore_simple".t_releves_pffs 
        SET
        id_nom = :id_nom, 
        commentaire = :commentaire, 
        cd_ref_origine = :cd_ref_origine, 
        nom_taxon_saisi = :nom_taxon_saisi, 
        status = :status, 
        id_file = :id_file
        WHERE id_releve_pffs = :id_pffs';

        $res_releve = $db_data->query($sql_releve, array(
            ':id_nom' => $observation['taxon_id'],
            ':commentaire' => $observation['remarques'],
            ':cd_ref_origine' => $observation['taxon_cd_nom'],
            ':nom_taxon_saisi' => $observation['nom_francais'],
            ':status' => TRUE,
            ':id_file' => $observation['id_file'],
            ':id_pffs' => $idReleve,
        ));

        // table cor_role_fiche_cf
        $sql_role = 'UPDATE "prot_faune_flore_simple".cor_role_fiche_pffs 
        SET 
        id_role = :id_role
        WHERE id_pffs = :id_pffs';

        $res_role = $db_data->query($sql_role, array(
            ':id_role' => $observation['id_role'],
            ':id_pffs' => $idReleve
        ));

        $sql_releve = 'UPDATE "prot_faune_flore_simple".t_releves_pffs SET status = :status
            WHERE id_pffs IN (:id_pffs)';

        $res_releve = $db_data->query($sql_releve, array(
            ':status' => true,
            ':id_pffs' => $idReleve,
        ));

        // MAJ syntheseff
        $sql_synth = 'UPDATE "synthese".syntheseff
            SET 
            cd_nom = :cd_nom,
            dateobs = :dateobs,
            altitude_retenue = :altitude,
            remarques = :remarques,
            derniere_action = \'u\',
            the_geom_2154 = ST_Transform(ST_SetSRID(ST_Point(:x, :y), 4326), 2154), the_geom_3857 = ST_Transform(ST_SetSRID(ST_Point(:x, :y), 4326), 3857)
            WHERE id_synthese = :id_synthese';

        $res_synth = $db_data->query($sql_synth, array(
            ':cd_nom' => $observation['taxon_cd_nom'],
            ':dateobs' => date('Y-m-d', strtotime($observation['date_obs'])),
            ':altitude' => $observation['altitude'],
            ':remarques' => $observation['remarques'],
            ':x' => $observation['longitude'],
            ':y' => $observation['latitude'],
            ':id_synthese' => $idObs
        ));

    }

    db_set_active();
}

function crea_get_available_taxons(){
	$geonature_group_amphibien = variable_get('geonature_group_amphibien',1);
	$geonature_group_mammiferes = variable_get('geonature_group_mammiferes',11);
	$geonature_group_oiseaux = variable_get('geonature_group_oiseaux',12);
	$geonature_group_reptiles = variable_get('geonature_group_reptiles',14);
	$geonature_group_flore = variable_get('geonature_group_flore',1003);

	$protocols = array(
		'faune' => array(
			$geonature_group_amphibien,
			$geonature_group_mammiferes,
			$geonature_group_oiseaux,
			$geonature_group_reptiles),
		'flore' => array(
			$geonature_group_flore
		)
	);

	$groups_name = unserialize(TAXONS_GROUPS);

	$taxons = getGeonatureAvailableTaxons($protocols);

	$crea_available_taxons = variable_get('crea_available_taxons', array());

	$taxon_tree = array();

	foreach ($protocols AS $key_protocol => $groups){
		if (isset($taxons[$key_protocol])){

			foreach ($groups AS $key_group){
				if (isset($taxons[$key_protocol][$key_group])){
					if (is_array($taxons[$key_protocol][$key_group])
					&& !empty($taxons[$key_protocol][$key_group])){
						foreach ($taxons[$key_protocol][$key_group] AS $taxon){
							if (isset($taxon->cd_nom)
							&& isset($taxon->nom_francais)
							&& isset($crea_available_taxons[$taxon->cd_nom])){
								$taxon_tree[$key_protocol][$key_group][$taxon->cd_nom] = $taxon->nom_francais;
							}
						}
					}
				}
			}
		}
	}
	return $taxon_tree;
}

function getGetonatureTaxonInformation($cd_nom){
	$db_data = Database::getConnection('geonaturedb','default');
	
	$sql = 'SELECT * FROM "taxonomie".bib_noms WHERE cd_nom = :cd_nom';
	$res_taxon = $db_data->query($sql, array(
		':cd_nom' => (int)$cd_nom,
	));
	
	db_set_active();
	return $res_taxon->fetchObject();
}

function getGeonaturePFFSUnpublishedObservations(){
	$db_data = Database::getConnection('geonaturedb','default');
	
	$sql = 'SELECT ptf.id_pffs, ptf.dateobs, ST_X(ST_Transform(ptf.the_geom_2154, 4326)) AS x, ST_Y(ST_Transform(ptf.the_geom_2154, 4326)) AS y, ptf.date_insert, ptf.altitude, ptr.nom_taxon_saisi, ptr.commentaire, ptr.id_file, utr.nom_role, utr.prenom_role
	FROM "prot_faune_flore_simple".t_releves_pffs ptr
	LEFT JOIN "prot_faune_flore_simple".t_fiches_pffs ptf ON ptf.id_pffs = ptr.id_pffs
	LEFT JOIN "prot_faune_flore_simple".cor_role_fiche_pffs pcr ON pcr.id_pffs = ptr.id_pffs
	LEFT JOIN "utilisateurs".t_roles utr ON utr.id_role = pcr.id_role
	WHERE ptr.status = :status
	ORDER BY ptf.date_insert DESC';
	$res_taxon = $db_data->query($sql, array(
		':status' => false,
	));
	
	db_set_active();
	return $res_taxon->fetchAll();
}

function crea_load_observations_by_user($pGroups = null, $pDate = null, $user){
	
	// on se pluggue sur la bdd geonature
	$db_data = Database::getConnection('geonaturedb','default');

	$data = array();
	
	// liste des groupes
	$sqlGroups = 'SELECT DISTINCT id_groupe
            FROM "taxonomie".bib_noms;';
	$resGroups = $db_data->query($sqlGroups);
	$groupsList = $resGroups->fetchAll();

	if($pDate == null){
		$data['date_ff'] = 'full';
	}else{
		$data['date_ff'] = $pDate['choice'];
		$data['from'] = $pDate['from'];
		$data['to'] = $pDate['to'];
	}

	$nbObs = 0;
	$listTaxons = "";
	foreach ($groupsList as $group)
	{
		$id_groupe = $group->id_groupe;
		$nom_groupe = crea_gimmeGroupName($id_groupe);
		$data[$id_groupe] = array();
		$data[$id_groupe]['name'] = $nom_groupe;
		// taxons associés
		$data[$id_groupe]['taxons'] = crea_gimmeTaxons($id_groupe);
		// puis les observations synthese
		$list_cd_nom = implode(",",array_keys($data[$id_groupe]['taxons']));
		// coché ou non ?
		if($pGroups == null || in_array($id_groupe, $pGroups)){
			$data[$id_groupe]['checked'] = 1;
			// on charge la liste globale des taxons
			if($listTaxons == ""){
				$listTaxons .= $list_cd_nom;
			}else{
				$listTaxons .= ",".$list_cd_nom;
			}
		}else{
			$data[$id_groupe]['checked'] = 0;
		}
		$data[$id_groupe]['nbObs'] = crea_gimmeObservations($list_cd_nom, $pDate, true, $user);
		$nbObs += $data[$id_groupe]['nbObs'];
	}

	// nombre total d observations
	$data['nbtotal'] = $nbObs;
	$data['listtaxons'] = $listTaxons;
	$data['entries'] = crea_gimmeObservations($listTaxons, $pDate, false, $user);

	// on se repluggue sur la bdd par defaut (drupal)
	db_set_active();
	return $data;
}

function crea_publish_protocole_faune_flore_observations($observations = array()){
	if (is_array($observations)
	&& !empty($observations)){
		$db_data = Database::getConnection('geonaturedb','default');
	
		// table t_releves_cf
		$sql_releve = 'UPDATE "prot_faune_flore_simple".t_releves_pffs SET status = :status
		WHERE id_pffs IN (:id_pffs)';
	
		$res_releve = $db_data->query($sql_releve, array(
			':status' => true,
			':id_pffs' => $observations,
		));
		
		db_set_active();
		return true;
	}
	else{
		return false;
	}
}

function crea_delete_protocole_faune_flore_observations($observations = array()){
	if (is_array($observations)
	&& !empty($observations)){
		$db_data = Database::getConnection('geonaturedb','default');
		
		// table t_releves_cf
		$sql_releve = 'DELETE FROM "prot_faune_flore_simple".t_releves_pffs
		WHERE id_pffs IN (:id_pffs)';
		
		$res_releve = $db_data->query($sql_releve, array(
				':id_pffs' => $observations,
		));
		
		// table cor_role_fiche_pffs
		$sql_role = 'DELETE FROM "prot_faune_flore_simple".cor_role_fiche_pffs
		WHERE id_pffs IN (:id_pffs)';
		
		$res_role = $db_data->query($sql_role, array(
				':id_pffs' => $observations,
		));

		// table t_releves_cf
		$sql_fiche = 'DELETE FROM "prot_faune_flore_simple".t_fiches_pffs
		WHERE id_pffs IN (:id_pffs)';
		
		$res_fiche = $db_data->query($sql_fiche, array(
			':id_pffs' => $observations,
		));

		db_set_active();
		return true;
	}
	else{
		return false;
	}
}