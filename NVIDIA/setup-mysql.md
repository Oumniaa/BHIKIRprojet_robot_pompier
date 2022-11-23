# Installation mysql
    ```shell
    sudo apt-get update  
    sudo apt install mysql-server
  

##	Création d'un utilisateur avec tous les privilèges
     
    sudo mysql -u root /: Connection à mysql 
    mysql> CREATE USER 'oumnia'@'localhost' IDENTIFIED BY 'mot_de_passe'
    mysql> GRANT ALL PRIVILEGES ON * . * TO 'oumnia'@'localhost';
    mysql> FLUSH PRIVILEGES;
    mysql>exit
    mysql>exit
    mysql> alter user oumnia@localhost identified with auth_socket;
    //pour faire fonctionner mon service sinon on demande le mot de passe à chaque fois
 
## Telechargement de la database

    wget https://www.mysqltutorial.org/wp-content/uploads/2018/03/mysqlsampledatabase.zip

    mysql> source /home/oumnia/mysqlsampledatabase.sql
    //importation de la base de donnée

## Le script

```
vim dump-database.sh
#!/bin/bash
 exec &>>/var/log/dump-mysql.log
 // Transfert vers .log
 echo "starting database backup"
current_date=$(date +%F+%H+%M+%S)
mysqldump -u oumnia classicmodels|bzip2 -c  > "$current_date.sql.bz2"                                                           echo "backup complete"      
fic=”*.bz2”                                                                                     
ls -t *fic | tail -n +5 | while read fic                                                                                     
do
    if test -e $fic
    then
     rm $fic
  fi
done
//si le nombre de fichier dépasse 5, on supprime les anciens
 ```
 
Et pour l'executer 
```
./dump-database.sh
```
