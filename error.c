#include "minishell.h"

void check_error(int n, char *comm, char *arg)
{
	if (n == -1)
	{
		ft_putstr_fd(comm, EXIT_FAILURE);
		ft_putstr_fd(": ", EXIT_FAILURE);
		ft_putstr_fd(arg, EXIT_FAILURE);
		if (arg)
			ft_putstr_fd(": ", EXIT_FAILURE);
		perror("");
		g_exit_status = 1;
	}
}