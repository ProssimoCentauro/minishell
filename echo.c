#include "minishell.h"

int	check_echo_flag(char *str)
{
	if (*str == '-')
		str++;
	else
		return (1);
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

void	ft_echo(char **str)
{
	int	n;
	int	newline;

	n = 0;
	newline = 1;
	if (!str || !str[n])
		return ;
	while (check_echo_flag(str[n]) == 0)
	{
		n++;
		newline = 0;
	}
	while (str[n])
	{
		ft_printf("%s", str[n]);
		if (str[n + 1] != NULL)
			ft_printf("%s", " ");
		n++;
	}
	if (newline == 1)
		ft_printf("%s", "\n");
	free_array(str);
}