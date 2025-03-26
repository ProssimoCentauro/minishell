#include "minishell.h"

int main()
{
	char	*input;

	input = calloc(1, sizeof(char));
	while (1)
	{
		input = readline("------>");
		if (ft_strncmp(input, "echo", ft_strlen("echo")) == 0)
		{
			ft_echo(ft_split(input + ft_strlen("echo"), ' '));
			free(input);
		}
	}
}