# crea-drupal-module

## Mise à jour d'une instance locale
- Récupérer une base de données à jour sur le serveur de prod
> pg_dump -U <myuser> -Fc -h localhost <mydatabase> > ./mybackup.backup

- Restaurer la base de données sur votre instance locale
> pg_restore -c --username=<myuser> --dbname=<mydatabase> -h localhost -n public ./mybackup.backup

- Mettre à jour le code
> cd crea-drupal-module
> git pull origin master

- Appliquer les mises à jour de code vers la base de données (par exemple : mise à jour de module).
Vérifier que le paramètre update est à TRUE dans le fichier settings.php
> http://<nom-de-domain-atlas.local>/update.php

- Désactiver le module captcha et recaptcha avec Drush
> cd path/mydrupal
> drush dis captcha

- Se connecter à l'instance atlasmontblanc. 
> http://<nom-de-domain-atlas.local>/user

- Modifier le chemin vers le dossier temporaire :
> http://<nom-de-domain-atlas.local>/admin/config/media/file-system

- Modifier les nom de domaines de prod par ceux de votre instance de démo ou locales :  
> http://<nom-de-domain-atlas.local>/fr/admin/structure/domain
