#include "minishell.h"

char	**find_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	char			**results;

	(void) str;
	results = NULL;
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	while (info != NULL)
	{
		if (info->d_type == DT_REG)
			printf("%s\n", info->d_name);
		info = readdir((curr_dir));
	}
	return (results);
}