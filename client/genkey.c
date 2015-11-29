#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "paillier.h"
#define BASE 32

int main() {
    paillier_pubkey_t *pubkey;
    paillier_prvkey_t *privkey;
    FILE *f = fopen("key", "r");
    if (f != NULL) {
        char yn;
        while(1) {
            printf("Key file exists, do you want overrite?[y/n]");
            scanf("%s", &yn);
            if (yn == 'n') {
                exit(1);
 	    }           
            if (yn == 'y') {
                fclose(f);
                break;
            }
        } 
    }
    FILE *p = fopen("key", "w");
    if (p == NULL) {
         printf("Please run with sudo!\n");
         exit(1);
     }
    printf("Generate new key...\n");
    generate_key(128, &pubkey, &privkey);
    fprintf(p, "%s\n", paillier_pubkey_to_hex(pubkey));
    fprintf(p, "%s\n", paillier_prvkey_to_hex(privkey));
    fprintf(p, "%d\n", BASE);
    fclose(p);
    
    FILE *q = fopen("pubkey","w");
    if (q == NULL) {
         printf("Please run with sudo!\n");
         exit(1);
    }
    fprintf(q, "%s\n", paillier_pubkey_to_hex(pubkey));
    fprintf(q, "%d\n", BASE);
    fclose(q);

    paillier_freepubkey(pubkey);
    paillier_freeprvkey(privkey);
    return 0;
}
