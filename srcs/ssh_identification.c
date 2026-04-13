#include "ssh_identification.h"

int error_msg(int err, const char *f_name)
{
	if(err == ERR_1)
		printf("getenv error in %s\n",f_name);
	if(err == ERR_2)
		printf("open error in %s\n",f_name);
	if(err == ERR_3)
		printf("gnl error in %s\n",f_name);
	if(err == ERR_4)
		printf("split error in %s\n", f_name);
	if(err == ERR_5)
		printf("substr error in %s\n", f_name);
	if(err == ERR_6)
		printf("public key not found in %s\n", f_name);
	return (err);
}

int get_pub_key(t_id *id)
{
	int		fd;
	char	*line;
	char	**split;
	char	*pub_key_path;

	pub_key_path = getenv("SSH_USER_AUTH");
	if (!pub_key_path)
		return (error_msg(ERR_1, __func__));
	fd = open(pub_key_path, O_RDONLY);
	if (fd < 0)
		return (error_msg(ERR_2, __func__));
	line = get_next_line(fd);
	close(fd);
	if (!line)
		return (error_msg(ERR_3, __func__));
	split = ft_split(line, 32);
	free(line);
	if (!split)
		return (error_msg(ERR_4, __func__));
	id->pub_key = ft_substr(split[2], 0, ft_strlen(split[2]) - 1);
	clean_split(split);
	if(!id->pub_key)
		return (error_msg(ERR_5, __func__));
	return (OK);
}

int get_user(t_id *id)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open("/home/network/.ssh/authorized_keys", O_RDONLY);
	if (fd < 0)
	{
		free(id->pub_key);
		return (error_msg(ERR_2, __func__));
	}
	while ((line = get_next_line(fd)))
	{
		if(!line)
		{
			close(fd);
			return (error_msg(ERR_3, __func__));
		}
		split = ft_split(line, 32);
		free(line);
		if(!split)
		{
			close(fd);
			return (error_msg(ERR_4, __func__));
		}
		if (!strcmp(id->pub_key, split[1]))
		{
			if (split[2])
			{
				id->user = ft_substr(split[2], 0, ft_strlen(split[2]) - 1);
				close(fd);
				clean_split(split);
				return (OK);
			}
		}
		clean_split(split);
	}
	close(fd);
	return (error_msg(ERR_6, __func__));
}

int	ssh_identification(t_id *id)
{
	int r;

	r = get_pub_key(id);
	if(r != OK)
		return (r);
	r = get_user(id);
	if(r != OK)
		return (r);
	return (OK);
}