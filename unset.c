#include "minishell.h"

void	ft_unset(char **var, t_data *data)
{
	int		i;
	int		len;
	//char	**temp;
	char	*to_delete;

	i = 0;
	if ((*var))
	{
		if (ft_getenv(*var, data->env))
		{
			len = ft_strlen(*var);
			while (ft_strncmp((data->env)[i], *var, len) != 0 && \
			(data->env[i][len + 1] != '=' || data->env[i][len + 1] != '\0'))
				i++;
			to_delete = data->env[i];
			data->env[i] = ft_strdup("");
			free(to_delete);
			//temp = *env;
			data->env = copy_array(data->env);
			//free_array(temp);
		}
	}
	data->exit_status = 0;
}