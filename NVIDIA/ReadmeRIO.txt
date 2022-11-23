sudo apt install mysql-server
sudo mysql_secure_installation

unzip le document 

connecte à mysql


sudo mysql

mysql> CREATE USER 'nouveau_utilisateur'@'localhost' IDENTIFIED BY 'mot_de_passe

mysql> GRANT ALL PRIVILEGES ON * . * TO 'nouveau_utilisateur'@'localhost';

mysql> FLUSH PRIVILEGES

mysql> exit

se reconecter sur l'utilisateur à mysql 

mysql> source mysqlsampledatabe.sql

mysql> exit

aller voir le script

mkdir log

script.sh
#!/bin/bash
date_stamp=$(date +"%F-%H-%M-%S")

mysqldump -u gui -p classicmodels | bzip2 -c > /log/$date_stamp.sql.bz2
find /log/* -mtime 50 rm {} \;

TD1.service
[Unit]
Description=execute script
After=network.target

[Service]
WorkingDirectory=/home/gui/TD1
User=gui
ExecStart=/home/gui/TD1/script.sh
Type=oneshot

TD1.timer
[Unit]
Description=Run script every 10 minutes
[Timer]
OnCalendar=*-*-* *:00,10,20,30,40,50
[Install]
WantedBy=default.target




