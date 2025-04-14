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

int	len_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	int				len;

	len = 0;
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	while (info != NULL)
	{
		if (info->d_type == DT_REG || info->d_type == 0)
			if (check_corrispondency(str, info->d_name) == 0)
			len ++;
		info = readdir((curr_dir));
	}
	closedir(curr_dir);
	return (len);
}

char	**find_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	char			**results;
	int				len;

	len = len_wildcards(str);
	if (len == 0)
		return (NULL);
	results = malloc((len + 1) * (sizeof(char *)));
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	len = 0;
	while (info != NULL)
	{
		if (info->d_type == DT_REG || info->d_type == 0)
		{
			if (check_corrispondency(str, info->d_name) == 0)
			{
				if (info->d_name[0] != '.')
				{
					results[len] = ft_strdup(info->d_name);
					len++;
				}
			}
		}
		info = readdir((curr_dir));
	}
	results[len] = NULL;
	closedir(curr_dir);
	return (results);
}
