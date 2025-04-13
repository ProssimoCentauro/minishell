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
	else if (type == NEW_LINE)
		return ("NEW_LINE");
	else if (type == END)
		return ("END");
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
	t_token	**tokens;
	t_data	*data;
	char	*line;
	size_t	i;
	t_execute	*info;
	char		*buf;
	char	**env_copy;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	setup_signal_handlers();
	env_copy = copy_array(env);
	data->env = env_copy;
//	printf("%s\n", ft_getenv("data", data->env));

	info = malloc(sizeof(t_execute));
	info->pid = 0;
	info->pipe_fd = 0;
	data->exit_status = 0;
	while (42)
	{
		buf = set_prompt();
		i = -1;
		set_info(info);
		tokens = NULL;
		//line = readline("\033[1;33m~~~\033[1;35m>\033[0m");
		line = readline(buf);
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		if (line && *line && ft_strcmp(line, "\n"))
			add_history(line);
		if (!ft_strcmp(line, "exit"))
			break ;
		if (tokenizer(line, &tokens))
			continue ;
/*       		printf("before reorder:\n");
		while (tokens[++i])
			printf("index %d: %s: %s: %s\n",
                    tokens[i]->index,
				type_to_str(tokens[i]->type),
                type_to_str(tokens[i]->sub_type),
				(char *)tokens[i]->content);
		i = -1;*/
		if (syntax_error(tokens, check_args(tokens)))
			continue ;
		reorder_tokens(tokens);
		assign_index(tokens);
		finalize_tokens(tokens, data);

        	ft_printf("assigning args!\n\n");
		assign_args(tokens);
        	printf("assign finished!\n\n");

       		 while (tokens[++i])
			printf("index %d: %s: %s: %s\n",
                    tokens[i]->index,
				type_to_str(tokens[i]->type),
                type_to_str(tokens[i]->sub_type),
				(char *)tokens[i]->content);

		printf("\n\n\n");
		i = 0;
		data->tree = build_tree(tokens, &i);
		print_tree(data->tree, 0);
		printf("\n\n");
		print_args(tokens);
		executor(data->tree, data, info);
		if (check_builtin(info, data) == 0)
			execve_cmd(info, data);
		while (info->pid > 0)
		{
			waitpid(-1, &data->exit_status, 0);
			info->pid -= 1;
		}
		i = -1;
		free_tokens(tokens);
		printf("last exit code: %d\n", g_exit_status);
	}
	rl_clear_history();
	free(info->args);
	free(info);
	exit(EXIT_SUCCESS);
}
