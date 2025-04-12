/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:34:25 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/11 15:34:28 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_info(t_execute *info)
{
	info->com = NULL;
	info->file_in = 0;
	info->file_out = 1;
	info->pipe = 0;
	info->args = ft_calloc(1, sizeof(char *));
	info->file = NULL;
	info->delimiter = 0;
}

void	print_info(t_execute *info)
{
	int	i;

	i = 0;
	printf("com: %s\n", info->com);
	while (info->args[i])
	{
		printf("arg %d: %s\n", i, info->args[i]);
		i++;
	}
	printf("pipe: %d\n", info->pipe);
	printf("file in: %d\n", info->file_in);
	printf("file out: %d\n", info->file_out);
	printf("pipe fd: %d\n\n", info->pipe_fd);
}
