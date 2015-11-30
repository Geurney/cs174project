#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "paillier.h"
#include <mysql/mysql.h>

#define HOST "54.153.80.124"
#define USER "MaLi"
#define PASSWORD "cs174$"
#define DB "project"
#define PORT 3306
#define BIT_LENGTH 128
#define BASE 32
#define BUFFER_SIZE 300

paillier_pubkey_t *pubkey;
paillier_prvkey_t *privkey;
MYSQL *conn;

void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "Error: %s\n", mysql_error(conn));
  mysql_close(conn);
  return;
}

void print_result(MYSQL *conn) {
  MYSQL_RES *result = mysql_store_result(conn);

  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  MYSQL_FIELD *field;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      int i;
      for(i = 0; i < num_fields; i++) 
      { 
          if (i == 0) 
          {              
             while(field = mysql_fetch_field(result)) 
             {
                printf("%s\t", field->name);
             }
             
             printf("\n");           
          }
          if (i == num_fields - 1 && row[i]) {
            printf("%lu\t", decrypt(row[i], BASE, pubkey, privkey));
          }
          else if (row[i]) {
             printf("%s\t", row[i]);
          } else {
              printf("NULL\t"); 
          }
      } 
  }
  printf("\n");
  mysql_free_result(result);
}

char execute(MYSQL *conn, char* query) {
  if (mysql_query(conn, query)) {
     finish_with_error(conn);
     return 0;
  }
  else {
    print_result(conn);
    return 1;
  }
}

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
     sprintf(query, "INSERT INTO Employees VALUES(%s, %s, '%s')", params[0], params[1], params[2]);
     printf("%s\n", query);

     if (mysql_query(conn, query)) {
        finish_with_error(conn);
     }
}

void handle_select(char input[]) {
     char query[BUFFER_SIZE];
     if(input[7] == '*') {
        strcpy(query, "SELECT * FROM Employees");
        printf("%s\n", query);
        execute(conn, query);
     } else {
         if (input[7] != 'S' && input[7] != 'A') {
             strcpy(query, "SELECT * FROM Employees WHERE id=");
             strcat(query, &input[7]);
             printf("%s\n", query);
             execute(conn, query);
         } else if(input[7] == 'S') {
 	    if (strchr(input, 'P') != NULL) {
	        strcpy(query, "SELECT age, SUM_HE(salary) FROM Employees");
	        strcat(query, &input[10]);
  	        printf("%s\n", query);     
                execute(conn, query);
            } else {
	        strcpy(query, "SELECT SUM_HE(salary) FROM Employees");
                strcat(query, &input[10]);
  	        printf("%s\n", query);     
                execute(conn, query);
            }
         } else {
 	    if (strchr(input, 'P') != NULL) {
                strcpy(query, "SELECT age, COUNT(*) FROM Employees");
                strcat(query, &input[10]);
  	        printf("%s\n", query);     
                if (mysql_query(conn, query)) {
                  finish_with_error(conn);
                  return;
                }
                MYSQL_RES *res;		
                MYSQL_ROW row;		
                res = mysql_store_result(conn);		
                int age[100] = {0};
                int count[100] = {0};
                int i = 0;
                while(row = mysql_fetch_row(res))		
                {	
                   age[i] = atoi(row[0]);
                   count[i] = atoi(row[1]);	
                   i++;
                }		
                mysql_free_result(res);
                int j = 0;
                for(j = 0; j < i; j++) {
               //    printf("%d\n", count[j]);
                }
               
 	        strcpy(query, "SELECT SUM_HE(salary) FROM Employees");
                strcat(query, &input[10]);
  	        printf("%s\n", query);     

                if (mysql_query(conn, query)) {
                  finish_with_error(conn);
                  return;
                }
                
                res = mysql_store_result(conn);		
                unsigned long int salary[100] = {0};
                i = 0;
                while(row = mysql_fetch_row(res))		
                {	 
                   if(row[0] != NULL) {
                     salary[i++] = decrypt(row[0], BASE, pubkey, privkey);	
                   }
                }		
                mysql_free_result(res);
                if (i == 0) {
                    printf("NULL\n");
                    return;
                }
                printf("Age\tCount\tSum\tAvg\n");
                for (j = 0; j < i; j++) {
                  float avg = (float)salary[j]/count[j];
                  printf("%d\t%d\t%lu\t%f\n", age[j], count[j], salary[j], avg); 
                }

            } else {
                strcpy(query, "SELECT COUNT(*) FROM Employees");
                strcat(query, &input[10]);
  	        printf("%s\n", query);     
                if (mysql_query(conn, query)) {
                  finish_with_error(conn);
                  return;
                }
                MYSQL_RES *res;		
                MYSQL_ROW row;		
                res = mysql_store_result(conn);		
                int count[100] = {0};
                int i = 0;
                while(row = mysql_fetch_row(res))		
                {	
                   count[i++] = atoi(row[0]);	
                }		
                mysql_free_result(res);
                int j = 0;
                for(j = 0; j < i; j++) {
                   printf("%d\n", count[j]);
                }
               
 	        strcpy(query, "SELECT SUM_HE(salary) FROM Employees");
                strcat(query, &input[10]);
  	        printf("%s\n", query);     

                if (mysql_query(conn, query)) {
                  finish_with_error(conn);
                  return;
                }
                
                res = mysql_store_result(conn);		
                unsigned long int salary[100] = {0};
                i = 0;
                while(row = mysql_fetch_row(res))		
                {	 
                   if(row[0] != NULL) {
                     salary[i++] = decrypt(row[0], BASE, pubkey, privkey);	
                   }
                }		
                mysql_free_result(res);
                if (i == 0) {
                    printf("NULL\n");
                    return;
                }
                printf("Count\tSum\tAvg\n");
                for (j = 0; j < i; j++) {
                  float avg = (float)salary[j]/count[j];
                  printf("%d\t%lu\t%f\n", count[j], salary[j], avg); 
                }
            }
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
    FILE *f = fopen("key", "r");
    if (f == NULL) {
      printf("Key file is missing. Please generate key...\n");
      return 0;
    }
    printf("Read key from file...\n");
    char line[128];
    fgets(line, sizeof(line), f);
    pubkey = paillier_pubkey_from_hex(line);
    fgets(line, sizeof(line), f);
    privkey = paillier_prvkey_from_hex(line, pubkey);
    fclose(f);

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
