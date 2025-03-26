#include "minishell.h"

int main()
{
	char	*input;
	char	*buf;

	input = ft_calloc(1, sizeof(char));
	while (1)
	{
		buf = ft_calloc(1024, sizeof(char));
		getcwd(buf, 1024);
		buf[ft_strlen(buf)] = ' ';
		buf[ft_strlen(buf) + 1] = '\0';
		input = readline(buf);
		if (ft_strncmp(input, "echo", ft_strlen("echo")) == 0)
		{
			ft_echo(ft_split(input + ft_strlen("echo"), ' '));
			free(input);
		}
		if (ft_strncmp(input, "cd", ft_strlen("cd")) == 0)
		{
			cd(ft_split(input + ft_strlen("cd"), ' '), buf);
		}
		free(buf);
	}
}