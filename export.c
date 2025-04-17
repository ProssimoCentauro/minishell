/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:42:27 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/17 14:25:28 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *var, t_data *data)
{
	int		error;
	size_t	i;

	error = 0;
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (forbidden_symbols(var[i]) && var[i] != '+')
			error = 1;
		if (var[i] == '+' && var[i + 1] != '=')
			error = 1;
		i++;
	}
	if (ft_isalpha(var[0]) == 0 || error == 1)
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->exit_status = 1;
		return ;
	}
	data->env = add_array(data, var);
	data->exit_status = 0;
}

void	print_line(char *str)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (*str != '=' && *str != '\0')
	{
		ft_putchar_fd(*str , STDOUT_FILENO);
		str++;
	}
	if (*str == '=')
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(str +1, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	print_sort_array(char **env, t_execute *info)
{
	char	*temp;
	int		n;
	int		b;

	n = 0;
	set_fd(info);
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
		print_line(env[n]);
		n++;
	}
	restore_fd(info);
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
		if (var[n] == '+')
			break ;
		if (var[n] == '\0')
			return ;
		n++;
	}
	while (ft_strncmp(env[i], var, n) != 0 && \
	(env[i][n + 1] != '=' || env[i][n + 1] != '\0'))
		i++;
	temp = env[i];
	if (var[n] == '+')
	{
		env[i] = ft_strjoin(get_export_variable(var), "=");
		env[i] = ft_strjoin(env[i], get_value(temp));
		env[i]= ft_strjoin(env[i], get_value(var));
	}
	else
		env[i] = ft_strdup(var);
	free(temp);
}

void	ft_export(char **var, t_data *data, t_execute *info)
{
	char	**copy;
	char	*value;
	extern char	**environ;

	if (var && *var)
	{
		while (*var)
		{
			value = ft_getenv(get_export_variable(*var), data->env);
			if (!value)
				add_env(*var, data);
			else if (ft_getenv(get_export_variable(*var), data->env))
			{
				change_env(data->env, *var);
				data->exit_status = 0;
			}
			var++;
		}
		environ = data->env;
		return ;
	}
	copy = copy_array(data->env);
	print_sort_array(copy, info);
	data->exit_status = 0;
	//free_array(copy);
}
