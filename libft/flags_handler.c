/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:24:22 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/01/06 19:35:06 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	add_esanum_flags(long long number, t_arg *arg)
{
	if (*arg -> c == 'p')
	{
		if (number != 0)
			write(1, "0x", 2);
	}
	else if (isthere('#', arg -> flags) == 1 && (unsigned int)number != 0)
	{
		if (*arg -> c == 'x')
			write(1, "0x", 2);
		else if (*arg -> c == 'X')
			write(1, "0X", 2);
	}
}

void	add_decimal_flags(long long number, t_arg *arg)
{
	if (*arg -> c == 'd' || *arg -> c == 'i')
	{
		if (isthere('+', arg -> flags) == 1 && (int)number >= 0)
			write(1, "+", 1);
	}
	if (isthere('+', arg -> flags) == 0 && isthere(' ', arg -> flags) == 1)
	{
		if ((int) number >= 0)
			write(1, " ", 1);
	}
}
