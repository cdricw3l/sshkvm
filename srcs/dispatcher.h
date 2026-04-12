#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "../libft_v2/libft.h"
#include "../getnextline/get_next_line.h"

#define DB "db/vm.db"

#define CREATE_VM       0
#define RESTART_VM      1
#define SNAPSHOT_VM     2
#define SHUTDOWN_VM     3
#define DISPATCH_ERR    4

#endif
