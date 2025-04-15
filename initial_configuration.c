/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_configuration.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:18:05 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/15 12:45:30 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initial_configuration(t_data *data, t_execute *info, char **env)
{
	char	*bash_level;
	int		new_level;

	setup_signal_handlers();
	data->env = copy_array(env);
	info->pid = 0;
	info->pipe_fd = 0;
	data->exit_status = 0;
	bash_level = ft_getenv("SHLVL", env);
	new_level = ft_atoi(bash_level) + 1;
	free(bash_level);
	bash_level = malloc(8);
	ft_strlcpy(bash_level, "SHLVL=", 7);
	bash_level = ft_strjoin(bash_level, ft_itoa(new_level));
	ft_export(ft_split(bash_level, ' '), data);
}

