#!/bin/bash
/etc/init.d/mysql restart > /dev/null
make
mysql -u root --password="cs174\$" -e "DROP FUNCTION IF EXISTS SUM_HE; CREATE AGGREGATE FUNCTION SUM_HE RETURNS STRING SONAME 'udf.so'; USE project; SELECT SUM_HE(salary) FROM Employees WHERE id > 6;"
