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
	if(line)
	{
		split = ft_split(line, 32);
		if(!split)
		{
			free(line);
			close(fd);
			return (NULL);
		}
		free(line);
	}
	close(fd);
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

int main(void)
{

	int db;
	sqlite3 *ppdb;

	db = sqlite3_open(DB, &ppdb);
	assert(db == SQLITE_OK);
	return(0);

}
