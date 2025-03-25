#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"


typedef enum	e_type
{
	NONE = 0,
	CMD = 1 << 1,
	LIMITER = 1 << 2,
	DELIMETER, = 1 << 3,
	REDIRECT = 1 << 4,
	FILENAME = 1 << 5,
	AND = 1 << 6,
	OR = 1 << 7,
	IN = 1 << 8,
	OUT = 1 << 9,
	HERE_DOC = 1 << 10,
	APPEND = 1 << 11,
	PIPE = 1 << 12,
	OPEN = 1 << 13,
	CLOSE = 1 << 14,
}	t_type;


typedef struct	s_token
{
	void	*content;
	t_type	type;
	t_type	sub_type;
	struct s_token *left;
	struct s_token *right;
}	t_token;

t_token	create_token(void *content, t_type type, t_type sub_type);



#endif
//pwd && echo loi && (echo sium || pwd)
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
