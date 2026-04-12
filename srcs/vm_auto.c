# include "./vm_auto.h"
# include <sqlite3.h>

char *get_pub_key(void)
{
	int fd;
	char *pub_key_path;
	char *line;
	char **split;
	char *key;

	pub_key_path = getenv("SSH_USER_AUTH");
	if(!pub_key_path)	
	{
		printf("path error\n");
		return (NULL);
	}
	fd = open(pub_key_path, O_RDONLY);
	if(fd < 0)
	{
		perror("read error");
		return (NULL);
	}
	else
		printf("fileDescriptor %d\n", fd);
	
	line = get_next_line(fd);
	if(!line)
	{
		close(fd);
		return (NULL);
	}
	split = ft_split(line, 32);
	free(line);
	if(!split)
	{
		close(fd);
		return (NULL);
	}
	key = ft_strdup(split[2]);
	clean_split(split);
	return (key);
}


// int main(void)
// {

// 	char *pub_key;
// 	int db;
// 	sqlite3 *ppdb;

// 	pub_key = get_pub_key();
// 	if(!pub_key)
// 		return (1);
// 	printf("key: %s\n", pub_key);
// 	db = sqlite3_open(DB, &ppdb);
// 	printf("voici db %d\n", db);
// 	free(pub_key);
// 	return(0);

// }

// int main(void)
// {

// 	int db;
// 	sqlite3 *ppdb;

// 	db = sqlite3_open(DB, &ppdb);
// 	assert(db == SQLITE_OK);
// 	return(0);

// }



int check_and_dispatch(char *arg)
{
	int i;
	int code;
	char **args;

	code = DISPATCH_ERR;
	args = ft_split(arg, 32);
	if(!args)
	{
		printf("Argument processing error\n");
		return (code);
	}
	i = 0;
	while (args[i])
	{
		if(i > 1)
			code = DISPATCH_ERR;
		if(!strcmp(args[i], "vmc"))
			code =  CREATE_VM;
		else if(!strcmp(args[i], "vms"))
			code = SNAPSHOT_VM;
		else if(!strcmp(args[i], "vmr"))
			code = RESTART_VM;
		else if(!strcmp(args[i], "vm_off"))
			code = SHUTDOWN_VM;
		i++;
	}
	clean_split(args);	
	return(code);
}

int main(void)
{
	char *arg;
	char *pub_key;
	int dispatch_code;

	arg = getenv("SSH_ORIGINAL_COMMAND");
	if(!arg)
	{
		printf("You need to give an argument\n");
		return (1);
	}
	
	pub_key = get_pub_key();
	if(!pub_key)
		return (1);
	printf("key: %s\n", pub_key);
	dispatch_code = check_and_dispatch(arg);
	printf("voici %d\n", dispatch_code);
	if(dispatch_code == DISPATCH_ERR)
		printf("Argument processing error\n");
	else if( dispatch_code == CREATE_VM)
		printf("You are asking a vm creation\n");
	else if( dispatch_code == RESTART_VM)
		printf("You are asking for a  restart vm\n");
	else if( dispatch_code == SNAPSHOT_VM)
		printf("You are asking for a  snapshot vm\n");
	else if( dispatch_code == SHUTDOWN_VM)
		printf("You are asking for a  shutdown  of vm\n");
	return (0);
}
