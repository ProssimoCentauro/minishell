#include "minishell.h"

int	array_len(char **array)
{
	int		n;
	int		len;

	n = 0;
	len = 0;
	while (array && array[n])
	{
		if (array[n][0] != '\0')
			len++;
		n++;
	}
	return (len);
}

char	**copy_array(char **array)
{
	char	**copy;
	int		n;
	int		len;

	len = array_len(array);
	copy = malloc((len + 1) * (sizeof(char *)));
	n = 0;
	len = 0;
	while (array[n])
	{
		if (array[n][0] != '\0')
		{
			copy[len] = ft_strdup(array[n]);
			len++;
		}
		n++;
	}
	copy[len] = NULL;
	return (copy);
}

char	**add_array(t_data *data, char *var)
{
	int		len;
	int		i;
	char	**temp;

	len = array_len(data->env);
	temp = data->env;
	i = 0;
	data->env = malloc((len + 2) * (sizeof(char *)));
	while (temp[i])
	{
		data->env[i] = ft_strdup(temp[i]);
		i++;
	}
	data->env[i] = ft_strdup(var);
	data->env[i + 1] = NULL;
	return(data->env);
}

char	**sort_array(char **env)
{
	char	*temp;
	int		n;
	int		b;

	n = 0;
	while (env[n])
	{
		b = n + 1;
		while (env[b])
		{
			if (ft_strncmp(env[n], env[b], ft_strlen(env[b]) + 1) > 0)
			{
				temp = env[n];
				env[n] = env[b];
				env[b] = temp;
			}
			b++;
		}
		n++;
	}
	return (env);
}