#include "minishell.h"

char	*export_join(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (str);
		if (str[i] == '+')
			break ;
		i++;
	}
	if (str[i] == '+')
	{
		temp = ft_strjoin(get_export_variable(str), "=");
		str = ft_strjoin(temp, get_value(str));
		free(temp);
	}
	return (str);
}
