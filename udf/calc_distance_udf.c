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
   
  my_bool summ_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
  void summ_deinit(UDF_INIT *initid);
  longlong summ(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
  void summ_clear(UDF_INIT *initid, char *is_null, char *error);
  void summ_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);


  my_bool summ_init(UDF_INIT *initid __attribute__((unused)),
                        UDF_ARGS *args __attribute__((unused)),
                        char *message __attribute__((unused)))
  {
    longlong* i; // create the variable
    *i = 0;                     // set it to a value
        
        // store it as a char pointer in the pointer variable
       // Make sure that you don`t run in typecasting troubles later!!
    initid->ptr = (char*)i;
        
        // check the arguments format
    if (args->arg_count != 1)
    {
         strcpy(message,"MyTest() requires one arguments");
         return 1;
    }
    if (args->arg_type[0] != INT_RESULT)
    {
      strcpy(message,"MyTest() requires an integer");
      return 1;
    }       
    return 0;    
  }

  void summ_clear(UDF_INIT *initid, char *is_null, char *error)
  {
        /* The clear function resets the sum to 0 for each new group
        Of course you have to allocate a longlong variable in the init 
        function and assign it to the pointer as seen above */
        *((longlong*)initid->ptr) = 0;
  }  

  void summ_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
  {
        // For each row the current value is added to the sum
        *((longlong*)initid->ptr) = *((longlong*)initid->ptr) + 
                                    *((longlong*)args->args[0]);
  } 

  longlong summ(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
  {
        // And in the end the sum is returned
        return *((longlong*)initid->ptr);
  }

  void summ_deinit(UDF_INIT *initid) {
    free(initid->ptr);
  }

/**********************************************/
   my_bool calc_distance_udf_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
   void calc_distance_udf_deinit(UDF_INIT *initid __attribute__((unused)));
   double calc_distance_udf(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)),
                     char* is_null __attribute__((unused)), char* error __attribute__((unused)));

   my_bool add_int_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
   void add_int_deinit(UDF_INIT *initid);
   longlong add_int(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

   my_bool add_int_init(UDF_INIT *initid __attribute__((unused)),
                        UDF_ARGS *args __attribute__((unused)),
                        char *message __attribute__((unused)))
   {
     if(!(args->arg_count == 2)) {
       strcpy(message, "Expected two arguments (a, b)");
       return 1;
     }
     args->arg_type[0] = INT_RESULT;
     args->arg_type[1] = INT_RESULT;
     return 0;
   }

   void add_int_deinit(UDF_INIT *initid __attribute__((unused)))
   {
     
   }


   longlong add_int(UDF_INIT *initid __attribute__((unused)), UDF_ARGS *args,
                    char *is_null __attribute__((unused)),
                    char *error __attribute__((unused)))
   {
     return *((longlong*)args->args[0]) + *((longlong*)args->args[1]);
   }

   
   my_bool calc_distance_udf_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
   {
     if(!(args->arg_count == 4)) {
       strcpy(message, "Expected four arguments (lat, lon, locate_lat, locate_lon");
       return 1;
     }
   
     args->arg_type[0] = REAL_RESULT;
     args->arg_type[1] = REAL_RESULT;
     args->arg_type[2] = REAL_RESULT;
     args->arg_type[3] = REAL_RESULT;
   
     return 0;
   }
   
   void calc_distance_udf_deinit(UDF_INIT *initid __attribute__((unused)))
   {
   
   }
   
   double calc_distance_udf(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)),
                     char* is_null __attribute__((unused)), char* error __attribute__((unused)))
   {
     double lat = *((double *)(args->args[0]));
     double lon = *((double *)(args->args[1]));
     double locate_lat = *((double *)(args->args[2]));
     double locate_lon = *((double *)(args->args[3]));
   
     lat = lat * M_PI / 180;
     lon = lon * M_PI / 180;
     locate_lat = locate_lat * M_PI / 180;
     locate_lon = locate_lon * M_PI / 180;
   
     return 3959 * acos(cos(lat) * cos(locate_lat) * cos(locate_lon - lon) + sin(lat) * sin(locate_lat));
   }
   


   #endif /* HAVE_DLOPEN */
