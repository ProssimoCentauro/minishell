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
	c = *(str + 1);
	while (*file != c)
	{
		if (!(*file))
			return (1);
		file++;
	}
	return (0 + check_corrispondency(str + 1, file));
}

char	**find_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	char			**results;
	int				q;

	q = 0;
	results = NULL;
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	while (info != NULL)
	{
		if (info->d_type == DT_REG)
			if (check_corrispondency(str, info->d_name) == 0)
				q++;
		info = readdir((curr_dir));
	}
	return (results);
}
