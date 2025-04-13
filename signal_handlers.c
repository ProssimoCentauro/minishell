#include "minishell.h"

void sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void setup_signal_handlers(void)
{
    struct sigaction sa;
    
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    
    struct sigaction sq;
    sq.sa_handler = SIG_IGN;
    sigemptyset(&sq.sa_mask);
    sq.sa_flags = 0;
    sigaction(SIGQUIT, &sq, NULL);
}
