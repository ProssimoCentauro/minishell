#include "minishell.h"


int	check_corrispondency(char *str, char *file)
{
	char	c;

	while (*str != '*')
	{
		if (*str != *file)
			return (1);
		else if (!(*str))
			return (0);
		str++;
		file++;
	}
	while (*(str + 1) == '*')
		str++;
	c = *(str + 1);
	while (*file != c)
	{
		if (!(*file))
			return (1);
		file++;
	}
	return (check_corrispondency(str + 1, file));
}

char	**find_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	char			**results;

	results = NULL;
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	while (info != NULL)
	{
		if (info->d_type == DT_REG || info->d_type == 0)
			if (check_corrispondency(str, info->d_name) == 0)
				printf("%s\n", info->d_name);
		info = readdir((curr_dir));
	}
	return (results);
}
