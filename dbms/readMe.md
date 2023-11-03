Installation Process :

sudo apt install mysql-server

sudo service mysql stop

sudo usermod -d /var/lib/mysql/ mysql

sudo ln -s /run/mysqld/mysqld.sock /var/run/mysqld/mysqld.sock



Extension Setup and more :
https://www.youtube.com/watch?v=4KXLY5Sf2fU
or explained at last



Checking MySQL : 
sudo service --status-all


Running Process :

STEP 1 : sudo service mysql start

STEP 2 : Write mysql code Right click and run selected part.

Note : write these before creating a new table,

CREATE DATABASE name;     // To create database in case
USE dbmsLab;              //  To select database to use
"DROP TABLE IF EXISTS table_name;"
"FLUSH TABLES table_Name;"



Extension Setup :

sudo mysql -h localhost -P 3306 or just sudo mysql

create user 'pratham'@'%' identified with mysql_native_password by 'password'

grant all privileges on *.* to 'pratham1'@'%';