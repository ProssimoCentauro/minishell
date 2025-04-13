#include "minishell.h"

void	pwd(t_data *data)
{
	char	*buf;

	buf = NULL;
	ft_printf("%s\n", getcwd(buf, 1024));
	data->exit_status = 0;
}