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

#include "pipex.h"

int	execute_com(char *av, char **env, int fd)
{
	char	*path;
	char	**com_flags;
	int		pid;
	int		pipefd[2];

	check_errors(pipe(pipefd));
	check_errors(pid = fork());
	if (pid == 0)
	{
		com_flags = ft_split(av, ' ');
		path = findpath(env, com_flags[0]);
		check_errors(dup2(fd, STDIN_FILENO));
		close(fd);
		close(pipefd[0]);
		check_errors(dup2(pipefd[1], STDOUT_FILENO));
		check_errors(execve(path, com_flags, NULL));
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		close(fd);
	}
	return (pipefd[0]);
}

void	final_process(int fd2, int pipe, char *av, char **env)
{
	char	*path;
	char	**com_flags;
	int		pid;

	check_errors(pid = fork());
	if (pid == 0)
	{
		com_flags = ft_split(av, ' ');
		path = findpath(env, com_flags[0]);
		check_errors(dup2(pipe, STDIN_FILENO) == 0);
		check_errors(dup2(fd2, STDOUT_FILENO));
		close(pipe);
		close(fd2);
		check_errors(execve(path, com_flags, NULL));
	}
	else
	{
		close(fd2);
		close(pipe);
	}
}

int	main(int ac, char **av, char **env)
{
	int		pipe;
	int		fd1;
	int		fd2;
	int		n;

	if (ac < 5)
		return (ft_putstr_fd("Error\n", 2), 0);
	pipe = 0;
	here_doc(ac, av, env);
	fd1 = open(av[1], O_RDWR);
	n = 3;
	fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (check_errors(fd2) == 0)
		exit (1);
	if (check_errors(fd1) == 1)
		pipe = execute_com(av[2], env, fd1);
	while ((ac - n) != 2)
	{
		pipe = execute_com(av[n], env, pipe);
		n++;
	}
	final_process(fd2, pipe, av[ac - 2], env);
	exit(0);
}
