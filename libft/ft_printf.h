/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:54:12 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/01/06 22:30:10 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_arg
{
	char	*flags;
	char	*width;
	char	*precision;
	char	*c;
	int		printed;
}	t_arg;

int		isthere(char input, char *set);
char	*strcreator(const char *input, char *set);
void	print_all(const char *input, va_list *arguments, t_arg *arg);
void	print_string(va_list *arguments, t_arg *arg);
void	handle_width(int len, char c);
void	print_numbers(va_list *arguments, t_arg *arg, va_list *copy);
int		lookforlen(va_list *arguments, char *c);
int		countlenint(va_list *arguments);
int		countlenunsigned(va_list *arguments, int d);
int		countlenpointer(va_list *arguments);
int		findmaxmin(int i1, int i2, char indicator);
void	print_char(va_list *arguments, t_arg *arg);
void	ft_putnbr(long long number, char *c, t_arg *arg, int numlen);
void	putnbrbase_unsigned(unsigned int number, char *c, int fd);
void	putnbrbase_long(long unsigned number);
void	print_esanum(va_list *arguments, t_arg *arg, va_list *copy);
void	free_arg(t_arg *arg);
int		ft_printf(const char *input, ...);
void	createlist(t_arg *arg);
void	handle_flags_num(long long number, t_arg *arg, int len, int numlen);
void	handle_minint(t_arg *arg, int len);
void	add_esanum_flags(long long number, t_arg *arg);
void	add_decimal_flags(long long number, t_arg *arg);

#endif
