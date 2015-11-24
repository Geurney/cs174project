#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "paillier.h"

int main() {
	
	paillier_pubkey_t *pubkey;
	paillier_prvkey_t *privkey;
	printf("Generating %d bit key\n", BIT_LENGTH);
	generate_key(&pubkey, &privkey);

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

	return 0;
}
