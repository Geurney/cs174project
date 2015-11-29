all: genkey encrypt decrypt main

genkey: genkey.c paillier.c
	gcc genkey.c paillier.c -o genkey -lgmp

encrypt: encrypt.c paillier.c
	gcc encrypt.c paillier.c -o encrypt -lgmp

decrypt: decrypt.c paillier.c
	gcc decrypt.c paillier.c -o decrypt -lgmp

main: main.c paillier.c
	gcc -I/usr/include/mysql -o main $(mysql_config --cflags) main.c $(mysql_config --libs) paillier.c -lgmp -lmysqlclient -lz

clean:
	rm main genkey encrypt decrypt
