#include "minishell.h"

void check_error(int n, char *comm, char *arg)
{
	if (n == 127)
	{
		ft_putstr_fd(comm, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		g_exit_status = 127;
	}
	else if (n == -1)
	{
		ft_putstr_fd(comm, STDERR_FILENO);
		if (comm != NULL)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		if (arg)
			ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		g_exit_status = 1;
	}
}
