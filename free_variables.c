#include "minishell.h"

int	is_a_free_variable(char *str, t_data *data)
{
	char	*value;

	while (*str)
	{
		if (forbidden_symbols(*str))
			return (0);
		if (*str == '=')
		{
			value = ft_getenv(str, data->env);
			if (!value)
				add_array(data->free_variables, str);
			else if (ft_getenv(str, data->env))
				change_env(data->free_variables, str);
			return (1);
		}
		str++;
	}
	return (0);
}