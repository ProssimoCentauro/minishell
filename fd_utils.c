#include "minishell.h"

void	set_fd(t_execute *info)
{
	if (info->file_in != 0)
	{
		dup2(info->file_in, STDIN_FILENO);
		close(info->file_in);
	}
	if (info->file_out != 1)
	{
		dup2(info->file_out, STDOUT_FILENO);
		close(info->file_out);
	}
}

void	restore_fd(t_execute *info)
{
	dup2(info->std_in, STDIN_FILENO);
	dup2(info->std_out, STDOUT_FILENO);
}