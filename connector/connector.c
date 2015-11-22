#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

static char *host_name = "localhost";
static char *user_name = "root";
static char *password = "cs174$";
static char *db_name = "mytest";
static unsigned int port_num = 3306;
static char *socket_name = NULL;
static unsigned int flags = 0;

int main()
{
    MYSQL *conn;
    
    conn = mysql_init(NULL);
    
    if(!(mysql_real_connect(conn, host_name, user_name, password, db_name, port_num, socket_name, flags)))
    {
        fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    printf("Connection opened\n");
    mysql_close(conn);
    return 0;
}
