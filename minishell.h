#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

void	ft_echo(char** str);
void	cd(char **str, char *curr_dir);
void	check_error(int n);
void	free_array(char **str);
void	pwd();
void	ft_env(char **env);
void	ft_export(char **env, char **var);
void	ft_exit();

#endif