#include "minishell.h"

/*
t_token	make_tree(char *str)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	j = 0;
	temp = 0;
	while (str[i])
	{
		while (str[i] != '\0')
		{
			if (str[i] == '(')
				temp = i;
			i++;
		}	
	}
}
*/

int	main()
{
        t_token **tokens;

        tokens = NULL;
        tokens = add_token(tokens, create_token(ft_strdup("Token1"), CMD, CMD));
        tokens = add_token(tokens, create_token(ft_strdup("Token1"), CMD, CMD));
        tokens = add_token(tokens, create_token(ft_strdup("Token1"), CMD, CMD));
        print_tokens(tokens);
        free_tokens(tokens);
        return (0);
}
