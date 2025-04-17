#include "minishell.h"

void	pwd(t_data *data, t_execute *info)
{
	char	*buf;

	buf = NULL;
	set_fd(info);
	ft_putstr_fd(getcwd(buf, 1024), 2);
	restore_fd(info);
	data->exit_status = 0;
}