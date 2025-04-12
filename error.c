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

void	check_error(int n, char *comm, char *arg)
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
		g_exit_status = 1;
	}
	else
		g_exit_status = 0;
}

void	command_error(char *comm)
{
	ft_putstr_fd(comm, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Command not found\n", STDERR_FILENO);
	g_exit_status = 127;
}
