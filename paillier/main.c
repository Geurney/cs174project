#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "paillier.h"

paillier_pubkey_t *pubkey;
paillier_prvkey_t *privkey;


int main() {
        FILE *f = fopen("key.txt", "r");
        if (f != NULL) {
          printf("Read key from file...\n");
          char line[128];
          fgets(line, sizeof(line), f);
          pubkey = paillier_pubkey_from_hex(line);
          fgets(line, sizeof(line), f);
          privkey = paillier_prvkey_from_hex(line, pubkey);
          fclose(f);
        } else {
            FILE *p = fopen("key.txt", "w");
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
        
        printf("%s\n", paillier_pubkey_to_hex(pubkey));
        printf("%s\n", paillier_prvkey_to_hex(privkey));
/*
	int a = 20;
	int b = 60;
	paillier_plaintext_t *input2;
	printf("Generating inputs: %d + %d = %d\n", a, b, a + b);
	input2 = paillier_plaintext_from_ui(b);

	paillier_ciphertext_t ciphertext1;
	paillier_ciphertext_t ciphertext2;
	printf("Encrypting inputs:\n");
        mpz_init(ciphertext1.c);
	mpz_init(ciphertext2.c);

  	encrypt(&ciphertext1, a, pubkey);
        char * encrypted_salary = mpz_get_str(NULL, 32, ciphertext1.c);
        printf("%s\n", mpz_get_str(NULL, 32, ciphertext1.c));

        long unsigned int result =  decrypt(encrypted_salary, 32, pubkey, privkey);       
*/
/*	paillier_ciphertext_t cipher;
	mpz_init(cipher.c);
	mpz_set_str(cipher.c, encrypted_salary, 2);

	paillier_plaintext_t output;
	mpz_init(output.m);
	printf("Decrypting result: ");
	paillier_dec(&output, pubkey, privkey, &cipher);
	int result = mpz_get_ui(output.m);
	printf("%lu\n", result);
        
*/


/*
	printf("%lu\n", mpz_get_ui(ciphertext1.c));
	encrypt(&ciphertext2, b, pubkey);
	printf("%lu\n", mpz_get_ui(ciphertext2.c));

	paillier_ciphertext_t ciphertext3;
	mpz_init(ciphertext3.c);
	printf("Multiplication:\n");
	paillier_mul(pubkey, &ciphertext3, &ciphertext1, &ciphertext2);
	printf("%lu\n", mpz_get_ui(ciphertext3.c));

	paillier_plaintext_t output;
	mpz_init(output.m);
	printf("Decrypting result: ");
	paillier_dec(&output, pubkey, privkey, &ciphertext3);
	int result = mpz_get_ui(output.m);
	printf("%d\n", result);
*/
	return 0;
}
