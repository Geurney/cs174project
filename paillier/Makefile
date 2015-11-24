all: paillier genkey

paillier: main.c paillier.c
	gcc main.c paillier.c -o paillier -L/lib -lgmp

genkey: genkey.c paillier.c
	gcc genkey.c paillier.c -o genkey -L/lib -lgmp

clean:
	$(rm) genkey
	$(rm) paillier
