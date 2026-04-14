#ifndef DB_MANAGMENT_H
#define DB_MANAGMENT_H


#include <sqlite3.h>
#include <stdio.h>
#include <sys/stat.h>

#define DB "db/vm.db"

/*
    shemas table vm_state db

    id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, poste TEXT, pub_key TEXT

*/

int db_initialisation(void);

#endif