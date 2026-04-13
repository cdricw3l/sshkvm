#ifndef SSH_IDENTIFICATION_H
#define SSH_IDENTIFICATION_H

#define ERR_1           -1
#define ERR_2           -2
#define ERR_3           -3
#define ERR_4           -4
#define ERR_5           -5
#define ERR_6           -6
#define OK              0

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "../libft_v2/libft.h"
#include "../getnextline/get_next_line.h"


typedef struct s_id
{
	char *user;
	char *pub_key;

} t_id;

int	ssh_identification(t_id *id);

#endif