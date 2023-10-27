                        # READ ME

Installation Process :

sudo apt install mysql-server
sudo service mysql stop
sudo usermod -d /var/lib/mysql/ mysql
ln -s /run/mysqld/mysqld.sock /var/run/mysqld/mysqld.sock


Extension Setup and more :
https://www.youtube.com/watch?v=4KXLY5Sf2fU


Running Process :

sudo service mysql start.
In mysql (located at lower left corner), Right click on mysql in localhost and select new query.
Close new file that gets opened.
Write mysql code Right click and run selected part.
Note : write "DROP TABLE IF EXISTS table_name;", before creating new table.
             "FLUSH TABLES table_Name;"