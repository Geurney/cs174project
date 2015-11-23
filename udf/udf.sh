#!bin/bash
mysql -u root --password="cs174\$" -e "DROP FUNCTION IF EXISTS calc_distance_udf; CREATE FUNCTION calc_distance_udf RETURNS REAL SONAME 'calc_distance_udf.so';  SELECT calc_distance_udf(1.0, 2.0, 3.0, 4.0);"
