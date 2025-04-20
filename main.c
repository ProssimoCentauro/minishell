/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:20:04 by marvin            #+#    #+#             */
/*   Updated: 2025/04/20 16:22:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	main(void)
{
	size_t	i;
	t_data		*data;
	char		*line;
	int exit_status;
	t_execute	*info;
	char		*buf;

	data = malloc(sizeof(t_data));
	info = malloc(sizeof(t_execute));
	initial_configuration(data, info);
	while (42)
	{
		buf = set_prompt();
		//i = -1;
		data->tokens = NULL;
		signal_manager(SIGINT, sigint_handler);
		line = readline(buf);
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
			data->exit_status = 130;
			free_tokens(data->tokens);
			continue ;
		}
		assign_args(data->tokens);
		i = 0;
		while (data->tokens[i])
		{
			data->tree = build_tree(data->tokens, &i);
			start_execution(info, data);
			data->tree = NULL;
			while (data->tokens[i] && (data->tokens[i]->type & (NEW_LINE | END)))
				i++;
		}
		//data->tree = build_tree(data->tokens, &i);
		free_tokens(data->tokens);
	}
	exit_status = data->exit_status;
	final_free(info, data);
  exit(exit_status);
}
