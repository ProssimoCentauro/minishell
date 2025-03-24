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
	char	*line;

	while (42)
	{
		printf("~~~~~~~>");
		line = readline(NULL);
	}
	return (0);
}
