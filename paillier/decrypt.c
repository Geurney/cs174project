#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "paillier.h"
#define BASE 32

paillier_pubkey_t *pubkey;
paillier_prvkey_t *privkey;


int main() {
        FILE *f = fopen("key", "r");
        if (f == NULL) {
          printf("Cannot find Key file...\n");
        }
        if (f != NULL) {
          printf("Read key from file...\n");
          char line[128];
          fgets(line, sizeof(line), f);
          pubkey = paillier_pubkey_from_hex(line);
          fgets(line, sizeof(line), f);
          privkey = paillier_prvkey_from_hex(line, pubkey);
          fclose(f);
        }
        printf("Public key: %s\n", paillier_pubkey_to_hex(pubkey));

        char input[100];
        while(1) {
          printf( "Enter a ciphertext: ");
          scanf("%s", input);
  	  printf("Decrypting result: ");
          printf("%lu\n", decrypt(input, BASE, pubkey, privkey));
        }

        paillier_freepubkey(pubkey);
        paillier_freeprvkey(privkey);
        return 0;
}

