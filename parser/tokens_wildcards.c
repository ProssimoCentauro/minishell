#include "minishell.h"

t_token	**add_wildcards(t_token **tokens)
{
	size_t	i;
	size_t	j;
	char	**mat;
	t_token	*token;


	i = 0;
	j = 0;
	token = NULL;
	while (tokens[i])
	{
		mat = find_wildcards((char *)tokens->content);
		if (!mat)
		{
			i++;
			continue;
		}
		while(*mat)
		{
			token = create_token
		}
	}
}
