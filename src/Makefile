main: main.c paillier.c
	gcc -I/usr/include/mysql -o main $(mysql_config --cflags) main.c $(mysql_config --libs) paillier.c -L/lib -lgmp -lmysqlclient -lz
