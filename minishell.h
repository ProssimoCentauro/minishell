#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct	s_data
{
	char	**variables;
}	t_data;

extern char	**environment;

void	ft_echo(char** str);
void	cd(char **str, char *curr_dir);
void	check_error(int n, char *comm, char *arg);
void	free_array(char **str);
void	pwd();
void	ft_env(char **env);
void	ft_export(char **env, char **var);
void	ft_exit();
t_data	*analize_env(char **env);
char	**copy_array(char **array);
char	*ft_getenv(char *variable, char **env);

#endif