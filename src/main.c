#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "paillier.h"
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "cs174$"
#define DB "project"
#define PORT 3306
#define BIT_LENGTH 128
#define BASE 32
#define BUFFER_SIZE 300

paillier_pubkey_t *pubkey;
paillier_prvkey_t *privkey;
MYSQL *conn;

void handle_insert(char input[]) {
     char * pch;
     pch = strtok(input, " ");
     pch = strtok(NULL, " ");
     char* params[3];
     params[0] = pch;
     pch = strtok(NULL, " ");
     params[1] = pch;
     pch = strtok(NULL, " ");

     paillier_ciphertext_t ciphertext;
     mpz_init(ciphertext.c);
     encrypt(&ciphertext, atoi(pch), pubkey);
     params[2] = mpz_get_str(NULL, BASE, ciphertext.c);

     char query[BUFFER_SIZE];
     strcpy(query, "INSERT INTO Employees VALUES(");
     strcat(query, params[0]);
     strcat(query, ",");
     strcat(query, params[1]);
     strcat(query, ",'");
     strcat(query, params[2]);
     strcat(query, "')");
     printf("%s\n", query);

     mysql_query(conn, query);
     if (mysql_error(conn)[0] != '\0') {
         printf("%s\n", mysql_error(conn));
     }
}

void handle_select(char input[]) {
     char query[BUFFER_SIZE];
     if(input[7] == '*') {
         strcpy(query, "SELECT * FROM Employees");
     } else {
         if (input[7] != 'S' && input[7] != 'A') {
             strcpy(query, "SELECT * FROM Employees WHERE id=");
             strcat(query, &input[7]);
             printf("%s\n", query);

             mysql_query(conn, query);
             if (mysql_error(conn)[0] != '\0') {
                 printf("%s\n", mysql_error(conn));
                 return;
             }  
             MYSQL_RES *res;
             MYSQL_ROW row;
             res = mysql_store_result(conn);
             while(row = mysql_fetch_row(res))
             {
                printf("%s\t%s\t%lu\n", row[0], row[1], decrypt(row[2], BASE, pubkey, privkey));
             }
             mysql_free_result(res);
         } else if(input[7] == 'S') {
 	    if (strchr(input, 'P') != NULL) {
	        strcpy(query, "SELECT age, SUM_HE(salary) FROM Employees");
	     } else {
	       strcpy(query, "SELECT SUM_HE(salary) FROM Employees");
	     }
	     strcat(query, &input[10]);
	     printf("%s\n", query);     
         } else {
  	    if (strchr(input, 'P') != NULL) {
	        strcpy(query, "SELECT age, AVG(salary) FROM Employees");
	     } else {
	       strcpy(query, "SELECT AVG(salary) FROM Employees");
	     }
	     strcat(query, &input[10]);
	     printf("%s\n", query);     
         }
     }
}

void handle_exit() {
     printf( "\nBye!\n");
}

void handle_unknown() {
     printf( "\nBad query!\n");
}

int main()
{
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
        generate_key(BIT_LENGTH, &pubkey, &privkey);
        fprintf(p, "%s\n", paillier_pubkey_to_hex(pubkey));
        fprintf(p, "%s\n", paillier_prvkey_to_hex(privkey));
        fclose(p);
    }

    conn = mysql_init(NULL);
    if(!(mysql_real_connect(conn, HOST, USER, PASSWORD, DB, PORT, NULL, 0)))
    {
        fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    printf("Connection opened\n");

    char input[BUFFER_SIZE];
    while(1) {
      printf( "Enter a query: ");
      fgets(input, 300, stdin);
     
      switch(input[0])
      {
           case 'I' : 
                handle_insert(input);
                break;
           case 'S' :
                handle_select(input);
                break;
           case 'e' :
                handle_exit();
		paillier_freepubkey(pubkey);
		paillier_freeprvkey(privkey);
                return 0;
           default : handle_unknown();
      }
    }

    paillier_freepubkey(pubkey);
    paillier_freeprvkey(privkey);
    return 0;
}
