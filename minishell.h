/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtodaro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:55 by rtodaro           #+#    #+#             */
/*   Updated: 2025/03/25 16:30:58 by rtodaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

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
	struct s_token	*left;
	struct s_token	*right;
}					t_token;

// tokens_utils.c && tokens_utils2.c
t_token				*create_token(void *content, t_type type,
        t_type sub_type, int index);
t_token				**add_token(t_token **arr, t_token *token);
void				copy_arr(t_token **new_arr, t_token **arr, size_t size);
void				free_tokens(t_token **tokens);
size_t				count_tokens(t_token **tokens);
void				print_tokens(t_token **tokens);

void    **create_mat();
int tokenizer(char *line, t_token ***tokens);
#endif

// pwd && echo loi && (echo sium || pwd)
//
//
//
//
//		pwd
//	||
//		echo
//&&
//		echo
//	&&
//		pwd
