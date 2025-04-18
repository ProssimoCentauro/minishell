/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtodaro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:55 by rtodaro           #+#    #+#             */
/*   Updated: 2025/04/18 17:45:22 by rtodaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int g_last_signal;

extern char		**env_copy;

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
    NEW_LINE = 1 << 15,
    END = 1 << 16,
} t_type;

typedef struct s_token
{
	int             index;
	void			*content;
	t_type			type;
	t_type			sub_type;
	int			quotes;
	struct s_token  **args;
	struct s_token	*left;
	struct s_token	*right;
}					t_token;


typedef	struct	s_data
{
	char	**variables;
	t_token	*root;
	char	**env;
	int		exit_status;
	t_token	*tree;
	char	**free_variables;
}	t_data;

typedef struct	s_execute
{
	char	*com;
	int		pipe;
	int		file_in;
	int		file_out;
	char	*file;
	char	**args;
	int		pipe_fd;
	int		pid;
	int		std_in;
	int		std_out;
	t_type	delimiter;
}				t_execute;


//main.c
int	ft_strcmp(char *s1, char *s2);

// tokens_utils.c && tokens_utils2.c
t_token **remove_token_at(t_token **arr, size_t index);
t_token **add_token_at(t_token **arr, t_token *token, size_t index);
t_token				*create_token(void *content, t_type type, t_type sub_type);
t_token				**add_token(t_token **arr, t_token *token);
void				copy_arr(t_token **new_arr, t_token **arr, size_t size);
void				free_tokens(t_token **tokens);
size_t				count_tokens(t_token **tokens);
void				print_tokens(t_token **tokens);
int	free_token(t_token *token);

//tokenizer_utils.c
int     special_char(char c);
char    *create_str(char *line, size_t i, size_t j);
int     search_special(char *line, size_t i);
void    jump_spaces(char *line, size_t *i, size_t *j);

//tokenizer.c
int tokenizer(char *line, t_token ***tokens);

//tokens_reoder.c
void    reorder_tokens(t_token **tokens);
void    assign_index(t_token **tokens);


t_token* build_command_tree(t_token** tokens, int token_count);
void print_command_tree(t_token* node, int depth);

//tree_builder.c
t_token *build_tree(t_token **tokens, size_t *i);

//built in
void	ft_echo(char** str, t_data *data, t_execute *info);
void	cd(char **str, t_data *data);
void	pwd(t_data *data, t_execute *info);
void	ft_env(t_data *data, t_execute *info);
void	ft_export(char **var, t_data *data, t_execute *info);
void	ft_exit(char **exit_status);
void	ft_unset(char **var, t_data *data);

void	change_env(char **env, char *var);
void	check_error(int n, char *comm, char *arg, t_data *data);
void	free_array(char **str);
char	**copy_array(char **array);
char	*ft_getenv(char *variable, char **env);
char	**find_wildcards(char *str);
void	executor(t_token *tree, t_data *data, t_execute *info);
char	*findpath(char **env, char *com);
void	print_info(t_execute *info);
void	set_info(t_execute *info);
t_data	*analize_env(char **env);
void	execve_cmd(t_execute *info, t_data *data);
int		check_builtin(t_execute *info, t_data *data);
char	*set_prompt();
int		array_len(char **array);
void	command_error(char *comm, t_data *data);
char	**add_array(t_data *data, char *var);
char	*quotes(char *str);
void	set_fd(t_execute *info);
void	restore_fd(t_execute *info);
void	check_dup(int n, int fd);
void	close_fd(int fd1, int fd2, int fd3);
void	exit_and_free(int exit_status, char *com);
int		is_a_free_variable(char *str, t_data *data);
void	add_env(char *var, t_data *data);
char    *get_value(char *str);
char    *export_join(char *str);
char    *get_export_variable(char *str);

int		len_wildcards(char *str);
char	**ft_arrayjoin(char **s1, char **s2);
char	**sort_array(char **env);
void	initial_configuration(t_data *data, t_execute *info);
char	*ft_strdup_quote(char *str);

int     assign_args(t_token **tokens);
void    print_args(t_token **tokens);

//int    write_on_file(int fd, char *delimeter);
//int     check_heredoc(t_token **tokens);
int     finalize_tokens(t_token **tokens, t_data *data);
int forbidden_symbols(char c);

int     syntax_error(t_token **tokens, t_token *check);

t_token *check_args(t_token **tokens);

//signal_handlers.c
void sigint_handler(int signum);
void setup_signal_handlers(void);
void    handle_heredoc(int signum);
int     signal_manager(int signum, void (*handler)(int s));

//quotes_utils.c
void remove_quotes(char *line);
t_token	*check_quotes(t_token *token, t_token **res);

char	*check_export2(char *line, t_data *data);

//check_next.c
t_token *check_next(t_token **tokens, size_t i, t_token **res);

//create_special.c
t_token	*create_special(char *line, size_t *i, size_t *j);

//create_cmd.c
t_token	*create_cmd(char *line, size_t *i, size_t *j, t_type type);

//select_handler.c
void	select_handler(t_token **tokens, t_token **root,
		t_token **last, size_t *i);
//write_on_file.c
int     write_on_file(int fd, char *delimiter, t_token **tokens, t_data *data);

//check_here
int	check_heredoc(t_token **tokens, size_t *i, t_data *data);

//tokens_final_funcs_utils.c
int     forbidden_symbols(char c);
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strncpy(char *dest, const char *src, size_t n);
char    *replace_range(char *s1, char *s2, size_t i, size_t j);

//process_string.c
char	*process_string(char *line, t_data *data, long *j, long *k);
#endif
