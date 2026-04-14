#include "ssh_identification.h"

int	error_msg(int err, const char *f_name)
{
	if (err == ERR_1)
		printf("getenv error in %s\n", f_name);
	if (err == ERR_2)
		printf("open error in %s\n", f_name);
	if (err == ERR_3)
		printf("gnl error in %s\n", f_name);
	if (err == ERR_4)
		printf("split error in %s\n", f_name);
	if (err == ERR_5)
		printf("substr error in %s\n", f_name);
	if (err == ERR_6)
		printf("public key not found in %s\n", f_name);
	return (err);
}

int	get_pub_key(t_id *id, int fd_pub_key)
{
	char	*line;
	char	**split;

	line = get_next_line(fd_pub_key);
	if (!line)
		return (error_msg(ERR_3, __func__));
	split = ft_split(line, 32);
	free(line);
	if (!split)
		return (error_msg(ERR_4, __func__));
	id->pub_key = ft_substr(split[2], 0, ft_strlen(split[2]) - 1);
	clean_split(split);
	if (!id->pub_key)
		return (error_msg(ERR_5, __func__));
	return (OK);
}

int	get_user(t_id *id, int fd_user)
{
	char	*line;
	char	**split;

	while ((line = get_next_line(fd_user)))
	{
		if (!line)
			return (error_msg(ERR_3, __func__));
		split = ft_split(line, 32);
		free(line);
		if (!split)
			return (error_msg(ERR_4, __func__));
		if (!strcmp(id->pub_key, split[1]))
		{
			if (split[2])
			{
				id->user = ft_substr(split[2], 0, ft_index_of(split[2], '@'));
				id->machine = ft_substr(split[2], ft_index_of(split[2], '@') + 1,
						ft_strlen(&split[2][ft_index_of(split[2], '@')]) - 2);
				clean_split(split);
				return (OK);
			}
		}
		clean_split(split);
	}
	return (error_msg(ERR_6, __func__));
}

int	ssh_identification(t_id *id)
{
	int		r;
	int		fd_pub_key;
	int		fd_user;
	char	*pub_key_path;

	pub_key_path = getenv("SSH_USER_AUTH");
	if (!pub_key_path)
		return (error_msg(ERR_1, __func__));
	fd_pub_key = open(pub_key_path, O_RDONLY);
	if (fd_pub_key < 0)
		return (error_msg(ERR_2, __func__));
	r = get_pub_key(id, fd_pub_key);
	close(fd_pub_key);
	if (r != OK)
		return (r);
	fd_user = open("/home/network/.ssh/authorized_keys", O_RDONLY);
	if (fd_user < 0)
	{
		free(id->pub_key);
		return (error_msg(ERR_2, __func__));
	}
	r = get_user(id, fd_user);
	close(fd_user);
	if (r != OK)
		free(id->pub_key);
	return (r);
}
