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

/*
static	void	test_tokens(void)
{
        t_token **tokens;

        tokens = NULL;
        tokens = add_token(tokens, create_token(ft_strdup("Token1"), CMD, CMD, 0));
        tokens = add_token(tokens, create_token(ft_strdup("Token1"), CMD, CMD, 0));
        tokens = add_token(tokens, create_token(ft_strdup("Token1"), CMD, CMD, 0));
        print_tokens(tokens);
        free_tokens(tokens);
}
*/
int	main(void)
{
	t_token	**tokens = NULL;
	char	*line;
    size_t  i;
    //void    **matrix = create_mat();
/*
    for (int i = 0; i < 9; i++)
    {
        printf("%s -> [%d, %d]\n",
               (char *)((void **)matrix)[i * 3 + 0],   // Prima colonna (stringa)
               (int)(long)((void **)matrix)[i * 3 + 1], // Seconda colonna (enum)
               (int)(long)((void **)matrix)[i * 3 + 2]  // Terza colonna (enum)
        );
    }*/
    //return 0;

    i = -1;
	while (42)
	{
		printf("\033[1;33m~~~\033[1;35m>\033[0m");
		line = readline(NULL);
        tokenizer(line, &tokens);
        while (tokens[++i])
            printf("index %d: %s\n", tokens[i]->index, (char *)tokens[i]->content);
        return (0);
	}
}
