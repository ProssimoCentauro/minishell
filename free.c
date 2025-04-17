/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:21:09 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/17 20:21:11 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		free (str[n]);
		n++;
	}
	free(str);
}

void	exit_and_free(int exit_status, char *com)
{
	free(com);
	exit(exit_status);
}
