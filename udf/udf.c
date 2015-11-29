#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;/* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#if defined(MYSQL_SERVER)
#include <m_string.h>/* To get strmov() */
#else
/* when compiled as standalone */
#include <string.h>
#define strmov(a,b) stpcpy(a,b)
#define bzero(a,b) memset(a,0,b)
#define memcpy_fixed(a,b,c) memcpy(a,b,c)
#endif
#endif
#include <mysql.h>
#include <ctype.h>
   
#ifdef HAVE_DLOPEN

#if !defined(HAVE_GETHOSTBYADDR_R) || !defined(HAVE_SOLARIS_STYLE_GETHOST)
static pthread_mutex_t LOCK_hostname;
#endif
   
#include <math.h>
#include <gmp.h>
#include "paillier.h"

#define BASE 32

struct product_type
{
  paillier_pubkey_t *pubkey;
  int base;
  char *product;
};

/*****************Encrypted Aggregation SUM*******************/
my_bool SUM_HE_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
   if (args->arg_count != 1)
   {
      strcpy(message, "Encrypted Aggregation SUM requires one argument");
      return 1;
   }
   if (args->arg_type[0] != STRING_RESULT)
   {
      strcpy(message ,"Encrypted Aggregation SUM requires one string");
      return 1;
   }
   FILE *f = fopen("/home/ubuntu/cs174project/udf/key", "r");
   if (f == NULL) {
      strcpy(message ,"Cannot find key file");
      return 1;
   }
   struct product_type* data = (struct product_type*)malloc(sizeof(struct product_type));
   data->product = "1";
   char line[128];
   fgets(line, sizeof(line), f);
   data->pubkey = paillier_pubkey_from_hex(line);
   fgets(line, sizeof(line), f);
   data->base = atoi(line);
   fclose(f);

   initid->maybe_null = 1;
   args->maybe_null[0] = 1;
   initid->ptr = (char*)data;   
   return 0;
}

void SUM_HE_deinit(UDF_INIT* initid) {
   struct product_type* data = (struct product_type*)initid->ptr;
   if (data->product != NULL) {
     data->product = NULL;
   }
   paillier_freepubkey(data->pubkey);
   free((struct product_type*)initid->ptr);
}

void SUM_HE_clear(UDF_INIT *initid, char *is_null, char *error)
{
   struct product_type* data = (struct product_type*)initid->ptr;
   data->product = "1";
}

void SUM_HE_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
   struct product_type* data = (struct product_type*)initid->ptr;
   char * product = encrypted_mul(data->product, args->args[0], data->base, data->pubkey);
   data->product = product;
}

char *SUM_HE(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length,
                char *is_null, char *error) { 

   struct product_type* data = (struct product_type*)initid->ptr;
   if (data->product == "1") {
      *is_null = 1;
      *length = 0;
      return NULL;
   }
   *length = strlen(data->product);
   return data->product;
}


#endif /* HAVE_DLOPEN */
