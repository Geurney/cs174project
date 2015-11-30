#!/bin/bash
make
/etc/init.d/mysql restart > /dev/null
echo "Creating Project Database and SUM_HE Function ..."
mysql -u root --password="cs174\$" -e "DROP DATABASE IF EXISTS project; CREATE DATABASE project; USE project; CREATE TABLE Employees(id integer, age integer, salary TEXT NOT NULL, PRIMARY KEY (id)); DROP FUNCTION IF EXISTS SUM_HE; CREATE AGGREGATE FUNCTION SUM_HE RETURNS STRING SONAME 'udf.so';" &> /dev/null
