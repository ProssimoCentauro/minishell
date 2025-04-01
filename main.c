#include "minishell.h"

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

int	main(void)
{
	t_token	**tokens;
//	t_token	*tree;
	char	*line;
	size_t	i;

	tokens = NULL;
	i = -1;
	while (42)
	{
		//		line = readline("\033[1;33m~~~\033[1;35m>\033[0m");
		line = readline("~~~>");
		if (tokenizer(line, &tokens))
		{
			continue ;
		}
		reorder_tokens(tokens);
		assign_index(tokens);
		while (tokens[++i])
			printf("index %d: %s: %s: %s\n", tokens[i]->index,
				type_to_str(tokens[i]->type), type_to_str(tokens[i]->sub_type),
				(char *)tokens[i]->content);
		
//		tree = build_tree(tokens, 0);


		/*
			printf("\n\n");
			tree = build_command_tree(tokens, count_tokens(tokens));
			if (tree)
			{
				print_command_tree(tree, 0);
			} else
			{
				printf("ERROR!\n");
			}
		*/
		// tree = build_command_tree(tokens, count_tokens(tokens));
		// print_command_tree(tree, 0);
		i = -1;
		tokens = NULL;
	}
}
