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
	return (prev);
}

void	cd(char **str, char *curr_dir)
{
	int	n;

	n = 0;
	if (!str || !str[n])
		return ;
	if (ft_strncmp(str[n], "..", ft_strlen("..")) == 0)
	{
		check_error(chdir(get_previous_directory(curr_dir)));
	}
	else
	{
		check_error(chdir(str[n]));
	}
}