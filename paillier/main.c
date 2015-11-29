#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "paillier.h"
#define BASE 32

paillier_pubkey_t *pubkey;
paillier_prvkey_t *privkey;


int main() {
        FILE *f = fopen("key", "r");
        if (f != NULL) {
          printf("Read key from file...\n");
          char line[128];
          fgets(line, sizeof(line), f);
          pubkey = paillier_pubkey_from_hex(line);
          fgets(line, sizeof(line), f);
          privkey = paillier_prvkey_from_hex(line, pubkey);
          fclose(f);
        } else {
            FILE *p = fopen("key", "w");
            if (p == NULL) {
                printf("Please run with sudo!\n");
                exit(1);
            }
            printf("Generate new key...\n");
            generate_key(128, &pubkey, &privkey);
            fprintf(p, "%s\n", paillier_pubkey_to_hex(pubkey));
            fprintf(p, "%s\n", paillier_prvkey_to_hex(privkey));
            fclose(p);
  	}
        
        printf("Public key: %s\n", paillier_pubkey_to_hex(pubkey));
        printf("Privte Key: %s\n", paillier_prvkey_to_hex(privkey));

	int a = 20;
	int b = 60;
	printf("Example inputs: %d + %d = %d\n", a, b, a + b);

	paillier_ciphertext_t ciphertext_a;
	paillier_ciphertext_t ciphertext_b;
        mpz_init(ciphertext_a.c);
	mpz_init(ciphertext_b.c);

	printf("Encrypting inputs...\n");
  	encrypt(&ciphertext_a, a, pubkey);
  	encrypt(&ciphertext_b, b, pubkey);
        char * encrypted_a = mpz_get_str(NULL, BASE, ciphertext_a.c);
        char * encrypted_b = mpz_get_str(NULL, BASE, ciphertext_b.c);
	printf("%d is : %s\n", a, encrypted_a);
	printf("%d is : %s\n", b, encrypted_b);

        printf("Mulitplication...\n");
        char * encrypted_result = encrypted_mul(encrypted_a, encrypted_b, BASE, pubkey);
        printf("%s\n", encrypted_result);

	printf("Decrypting result: ");
	printf("%lu\n", decrypt(encrypted_result, BASE, pubkey, privkey));

        paillier_freepubkey(pubkey);
        paillier_freeprvkey(privkey);
	return 0;
}
