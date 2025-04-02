/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtodaro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:55 by rtodaro           #+#    #+#             */
/*   Updated: 2025/04/02 15:55:19 by rtodaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

  
 
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <dirent.h>
# include <sys/types.h>
  
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct	s_data
{
	char	**variables;
}	t_data;
  
typedef enum e_type
{
	NONE = 0,
	CMD = 1 << 1,
	LIMITER = 1 << 2,
	DELIMETER = 1 << 3,
	REDIRECT = 1 << 4,
	FILENAME = 1 << 5,
	AND = 1 << 6,
	OR = 1 << 7,
	IN = 1 << 8,
	OUT = 1 << 9,
	HEREDOC = 1 << 10,
	APPEND = 1 << 11,
	PIPE = 1 << 12,
	OPEN = 1 << 13,
	CLOSE = 1 << 14,
}					t_type;

typedef struct s_token
{
	int             index;
	void			*content;
    t_type			type;
	t_type			sub_type;
    struct s_token  **args;
	struct s_token	*left;
	struct s_token	*right;
}					t_token;

// tokens_utils.c && tokens_utils2.c
t_token				*create_token(void *content, t_type type, t_type sub_type);
t_token				**add_token(t_token **arr, t_token *token);
void				copy_arr(t_token **new_arr, t_token **arr, size_t size);
void				free_tokens(t_token **tokens);
size_t				count_tokens(t_token **tokens);
void				print_tokens(t_token **tokens);

//tokenizer.c
int tokenizer(char *line, t_token ***tokens);

//tokens_reoder.c
void    reorder_tokens(t_token **tokens);
void    assign_index(t_token **tokens);


t_token* build_command_tree(t_token** tokens, int token_count);
void print_command_tree(t_token* node, int depth);

//tree_builder.c
t_token *build_tree(t_token **tokens, size_t *i);


void	ft_echo(char** str);
void	cd(char **str, char *curr_dir);
void	check_error(int n, char *comm, char *arg);
void	free_array(char **str);
void	pwd();
void	ft_env(char **env);
void	ft_export(char **env, char **var);
void	ft_exit(char **exit_status);
t_data	*analize_env(char **env);
char	**copy_array(char **array);
char	*ft_getenv(char *variable, char **env);
void	ft_unset(char **var, char ***env);
void	change_env(char **env, char *var);
char	**find_wildcards(char *str);


int     assign_args(t_token **tokens);
void    print_args(t_token **tokens);
#endif
