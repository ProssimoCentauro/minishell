/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:15:26 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/01/06 22:16:02 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	countlenint(va_list *arguments)
{
	int	number;
	int	len;

	number = va_arg(*arguments, int);
	len = 0;
	if (number == -2147483648)
		return (11);
	if (number <= 0)
	{
		len++;
		number *= -1;
	}
	while (number > 0)
	{
		len++;
		number /= 10;
	}
	return (len);
}

int	countlenpointer(va_list *arguments)
{
	int					len;
	long unsigned int	number;

	len = 0;
	number = va_arg(*arguments, long unsigned int);
	if (number == 0)
		return (5);
	while (number > 0)
	{
		len++;
		number /= 16;
	}
	return (len);
}

int	countlenunsigned(va_list *arguments, int d)
{
	int				len;
	unsigned int	number;

	len = 0;
	number = va_arg(*arguments, unsigned int);
	if (number == 0)
		return (1);
	while (number > 0)
	{
		len++;
		number /= d;
	}
	return (len);
}

int	lookforlen(va_list	*arguments, char *c)
{
	int	len;

	len = 0;
	if (*c == 'd' || *c == 'i')
		len = countlenint(arguments);
	if (*c == 'p')
		len = countlenpointer(arguments);
	else
	{
		if (*c == 'u')
			len = countlenunsigned(arguments, 10);
		if (*c == 'x' || *c == 'X')
			len = countlenunsigned(arguments, 16);
	}
	return (len);
}
