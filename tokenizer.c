#include "minishell.h"

//cmd1 arg0 arg1 &&(cmd2 arg0 | cmd3 )
//
//

static size_t	count_tokens(t_token *tokens)
{
	size_t	i;

	if (tokens == NULL)
		return (2);
	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

t_token	**add_token(t_token **arr, t_token *token)
{
	t_token	*new_arr;
	size_t	i;

	i = count_tokens(*arr);
	if (*arr == NULL)
	{
		new_arr = (t_token *)malloc(sizeof(t_token));
		new_arr[0] = NULL;
	}
	else
	{
		new_arr = (t_token *)malloc(sizeof(t_token) * i);

	}
}

t_token	**tokenizer(char *str)
{
	t_token *tokens = NULL;
	size_t	i;

	i = 0;
	while (str[i])
	{

	}
}
