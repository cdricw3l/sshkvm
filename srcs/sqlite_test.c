#include <sqlite3.h>
#include <stdio.h>

#define DB "db/vm.db"

int sqlite_error(sqlite3 *db)
{
    printf("%s", sqlite3_errmsg(db));
    sqlite3_close(db);
    return (1);
}


int main(void)
{

    int r;
    sqlite3 *db;
    sqlite3_stmt *st;

    if(sqlite3_open_v2(DB, &db, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
        return(sqlite_error(db));
    else
        printf("Connexion OK!\n");

    char *sql = "SELECT * FROM test;";
    if((r = sqlite3_prepare_v2(db,sql,-1, &st ,NULL)) != SQLITE_OK)
        return(sqlite_error(db));
    else
        printf("Statment ready OK! %d\n", r);
    ;
    while((r = sqlite3_step(st)) == SQLITE_ROW)
    {
       char *str = (char *)sqlite3_column_text(st,0);
       if (str)
            printf("str: %s\n",str);
    }
    sqlite3_close(db);   
    return(0);
}