#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

static char *host_name = "localhost";
static char *user_name = "root";
static char *password = "cs174$";
static char *db_name = "test";
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

    MYSQL_RES *res;
    MYSQL_ROW row;
    char *query = "SELECT * FROM users";
    printf("%s\n", query);
    mysql_query(conn, query);
    res = mysql_store_result(conn);
    while(row = mysql_fetch_row(res))
    {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);

    printf("Connection closed\n");
    mysql_close(conn);
    return 0;
}
