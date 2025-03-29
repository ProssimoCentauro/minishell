#include "minishell.h"

int	check(char *str)
{
	long long	number;
	int			i;
	// int			sign;

	number = 0;
	// sign = 1;
	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		// sign *= -1;
	}
	if (!str[i])
		return (0);
	while (str[i++])
	{
		if (str[i - 1] < '0' || str[i - 1] > '9')
			return (0);
		number = (number * 10) + (str[i - 1] - '0');
		// if ((number * sign) > 2147483647 || (number * sign) < -2147483648)
		// 	return (0);
	}
	return (1);
}

void	ft_exit(char	**exit_status)
{
	if (*(exit_status + 1) != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	if (check(*exit_status) == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(*exit_status, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		printf("exit\n");
		exit(2);
		return ;
	}
	printf("exit\n");
	exit(ft_atoi(*exit_status));
}