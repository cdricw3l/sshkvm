#include "dispatcher.h"

int	check_and_dispatch(char *arg)
{
	int		i;
	int		code;
	char	**args;

	code = DISPATCH_ERR;
	args = ft_split(arg, 32);
	if (!args)
		return (code);
	i = 0;
	while (args[i])
	{
		if (i > 1)
			code = DISPATCH_ERR;
		if (!strcmp(args[i], "vmc"))
			code = CREATE_VM;
		else if (!strcmp(args[i], "vms"))
			code = SNAPSHOT_VM;
		else if (!strcmp(args[i], "vmr"))
			code = RESTART_VM;
		else if (!strcmp(args[i], "vm_off"))
			code = SHUTDOWN_VM;
		else if (!strcmp(args[i], "help"))
			code = HELP;
		i++;
	}
	clean_split(args);
	return (code);
}

void	ft_print_help(void)
{
	printf("Usage:\n");
	printf("  -vmc   Create a virtual machine\n");
	printf("  -vmr   Reboot a virtual machine\n");
	printf("  -vms   Create a snapshot of a virtual machine\n");
	printf("  -vmsd  Shutdown a virtual machine\n");
	printf("  -help  Display this help message\n");
}

int	main(void)
{
	t_id	id;
	int		err;
	char	*arg;
	int		dispatch_code;

	if((err = db_initialisation()) != SQLITE_OK)
		return (err);
	if (ssh_identification(&id) != OK)
	{
		printf("Identification error\n");
		return (1);
	}
	else
	{
		printf("User: %s\n", id.user);
		printf("Key: %s\n", id.pub_key);
	}
	arg = getenv("SSH_ORIGINAL_COMMAND");
	if (!arg)
	{
		printf("You need to give an argument\n");
		ft_print_help();
		return (1);
	}
	
	dispatch_code = check_and_dispatch(arg);
	if (dispatch_code == DISPATCH_ERR)
		printf("Argument processing error\n");
	else if (dispatch_code == CREATE_VM)
		printf("You are asking a vm creation\n");
	else if (dispatch_code == RESTART_VM)
		printf("You are asking for a  restart vm\n");
	else if (dispatch_code == SNAPSHOT_VM)
		printf("You are asking for a  snapshot vm\n");
	else if (dispatch_code == SHUTDOWN_VM)
		printf("You are asking for a  shutdown  of vm\n");
	else if (dispatch_code == HELP)
		ft_print_help();
	
	free(id.pub_key);
	free(id.user);
	return (0);
}
