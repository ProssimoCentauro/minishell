/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:55:06 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/01/06 21:47:05 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	isthere(char input, char *set)
{
	while (*set)
	{
		if (input == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*strcreator(const char *input, char *set)
{
	int		len;
	char	*str;

	len = 0;
	while (isthere(input[len], set) == 1)
	{
		len++;
	}
	if (len != 0)
		str = ft_substr(input, 0, len);
	else
	{
		str = malloc (sizeof(char));
		*str = '\0';
	}
	return (str);
}

void	handle_width(int len, char c)
{
	while (len > 0)
	{
		write (1, &c, 1);
		len--;
	}
}

void	handle_flags_num(long long number, t_arg *arg, int len, int numlen)
{
	char	*precision;
	char	*flags;

	precision = arg -> precision;
	flags = arg -> flags;
	if (isthere('-', flags) == 0 && isthere('0', flags) == 0)
		handle_width(ft_atoi(arg -> width) - len, ' ');
	if (*arg -> c == 'd' || *arg -> c == 'i' || *arg -> c == 'u')
		add_decimal_flags(number, arg);
	if (*arg -> c == 'p' || *arg -> c == 'x' || *arg -> c == 'X')
		add_esanum_flags(number, arg);
	if (isthere('-', flags) == 0 && isthere('0', flags) == 1 && !precision)
	{
		if ((int)number < 0 && ((*arg -> c == 'd') || (*arg -> c == 'i')))
		{
			write (1, "-", 1);
			number *= -1;
		}
		handle_width(ft_atoi(arg -> width) - len, '0');
	}
	else if (isthere('-', flags) == 0 && isthere('0', flags) == 1 && precision)
		handle_width(ft_atoi(arg -> width) - len, ' ');
	ft_putnbr(number, arg -> c, arg, numlen);
	if (isthere('-', flags) == 1)
		handle_width(ft_atoi(arg -> width) - len, ' ');
}

void	handle_minint(t_arg *arg, int len)
{
	char	*flags;
	char	*precision;

	flags = arg -> flags;
	precision = arg -> precision;
	if (isthere('-', flags) == 0 && isthere('0', flags) == 0)
		handle_width(ft_atoi(arg -> width) - len, ' ');
	write(1, "-", 1);
	if (isthere('-', flags) == 0)
		handle_width(ft_atoi(arg -> width) - len, ' ');
	if (isthere('-', flags) == 0 && isthere('0', flags) == 1 && !(precision))
		handle_width(ft_atoi(arg -> width) - len, '0');
	if (arg -> precision)
		handle_width(ft_atoi(precision) - 11, '0');
	write(1, "2147483648", 10);
	if (isthere('-', arg -> flags) == 1)
		handle_width(ft_atoi(arg -> width) - len, ' ');
}
