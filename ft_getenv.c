#include "minishell.h"

char	*get_value(char *str)
{
	int	n;

	n = 0;
	while (str[n] != '=')
	{
		if (str[n] == '\0')
			return ("\0");
		n++;
	}
	return (ft_substr(str, n + 1, ft_strlen(str) - n));
}

char	*ft_getenv(char *variable, char **env)
{
	char	*value;
	int		len;
	int		i;

	value = NULL;
	len = 0;
	i = 0;
	while (variable[len] != '=' && variable[len] != '\0')
		len++;
	while (env[i])
	{
		if (ft_strncmp(variable, env[i], len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
		{
			value = get_value(env[i]);
		}
		i++;
	}
	if (value && ft_strlen(value) == 0)
		return (ft_strdup(""));
	return (value);
}
