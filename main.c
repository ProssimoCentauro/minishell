#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char	*input;
	char	*buf;

	input = ft_calloc(1, sizeof(char));
	(void) ac;
	(void) av;
	find_wildcards("*.c");
	while (1)
	{
		buf = ft_calloc(1024, sizeof(char));
		getcwd(buf, 1024);
		buf[ft_strlen(buf)] = ' ';
		buf[ft_strlen(buf) + 1] = '\0';
		input = readline(buf);
		if (ft_strncmp(input, "echo ", ft_strlen("echo ")) == 0 || \
		ft_strncmp(input, "echo", ft_strlen("echo") + 1) == 0)
			ft_echo(ft_split(input + ft_strlen("echo"), ' '));
		else if (ft_strncmp(input, "cd ", ft_strlen("cd ")) == 0 || \
		ft_strncmp(input, "cd", ft_strlen("cd") + 1) == 0)
			cd(ft_split(input + ft_strlen("cd"), ' '), buf);
		else if (ft_strncmp(input, "pwd", ft_strlen("pwd") + 1) == 0)
			pwd();
		else if (ft_strncmp(input, "env", ft_strlen("env") + 1) == 0)
			ft_env(env);
		else if (ft_strncmp(input, "export ", ft_strlen("export ")) == 0 || \
		ft_strncmp(input, "export", ft_strlen("export") + 1) == 0)
			ft_export(env, ft_split(input + ft_strlen("export"), ' '));
		else if (ft_strncmp(input, "exit", ft_strlen("exit") + 1) == 0 || \
		ft_strncmp(input, "exit ", ft_strlen("exit ")) == 0)
			ft_exit(ft_split(input + ft_strlen("exit"), ' '));
		else if (ft_strncmp(input, "unset", ft_strlen("unset") + 1) == 0 || \
		ft_strncmp(input, "unset ", ft_strlen("unset ")) == 0)
			ft_unset(ft_split(input + ft_strlen("unset"), ' '), &env);
		else if (*input != '\0')
			printf("%s: command not found\n", input);
		free(input);
		free(buf);
	}
}