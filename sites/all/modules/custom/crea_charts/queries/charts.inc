<?php
/*
 * Renvoie un tableau de données avec les températures moyennes annuelles
 * @param $id_station
 * @param $year
 */
function crea_load_annual_charts($id_station, $year){
    // on se pluggue sur la bdd crea-data
    $db_data = Database::getConnection('crea-data','default');
    $db_data_archive = Database::getConnection('crea-data-archive','default');

    // init data
    $data = array();
    $mergeData = array();

    // on recupère tous les jours enregistrés

    $sqlDays = 'SELECT to_char(value_date, \'YYYY-MM-DD\') as day,
                ROUND(AVG(capteur_1)::numeric,2) as sum_c1,
                ROUND(AVG(capteur_2)::numeric,2) as sum_c2,
                ROUND(AVG(capteur_3)::numeric,2) as sum_c3,
                ROUND(AVG(capteur_4)::numeric,2) as sum_c4
                FROM "data-temperatures".temperatures
                WHERE id_station='.$id_station.'
                AND extract(year from value_date) = '.$year.'
                GROUP BY to_char(value_date, \'YYYY-MM-DD\')
                ORDER BY day ASC
                LIMIT 366;';
    $resDays = $db_data->query($sqlDays);
    $resDaysArchive = $db_data_archive->query($sqlDays);
    $daysList = $resDays->fetchAll();
    $daysListArchive = $resDaysArchive->fetchAll();

    $mergeData = array_merge_recursive($daysList, $daysListArchive);

    $data = _formate_data_annual_charts($mergeData);

    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

function _formate_data_annual_charts($dayList) {
  $data = array();
  foreach ($daysList as $day){
        // timestamp du jour parcouru en ms
        $d = new DateTime($day->day);
        $timing = $d->getTimestamp()*1000;
        // moyennes journalières
        $data[0][] = array($timing, floatval($day->sum_c1));
        $data[1][] = array($timing, floatval($day->sum_c2));
        $data[2][] = array($timing, floatval($day->sum_c3));
        $data[3][] = array($timing, floatval($day->sum_c4));
  }
  return $data;
}

/*
 * Renvoie un tableau de données avec les températures au 1/4h des 7 derniers jours
 * @param $id_station
 */
function crea_load_lastdays_charts($id_station){
    // on se pluggue sur la bdd crea-data
    $db_data = Database::getConnection('crea-data','default');
    // init data
    $data = array();
    $day = mktime(0, 0, 0);
    // on recupère tous les jours enregistrés
    $sqlRecords = 'SELECT value_date, capteur_1, capteur_2, capteur_3, capteur_4
                FROM "data-temperatures".temperatures
                WHERE id_station='.$id_station.'
                AND value_date <= CURRENT_TIMESTAMP
                AND value_date >= CURRENT_TIMESTAMP - INTERVAL \'7 days\'
                ORDER BY value_date ASC
                LIMIT 700';
    // AND value_date <= CURRENT_TIMESTAMP - INTERVAL \'2 years\'
    // AND value_date >= CURRENT_TIMESTAMP - INTERVAL \'2 years 7 days\'
    $resRecords = $db_data->query($sqlRecords);
    $records = $resRecords->fetchAll();

    foreach ($records as $rec)
    {
        // timestamp du jour parcouru en ms
        $d = new DateTime($rec->value_date);
        $timing = $d->getTimestamp()*1000;
        // temperatures au 1/4h
        if(floatval($rec->capteur_1) <= 50 && floatval($rec->capteur_1) >= -40){
            $data[0][] = array($timing, floatval($rec->capteur_1));
        }else{
            $data[0][] = array($timing, null);
        }
        if(floatval($rec->capteur_2) <= 50 && floatval($rec->capteur_2) >= -40) {
            $data[1][] = array($timing, floatval($rec->capteur_2));
        }else{
            $data[1][] = array($timing, null);
        }
        if(floatval($rec->capteur_3) <= 50 && floatval($rec->capteur_3) >= -40) {
            $data[2][] = array($timing, floatval($rec->capteur_3));
        }else{
            $data[2][] = array($timing, null);
        }
        if(floatval($rec->capteur_4) <= 50 && floatval($rec->capteur_4) >= -40) {
            $data[3][] = array($timing, floatval($rec->capteur_4));
        }else{
            $data[3][] = array($timing, null);
        }
    }
    // on se repluggue sur la bdd par defaut (drupal)
    db_set_active();

    return $data;
}

/*
 * Renvoie un tableau de données avec les températures moyennes d une station
 * @param $id_station
 */
function crea_load_station_charts($id_station){
  // on se pluggue sur la bdd crea-data
  $db_data = Database::getConnection('crea-data','default');
  $db_data_archive = Database::getConnection('crea-data-archive','default');

  // init data
  $data = array();
  $mergeData = array();

  // on recupère tous les jours enregistrés
  $midnight = mktime(0,0,0,date("n"),date("j"),date("Y"));
  $midnight = date("Y-m-d H:i:s", $midnight);
  $sqlDays = 'SELECT to_char(value_date, \'YYYY-MM-DD\') as day,
                ROUND(AVG(capteur_1)::numeric,2) as sum_c1,
                ROUND(AVG(capteur_2)::numeric,2) as sum_c2,
                ROUND(AVG(capteur_3)::numeric,2) as sum_c3,
                ROUND(AVG(capteur_4)::numeric,2) as sum_c4
                FROM "data-temperatures".temperatures
                WHERE id_station='.$id_station.'
                AND value_date < \''.$midnight.'\'
                GROUP BY to_char(value_date, \'YYYY-MM-DD\')
                ORDER BY day ASC';
  // bd de temperature courante crea-data
  $resDays = $db_data->query($sqlDays);
  $daysList = $resDays->fetchAll();

  // bd de temperature archivées crea-data-archive
  $resDaysArchive = $db_data_archive->query($sqlDays);
  $daysListArchive = $resDaysArchive->fetchAll();

  $mergeData = array_merge_recursive($daysListArchive, $daysList);

  $data = _formate_data_station_charts($mergeData);

  // on se repluggue sur la bdd par defaut (drupal)
  db_set_active();

  return $data;
}

function _formate_data_station_charts($daysList){
  $data= array();

  foreach ($daysList as $day)
  {
    // timestamp du jour parcouru en ms
    $d = new DateTime($day->day);
    $timing = $d->getTimestamp()*1000;
    // moyennes journalières
    if(floatval($day->sum_c1) <= 50 && floatval($day->sum_c1) >= -40) {
      $data[0][] = array($timing, floatval($day->sum_c1));
    }else{
      $data[0][] = array($timing, null);
    }
    if(floatval($day->sum_c2) <= 50 && floatval($day->sum_c2) >= -40) {
      $data[1][] = array($timing, floatval($day->sum_c2));
    }else{
      $data[1][] = array($timing, null);
    }
    if(floatval($day->sum_c3) <= 50 && floatval($day->sum_c3) >= -40) {
      $data[2][] = array($timing, floatval($day->sum_c3));
    }else{
      $data[2][] = array($timing, null);
    }
    if(floatval($day->sum_c4) <= 50 && floatval($day->sum_c4) >= -40) {
      $data[3][] = array($timing, floatval($day->sum_c4));
    }else{
      $data[3][] = array($timing, null);
    }
  }
  return $data;
}

/*
 * Renvoie un tableau des dernières données d une station
 * @param $id_station
 */
function crea_load_station_last_values($id_station){
  // on se pluggue sur la bdd crea-data
  $db_data = Database::getConnection('crea-data','default');

  // on recupère les données
  $sqlData = 'SELECT to_char(value_date, \'HH24hMI\') as last_date,
                value_date,
                ROUND(AVG(capteur_1)::numeric,2) as sum_c1,
                ROUND(AVG(capteur_2)::numeric,2) as sum_c2,
                ROUND(AVG(capteur_3)::numeric,2) as sum_c3,
                ROUND(AVG(capteur_4)::numeric,2) as sum_c4
                FROM "data-temperatures".temperatures
                WHERE id_station='.$id_station.'
                AND value_date >= CURRENT_TIMESTAMP - INTERVAL \'1 day\'
                GROUP BY value_date
                ORDER BY value_date DESC
                LIMIT 1';
  $resData = $db_data->query($sqlData);
  $data = $resData->fetchObject();

  // cas où on n'a pas d'info depuis 24h

  if($data == null){
    $data = new stdClass();
    $data->last_date = '---';
    $data->value_date = '---';
    $data->sum_c4 = '- ';
    $data->sum_c1 = '- ';
  }

  // on se repluggue sur la bdd par defaut (drupal)
  db_set_active();

  return $data;
}
