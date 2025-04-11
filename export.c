/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:42:27 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/11 15:42:30 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char ***env, char *var)
{
	int		error;
	size_t	i;

	error = 0;
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (forbidden_symbols(var[i]))
			error = 1;
		i++;
	}
	if (ft_isalpha(var[0]) == 0 || error == 1)
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	*env = add_array(*env, var);
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

void	sort_array(char **env)
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
	while (ft_strncmp(env[i], var, n) != 0 && \
	(env[i][n + 1] != '=' || env[i][n + 1] != '\0'))
		i++;
	temp = env[i];
	env[i] = var;
	free(temp);
}

void	ft_export(char ***env, char **var)
{
	char	**copy;
	char	*value;

	if (var && *var)
	{
		while (*var)
		{
			value = ft_getenv(*var, *env);
			if (ft_strlen(value) == 0)
			{
				free(value);
				add_env(env, *var);
			}
			else if (ft_getenv(*var, *env))
				change_env(*env, *var);
			var++;
		}
		return ;
	}
	copy = copy_array(*env);
	sort_array(copy);
	//free_array(copy);
}
