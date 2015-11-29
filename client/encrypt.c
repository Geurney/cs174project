#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "paillier.h"

paillier_pubkey_t *pubkey;
int base;

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
          fgets(line, sizeof(line), f);
          base = atoi(line);
          fclose(f);
        }        
        printf("Public key: %s\n", paillier_pubkey_to_hex(pubkey));
        printf("Base: %d\n", base);
	
        int input;
        while(1) {
          printf( "Enter a number: ");
          if (scanf("%d", &input) == 0) {
            break;
          }
	  paillier_ciphertext_t ciphertext_input;
          mpz_init(ciphertext_input.c);
	  printf("Encrypting inputs...\n");
          encrypt(&ciphertext_input, input, pubkey);
          char * encrypted_input = mpz_get_str(NULL, base, ciphertext_input.c);
	  printf("%s\n", encrypted_input);
        }

        paillier_freepubkey(pubkey);
	return 0;
}
