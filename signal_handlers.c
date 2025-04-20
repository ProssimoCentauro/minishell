#include "minishell.h"

void    sigquit_handler(int signum)
 {
     (void)signum;
     signal_manager(SIGQUIT, SIG_IGN);
     g_last_signal = SIGQUIT;
     kill(0, SIGQUIT);
     write(STDOUT_FILENO, "Quit\n", 5);
 }


void sigint_handler(int signum)
{
        extern  unsigned        long    rl_readline_state;

        (void)signum;
        write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        if (rl_readline_state & (RL_STATE_READCMD))
                rl_redisplay();
        g_last_signal = SIGINT;
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

void    heredoc_handler(int signum)
{
        (void)signum;
        rl_on_new_line();
        g_last_signal = SIGINT;
        exit(1);
}

void     signal_manager(int signum, void (*handler)(int signum))
{
        struct sigaction        sa;

        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sigaction(signum, &sa, NULL);
}
