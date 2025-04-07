/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:53 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/02/11 14:49:51 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	execute_pipe(char *av, char **env, int fd)
// {
// 	char	*path;
// 	char	**com_flags;
// 	int		pid;
// 	int		pipefd[2];

// 	check_errors(pipe(pipefd));
// 	check_errors(pid = fork());
// 	if (pid == 0)
// 	{
// 		com_flags = ft_split(av, ' ');
// 		path = findpath(env, com_flags[0]);
// 		check_errors(dup2(fd, STDIN_FILENO));
// 		close(fd);
// 		close(pipefd[0]);
// 		check_errors(dup2(pipefd[1], STDOUT_FILENO));
// 		check_errors(execve(path, com_flags, NULL));
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(pipefd[1]);
// 		close(fd);
// 	}
// 	return (pipefd[0]);
// }

void	final_process(t_execute *info, char **env)
{
	char	*path;
	char	**com_flags;
	int		pid;

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
		if (info->file_out != 0)
		{
			dup2(info->file_out, STDOUT_FILENO);
			close(info->file_out);
		}
		check_error(execve(path, com_flags, NULL), info->com, NULL);
	}
	else
		wait(NULL);
}

void	execve_cmd(t_execute *info, char **env)
{
	check_error(info->file_in, info->com, info->filename);
	if (info->file_in == -1)
		return ;
	if (info->pipe == 0)
		final_process(info, env);
	if (info->file_in != 0)
		close(info->file_in);
	if (info->file_out != 0)
		close(info->file_out);
	return ;
	// while ((ac - n) != 2)
	// {
	// 	pipe = execute_com(av[n], env, pipe);
	// 	n++;
	// }
	// final_process(fd2, pipe, av[ac - 2], env);
}
