#include "minishell.h"
/*
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
}*/
static char	*type_to_str(t_type type);

void	print_tree(t_token *root, int depth)
{
	int	i;

	if (root == NULL)
		return ;
	depth += 5;
	print_tree(root->right, depth);
	ft_printf("\n");
	i = 5;
	while (i < depth)
	{
		ft_printf(" ");
		i++;
	}
	ft_printf("%s\n", (char *)root->content);
	print_tree(root->left, depth);
}

static char	*type_to_str(t_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == LIMITER)
		return ("LIMITER");
	else if (type == DELIMETER)
		return ("DELIMETER");
	else if (type == REDIRECT)
		return ("REDIRECT");
	else if (type == FILENAME)
		return ("FILENAME");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == IN)
		return ("IN");
	else if (type == OUT)
		return ("OUT");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == OPEN)
		return ("OPEN");
	else if (type == CLOSE)
		return ("CLOSE");
	return ("TYPE ERROR!");
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	main(void)
{
	t_token	**tokens;
	t_token	*tree;
	char	*line;
	size_t	i;

	i = -1;
	while (42)
	{
		tokens = NULL;
		//line = readline("\033[1;33m~~~\033[1;35m>\033[0m");
		line = readline("~~~>");
		if (!ft_strcmp(line, "exit"))
			exit(EXIT_SUCCESS);
		if (tokenizer(line, &tokens))
			continue ;
		reorder_tokens(tokens);
		assign_index(tokens);
        ft_printf("assigning args!\n\n");
		assign_args(tokens);
        printf("assign finished!\n\n");
        while (tokens[++i])
			printf("index %d: %s: %s: %s\n", tokens[i]->index,
				type_to_str(tokens[i]->type), type_to_str(tokens[i]->sub_type),
				(char *)tokens[i]->content);
		
		printf("\n\n\n");
		i = 0; 
		tree = build_tree(tokens, &i);
		print_tree(tree, 0);
		printf("\n\n");
        print_args(tokens);
        i = -1;
		free_tokens(tokens);
    }
}
