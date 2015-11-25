udf: udf.c
	gcc -I/usr/include/mysql $(mysql_config --cflags) -shared -fPIC -o  /usr/lib/mysql/plugin/udf.so udf.c
clean:
	rm /usr/lib/mysql/plugin/udf.so
