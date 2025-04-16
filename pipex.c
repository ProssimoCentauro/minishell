/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:53 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/15 12:51:32 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_execute *info, t_data *data)
{
	char	*path;
	char	**com_flags;

	com_flags = info->args;
	path = findpath(data->env, com_flags[0]);
	if (check_builtin(info, data) == 1)
		exit_and_free(data->exit_status, info, path);
	if (!path)
		if (execve(com_flags[0], com_flags, data->env) == -1)
			command_error(com_flags[0], data, info);
	execve(path, com_flags, data->env);
}

void	execute_pipe(t_execute *info, t_data *data)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	info->pid  += 1;
	pid = fork();
	if (pid == 0)
	{
		check_dup(dup2(info->file_in, STDIN_FILENO), info, pipefd[1]);
		dup2(pipefd[1], STDOUT_FILENO);
		close_fd(info->file_in, pipefd[1], pipefd[0]);
		execution(info, data);
	}
	close_fd(pipefd[1], info->pipe_fd, 0);
	info->pipe_fd = pipefd[0];
}

void	final_process(t_execute *info, t_data *data)
{
	int		pid;

	info->pid += 1;
	pid = fork();
	if (pid == 0)
	{
		check_dup(dup2(info->file_in, STDIN_FILENO), info, info->file_in);
		dup2(info->file_out, STDOUT_FILENO);
		close_fd(info->file_in, info->file_out, 0);
		execution(info, data);
	}
	waitpid(pid, &(data->exit_status), 0);
	if (info->file_in != 0)
		close(info->file_in);
}

void	execve_cmd(t_execute *info, t_data *data)
{
	if (info->file_in != -2)
		check_error(info->file_in, info->com, info->file, data);
	if (info->file_in == -2 || info->com == NULL)
		return ;
	if ((info->delimiter == AND && data->exit_status != 0) || (info->delimiter == OR && data->exit_status == 0))
		return ;
	if (info->pipe_fd != 0 )
	{
		info->file_in = info->pipe_fd;
		info->pipe_fd = 0;
		if (info->pipe == 0)
			final_process(info, data);
		else
			execute_pipe(info, data);
	}
	else if (info->pipe == 0)
	{
		if (check_builtin(info, data) == 0)
			final_process(info, data);
	}
	else if (info->pipe == 1)
		execute_pipe(info, data);
	close_fd(info->file_in, info->file_out, 0);
}
