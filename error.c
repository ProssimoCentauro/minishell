/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:16:37 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/12 11:58:37 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error(int n, char *comm, char *arg, t_data *data)
{
	if (n == -1)
	{
		ft_putstr_fd(comm, STDERR_FILENO);
		if (comm != NULL)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		if (arg)
			ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		data->exit_status = 1;
	}
}

void	command_error(char *comm, t_data *data)
{
	ft_putstr_fd(comm, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
	data->exit_status = 127;
	exit(127);
}

void	check_dup(int n, int fd)
{
	if (n == -1)
	{
		close(fd);
		exit(1);
	}
}
