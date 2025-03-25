#include "minishell.h"

t_token	create_token(void *content, t_type type, t_type sub_type)
{
	t_token	token;
	
	token = (t_token)malloc(sizeof(t_token));
	token.content = content;
	token.type = type;
	token.sub_type = sub_type;
	token.left = NULL;
	token.right = NULL;
	return (token);
}
