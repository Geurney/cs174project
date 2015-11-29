#!/bin/bash
make
/etc/init.d/mysql restart > /dev/null
mysql -u root --password="cs174\$" -e "DROP FUNCTION IF EXISTS SUM_HE; CREATE AGGREGATE FUNCTION SUM_HE RETURNS STRING SONAME 'udf.so';"
