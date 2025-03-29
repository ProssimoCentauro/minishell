#include "minishell.h"

void	add_env(char **env, char **var)
{
	int		n;

	n = 0;
	while (env[n])
		n++;
	while (*var)
	{

		env[n] = *var;
		var++;
		n++;
	}
	env[n] = NULL;
}

void	print_line(char *str)
{
	printf("declare -x ");
	while (*str != '=' && *str != '\0')
	{
		printf("%c", *str);
		str++;
	}
	if (*str == '=')
		printf("=\"%s\"\n", str + 1);
	else
		printf("\n");
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
		print_line(env[n]);
		n++;
	}
}
void	change_env(char **env, char *var)
{
	int		n;
	int		i;
	char	*temp;

	n = 0;
	i = 0;
	while (var[n] != '=')
	{
		if (var[n] == '\0')
			return ;
		n++;
	}
	while (ft_strncmp(env[i], var, n + 1) != 0)
		i++;
	temp = env[i];
	env[i] = var;
	free(temp);
}

void	ft_export(char **env, char **var)
{
	char	**copy;

	if (*var)
	{
		if (ft_getenv(*var, env) == NULL)
			add_env(env, var);
		else if (ft_getenv(*var, env))
			change_env(env, *var);
		return ;
	}
	copy = copy_array(env);
	sort_array(copy);
	free_array(copy);
}