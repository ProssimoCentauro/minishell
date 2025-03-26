/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorterfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:56:42 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/01/07 11:08:07 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_string(va_list *arguments, t_arg *arg)
{
	char	*str;
	int		len;
	char	*precision;
	int		i;

	precision = arg -> precision;
	str = va_arg(*arguments, char *);
	if (!str)
		str = "(null)";
	if (precision)
		len = findmaxmin((ft_atoi(precision)), ft_strlen(str), 'm');
	else
		len = ft_strlen(str);
	i = ft_atoi(arg -> width) - len;
	arg -> printed += findmaxmin(len, i + len, 'M');
	if (isthere('-', arg -> flags) == 0)
		handle_width(i, ' ');
	while (len-- > 0)
		write(1, str++, 1);
	if (isthere('-', arg -> flags) == 1)
		handle_width(i, ' ');
}

void	print_numbers(va_list *arguments, t_arg *arg, va_list *copy)
{
	long long	number;
	int			len;
	int			numlen;
	char		*precision;

	precision = arg -> precision;
	len = lookforlen(copy, arg -> c);
	numlen = len;
	number = va_arg(*arguments, long long);
	if (precision && ft_atoi(precision) == 0 && (int)number == 0)
		len = 0;
	else if (precision)
		len = findmaxmin(ft_atoi(precision), numlen, 'M');
	if (isthere('+', arg -> flags) == 1 || isthere(' ', arg -> flags) == 1)
		if ((int)number >= 0 && *(arg -> c) != 'u')
			len ++;
	arg -> printed += findmaxmin(len, ft_atoi(arg -> width), 'M');
	if ((int)number == -2147483648 && *(arg -> c) != 'u')
	{
		handle_minint(arg, len);
		return ;
	}
	handle_flags_num(number, arg, len, numlen);
}

void	print_char(va_list *arguments, t_arg *arg)
{
	char	c;
	int		i;
	int		len;

	c = va_arg(*arguments, int);
	if (arg -> precision)
		len = findmaxmin(ft_atoi(arg -> precision), 1, 'm');
	else
		len = 1;
	i = ft_atoi(arg -> width) - len;
	arg -> printed += findmaxmin(len, i + len, 'M');
	if (isthere('-', arg -> flags) == 0)
		handle_width(i, ' ');
	while (len-- > 0)
		write(1, &c, 1);
	if (isthere('-', arg -> flags) == 1)
		handle_width(i, ' ');
}

void	print_esanum(va_list *arguments, t_arg *arg, va_list *copy)
{
	long long			number;
	int					len;
	int					numlen;
	char				*precision;

	precision = arg -> precision;
	len = lookforlen(copy, arg -> c);
	numlen = len;
	number = va_arg(*arguments, long long);
	if (precision && ft_atoi(precision) == 0 && number == 0)
		len = 0;
	else if (*arg -> c == 'p' && number == 0)
		len = 5;
	else if (precision)
		len = findmaxmin(ft_atoi(precision), len, 'M');
	if (isthere('#', arg -> flags) == 1 && (unsigned int)number != 0)
	{
		if (*(arg -> c) != 'p')
			len += 2;
	}
	else if (*arg -> c == 'p' && number != 0)
		len += 2;
	arg -> printed += findmaxmin(len, ft_atoi(arg -> width), 'M');
	handle_flags_num(number, arg, len, numlen);
}
