#include "minishell.h"

char	*quotes(char *str)
{
	char	*temp;

	if (!str)
		return (NULL);
	if (*str == 39)
	{
		temp = str;
		str = ft_substr(str, 1, ft_strlen(str) - 2);
		return (free(temp), str);
	}
	return (str);
}
