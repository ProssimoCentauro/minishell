/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:55:50 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/01/06 22:22:33 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	free_arg(t_arg *arg)
{
	free (arg -> c);
	arg -> c = NULL;
	free (arg -> flags);
	arg -> flags = NULL;
	free (arg -> precision);
	arg -> precision = NULL;
	free (arg -> width);
	arg -> width = NULL;
}

void	createlist(t_arg *arg)
{
	arg -> c = NULL;
	arg -> flags = NULL;
	arg -> precision = NULL;
	arg -> width = NULL;
	arg -> printed = 0;
}

int	findmaxmin(int i1, int i2, char indicator)
{
	if (indicator == 'm')
	{
		if (i1 < i2)
			return (i1);
		return (i2);
	}
	if (indicator == 'M')
	{
		if (i1 > i2)
			return (i1);
	}
	return (i2);
}
