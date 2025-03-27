#include "minishell.h"

void ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

void sort_array(char **env)
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
			if (ft_strncmp(env[n], env[b], ft_strlen(env[b])) > 0)
			{
				temp = env[n];
				env[n] = env[b];
				env[b] = temp;

			}
			b++;
		}
		printf("declare -x %s\n", env[n]);
		n++;
	}
}

void	ft_export(char **env, char **var)
{
	(void) var;
	sort_array(env);
}