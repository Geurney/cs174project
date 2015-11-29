udf: udf.c
	gcc -I/usr/include/mysql -I/usr/include $(mysql_config --cflags) -shared -fPIC -o  /usr/lib/mysql/plugin/udf.so udf.c paillier.c -lgmp
clean:
	rm /usr/lib/mysql/plugin/udf.so
