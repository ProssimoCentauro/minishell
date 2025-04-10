#include "minishell.h"

int g_exit_status;

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

int	main(int ac, char **av, char **env)
{
	t_token		**tokens;
	t_token		*tree;
	char		*line;
	size_t		i;
	t_execute	*info;
	char		*buf;

	(void) ac;
	(void) av;
	i = -1;
	info = malloc(sizeof(t_execute));
	info->pipe_fd = 0;
	while (42)
	{
		buf = set_prompt();
		set_info(info);
		tokens = NULL;
		//line = readline("\033[1;33m~~~\033[1;35m>\033[0m");
		line = readline(buf);
		if (!ft_strcmp(line, "exit"))
			ft_exit(EXIT_SUCCESS);
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
		executor(tree, env, info);
		if (check_builtin(info, env) == 0)
			execve_cmd(info, env);
		while (info->pid > 0)
		{
			waitpid(-1, NULL, 0);
			info->pid -= 1;
		}
		i = -1;
		free_tokens(tokens);
  }
}
