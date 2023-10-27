                        # READ ME

Installation Process :

sudo apt install mysql-server
sudo service mysql stop
sudo usermod -d /var/lib/mysql/ mysql
ln -s /run/mysqld/mysqld.sock /var/run/mysqld/mysqld.sock


Extension Setup and more :
https://www.youtube.com/watch?v=4KXLY5Sf2fU


Checking :
sudo service --status-all


Running Process :

STEP 1 : sudo service mysql start

STEP 2 : In mysql (located at lower left corner), Right click on mysql in localhost and select new query.
Close new file that gets opened.
Write mysql code Right click and run selected part.
Note : write these before creating a new table,

"DROP TABLE IF EXISTS table_name;"
"FLUSH TABLES table_Name;"
