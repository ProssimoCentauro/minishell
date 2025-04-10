/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:53 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/07 00:58:22 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipe(t_execute *info, char **env)
{
	char	*path;
	char	**com_flags;
	int		pid;
	int		pipefd[2];

	pipe(pipefd);
	info->pid  += 1;
	print_info(info);
	pid = fork();
	if (pid == 0)
	{
		com_flags = info->args;
		path = findpath(env, com_flags[0]);
		dup2(info->file_in, STDIN_FILENO);
		if (info->file_in != 0)
			close(info->file_in);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (!path)
			check_error(127, info->com, NULL);
		execve(path, com_flags, NULL);
	}
	close(pipefd[1]);
	if (info->pipe_fd != 0)
		close(info->pipe_fd);
	info->pipe_fd = pipefd[0];
}

void	final_process(t_execute *info, char **env)
{
	char	*path;
	char	**com_flags;
	int		pid;

	info->pid += 1;
	print_info(info);
	pid = fork();
	if (pid == 0)
	{
		com_flags = info->args;
		path = findpath(env, com_flags[0]);
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
		if (!path)
			check_error(127, info->com, NULL);
		execve(path, com_flags, NULL);
	}
	wait(NULL);
}

void	execve_cmd(t_execute *info, char **env)
{
	check_error(info->file_in, info->com, info->filename);
	if (info->file_in == -1)
		return ;
	if ((info->delimiter == AND && g_exit_status != 0) || (info->delimiter == OR && g_exit_status == 0))
		return ;
	if (info->pipe_fd != 0)
		{
			info->file_in = info->pipe_fd;
			info->pipe_fd = 0;
		}
	if (info->pipe == 0)
		final_process(info, env);
	else
		execute_pipe(info, env);
	if (info->file_in != 0)
		close(info->file_in);
	if (info->file_out != 1)
		close(info->file_out);
}
