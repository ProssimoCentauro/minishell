#include "minishell.h"

void	pwd()
{
	char	*buf;

	buf = NULL;
	ft_printf("%s\n", getcwd(buf, 1024));
}