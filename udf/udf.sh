#!/bin/bash
mysql -u root --password="cs174\$" -e "DROP FUNCTION IF EXISTS SUM_HE; CREATE AGGREGATE FUNCTION SUM_HE RETURNS INTEGER SONAME 'udf.so'; USE test; SELECT SUM_HE(id) FROM users;"
