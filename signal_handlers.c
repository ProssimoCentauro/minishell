/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:03:41 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/19 17:17:03 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	extern unsigned long	rl_readline_state;

	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (rl_readline_state & (RL_STATE_READCMD))
		rl_redisplay();
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;
	struct sigaction	sq;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sq.sa_handler = SIG_IGN;
	sigemptyset(&sq.sa_mask);
	sq.sa_flags = 0;
	sigaction(SIGQUIT, &sq, NULL);
}

void	handle_heredoc(int signum)
{
	(void)signum;
	rl_on_new_line();
	g_last_signal = SIGINT;
	exit(1);
}

int	signal_manager(int signum, void (*handler)(int s))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(signum, &sa, NULL) == -1)
		return (1);
	return (0);
}
