#include "db_managment.h"

static int sqlite_error(sqlite3 *db)
{
    int err;

    err = sqlite3_errcode(db);
    printf("code %d: %s", err, sqlite3_errmsg(db));
    if(sqlite3_close(db) != SQLITE_OK)
        printf("code %d: %s", err, sqlite3_errmsg(db));
    return (err);
}

static int create_folder(char *folder_name)
{
    int r;

    r = mkdir(folder_name, 0755);
    if(r != 0)
        perror("mkir error:");
    return (r);
}

int db_initialisation(void)
{
    sqlite3 *db;
    char *err;
    char *sql;

    if(create_folder("db") != 0)
        return (-1);
    if(sqlite3_open_v2(DB, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
        return(sqlite_error(db));
    else
        printf("Connexion DB OK!\n");
    sql = "CREATE TABLE IF NOT EXISTS vm_state("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT," 
                    "user TEXT," 
                    "poste TEXT," 
                    "pub_key TEXT,"
                    "date TEXT DEFAULT CURRENT_DATE );";
    if(sqlite3_exec(db,sql,0,0, &err)!= SQLITE_OK)
        return(sqlite_error(db));
    if(sqlite3_close(db) != SQLITE_OK)
        return(sqlite_error(db));
    return(SQLITE_OK);
}