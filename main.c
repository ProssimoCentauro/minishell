#include "minishell.h"

int g_last_signal;
/*
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
}*/

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

int	main(int ac, char **av)
{
	int exit_status;
	t_data	*data;
	char	*line;
	size_t	i;
	t_execute	*info;
	char		*buf;

	(void)ac;
	(void)av;

	data = malloc(sizeof(t_data));
	info = malloc(sizeof(t_execute));
	initial_configuration(data, info);
	while (42)
	{
		buf = set_prompt();
		i = -1;
		set_info(info);
		data->tokens = NULL;
		signal_manager(SIGINT, sigint_handler);
        signal_manager(SIGQUIT, SIG_IGN);
        line = readline(buf);
		if (g_last_signal == SIGINT)
            data->exit_status = 130;
        else if (g_last_signal == SIGQUIT)
            data->exit_status = 131;
		free (buf);
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		if (line && *line && ft_strcmp(line, "\n"))
			add_history(line);
		if (tokenizer(line, &data->tokens))
			continue ;
		if (syntax_error(data->tokens, check_args(data->tokens)))
			continue ;
		reorder_tokens(data->tokens);
		assign_index(data->tokens);
		if (finalize_tokens(data->tokens, data) == 256)
		{
			free_tokens(data->tokens);
			continue ;
		}
		assign_args(data->tokens);
		i = 0;
		while (data->tokens[i])
		{
            signal_manager(SIGQUIT, sigquit_handler);
            g_last_signal = 0;
			data->tree = build_tree(data->tokens, &i);
			executor(data->tree, data, info);
			execve_cmd(info, data);
			waitpid(info->pid, &(data->exit_status), 0);
			data->exit_status = WEXITSTATUS(data->exit_status);
			while (info->processes > 0)
			{
				wait(NULL);
				info->processes -= 1;
			}
			data->tree = NULL;
			free_array(info->args);
			set_info(info);
			while (data->tokens[i] && (data->tokens[i]->type & (NEW_LINE | END)))
				i++;
		}
		//data->tree = build_tree(data->tokens, &i);
		free_tokens(data->tokens);
	}
	exit_status = data->exit_status;
	rl_clear_history();
	free_array(data->env);
	free(info->args);
	free(info);
	free(data);
	exit(exit_status);
}
