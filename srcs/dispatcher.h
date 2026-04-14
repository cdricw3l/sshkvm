#ifndef DISPATCHER_H
#define DISPATCHER_H


#include <sqlite3.h>
#include "ssh_identification.h"
#include "db_managment.h"
#define NL printf("\n")


#define CREATE_VM       0
#define RESTART_VM      1
#define SNAPSHOT_VM     2
#define SHUTDOWN_VM     3
#define HELP            4
#define DISPATCH_ERR    5




#endif
