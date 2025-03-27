#include "minishell.h"

char	*get_previous_directory(char *curr_dir)
{
	char	*end;
	char	*prev;
	int		len;

	len = ft_strlen(curr_dir);
	end = curr_dir + len;
	while (*end != '/')
	{
		end--;
		len--;
	}
	prev = ft_substr(curr_dir, 0, len);
	if (*prev == '\0')
	{
		*prev = '/';
		*(prev + 1) = '\0';
	}
	return (prev);
}

void	cd(char **str, char *curr_dir)
{
	int		n;
	char	*new_dir;

	n = 0;
	if (!str || !str[n])
	{
		new_dir = ft_strjoin("/nfs/homes/", getenv("USER"));
		chdir(new_dir);
		return (free_array(str), free(new_dir));
	}
	if (str[1] != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
	}
	if (ft_strncmp(str[n], "..", ft_strlen("..")) == 0)
	{
		new_dir = get_previous_directory(curr_dir);
		check_error(chdir(new_dir));
		return (free_array(str), free(new_dir));
	}
	else
		check_error(chdir(str[n]));
	free_array(str);
}