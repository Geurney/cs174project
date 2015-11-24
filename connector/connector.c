#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "cs174$"
#define DB "test"
#define PORT 3306

#define INSERT_CLAUSE(id, age, salary) "INSERT INTO Employees VALUES(" #id "," #age "," #salary ")"
static char *socket_name = NULL;
static unsigned int flags = 0;

int main()
{
    MYSQL *conn;
    
    conn = mysql_init(NULL);
    
    if(!(mysql_real_connect(conn, HOST, USER, PASSWORD, DB, PORT, NULL, 0)))
    {
        fprintf(stderr, "Error : %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    printf("Connection opened\n");

    MYSQL_RES *res;
    MYSQL_ROW row;

    char *query = "INSERT INTO users VALUES(27, 45, 'txt')";
    printf("%s\n", query);
    mysql_query(conn, query);
    if (mysql_error(conn)[0] != '\0') {
	printf("%s\n", mysql_error(conn));
    }

    query = "SELECT * FROM users";
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
