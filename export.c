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
	int		i;

	n = 0;
	while (env[n])
	{
		b = n + 1;
		i = 0;
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
		printf("declare -x ");
		while (env[n][i] != '=' && env[n][i] != '\0')
		{
			 printf("%c", env[n][i]);
			 i++;
		}
		if (env[n][i] == '=')
		{
			printf("=\"%s\"\n", env[n] + i + 1);
		}
		n++;
	}
}

void	ft_export(char **env, char **var)
{
	int		n;
	char	**copy;

	(void) var;
	copy = calloc(1024, sizeof(char *));
	n = 0;
	while (env[n])
	{
		copy[n] = ft_strdup(env[n]);
		n++;
	}
	copy[n] = NULL;
	sort_array(copy);
	free_array(copy);
}