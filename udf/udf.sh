#!/bin/bash
echo "Compiling..."
make clean > /dev/null
make > /dev/null
echo "Restart MySql..."
/etc/init.d/mysql restart > /dev/null
echo "Enter Client IP address:"
read IP
echo "Creating Project Database, granting MaLi@$IP and creating SUM_HE Function ..."
mysql -u root --password="cs174\$" -e "DROP DATABASE IF EXISTS project; CREATE DATABASE project; USE project; CREATE TABLE Employees(id integer, age integer, salary TEXT NOT NULL, PRIMARY KEY (id)); GRANT ALL ON project.* TO MaLi@'$IP' IDENTIFIED BY 'cs174\$'; DROP FUNCTION IF EXISTS SUM_HE; CREATE AGGREGATE FUNCTION SUM_HE RETURNS STRING SONAME 'udf.so';" &> /dev/null
