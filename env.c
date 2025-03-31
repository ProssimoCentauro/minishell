#include "minishell.h"

void ft_env(char **env)
{
	while (*env)
	{
		if (*(ft_getenv(*env, env)) != '\0')
			printf("%s\n", *env);
		env++;
	}
}

t_data	*analize_env(char **env)
{
	t_data	*env_variables;
	int		n;
	int		i;

	env_variables = malloc(sizeof(t_data));
	env_variables->variables = malloc(1024 * sizeof(char *));
	n = 0;
	i = 0;
	while (env[n])
	{
		i = 0;
		while (env[n][i] != '=' && env[n][i] != '\0')
		{
			i++;
		}
		env_variables->variables[n] = ft_substr(env[n], 0, i);
		printf("%s\n", env_variables->variables[n]);
		n++;
	}
	return (env_variables);
}