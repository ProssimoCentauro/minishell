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
	CMD,
	LIMITER,
	DELIMETER,
	REDIRECT,
	FILENAME,
	AND,
	OR,
	IN,
	OUT,
	HERE_DOC,
	APPEND,
	PIPE,
	OPEN,
	CLOSE,
}	t_type;


typedef struct	s_token
{
	void	*content;
	t_type	type;
	t_type	sub_type;
	struct s_token *left;
	struct s_token *right;
}	t_token;

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
