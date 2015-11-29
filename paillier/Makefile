all: paillier genkey encrypt decrypt

paillier: main.c paillier.c
	gcc main.c paillier.c -o paillier -lgmp

genkey: genkey.c paillier.c
	gcc genkey.c paillier.c -o genkey -lgmp

encrypt: encrypt.c paillier.c
	gcc encrypt.c paillier.c -o encrypt -lgmp

decrypt: decrypt.c paillier.c
	gcc decrypt.c paillier.c -o decrypt -lgmp

clean:
	rm genkey paillier encrypt decrypt
