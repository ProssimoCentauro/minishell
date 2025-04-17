#include "minishell.h"

static int	is_pair_1(t_token **tokens, size_t i)
{
	if (tokens[i]->sub_type & CMD)
		if (tokens[i + 1]->sub_type & OPEN)
			return (1);
	if (tokens[i]->sub_type & CLOSE)
		if (tokens[i + 1]->sub_type & CMD)
			return (1);
	return (0);
}

static int	is_pair_2(t_token **tokens, size_t i)
{
	if (tokens[i]->sub_type & (AND | OR | PIPE))
		if (tokens[i + 1]->sub_type & (AND | OR | PIPE | CLOSE | END))
			return (1);
	if (tokens[i]->sub_type & OPEN)
		if (tokens[i + 1]->sub_type & (AND | OR | PIPE | CLOSE | END))
			return (1);
	return (0);
}

static int	is_pair_3(t_token **tokens, size_t i)
{
	if (tokens[i]->sub_type & (IN | OUT | APPEND | HEREDOC))
		if (tokens[i + 1]->sub_type & (NEW_LINE | END))
			return (1);
	return (0);
}

static int	should_assign_res(t_token **tokens, size_t i)
{
	int	found;

	found = 0;
	if (is_pair_1(tokens, i))
		found = 1;
	if (is_pair_2(tokens, i))
		found = 1;
	if (is_pair_3(tokens, i))
		found = 1;
	return (found);
}

t_token	*check_next(t_token **tokens, size_t i, t_token **res)
{
	int	should_assign;

	should_assign = should_assign_res(tokens, i);
	if (should_assign)
		*res = tokens[i + 1];
	return (*res);
}

t_token	*check_quotes(t_token *token, t_token **res)
{
	size_t	j;
	char	*line;
	char	to_find;

	j = 0;
	line = (char *)token->content;
	to_find = 0;
	while (line[j])
	{
		if (line[j] == '"' || line[j] == '\'')
		{
			to_find = line[j++];
			while (line[j] && line[j] != to_find)
				j++;
			if (!line[j])
			{
				*res = token;
				break ;
			}
		}
		j++;
	}
	return (*res);
}

static int	is_invalid_start(t_token **tokens)
{
	if (tokens[0]->sub_type & (AND | OR | PIPE | CLOSE))
		return (1);
	return (0);
}

static int	is_background_amp(t_token *token)
{
	if (token && token->sub_type == AND)
		if (!ft_strcmp((char *)token->content, "&"))
			return (1);
	return (0);
}

static int	handle_quotes(t_token *token, t_token **res)
{
	t_token	*match;

	match = check_quotes(token, res);
	if (match)
	{
		token->quotes = 1;
		return (1);
	}
	return (0);
}

static int	handle_brackets(t_token *token, size_t *brackets, int *unmatched)
{
	if (token->type == OPEN)
		(*brackets)++;
	else if (token->type == CLOSE && *brackets == 0)
	{
		*unmatched = 1;
		return (1);
	}
	else if (token->type == CLOSE)
		(*brackets)--;
	return (0);
}

t_token	*check_args(t_token **tokens)
{
	t_token	*res;
	size_t	i;
	size_t	brackets;
	int		unmatched;

	res = NULL;
	i = -1;
	brackets = 0;
	unmatched = 0;
	if (is_invalid_start(tokens))
		return (tokens[0]);
	while (tokens[++i])
	{
		if (is_background_amp(tokens[i]))
			return (tokens[i]);
		if (check_next(tokens, i, &res))
			break ;
		if (handle_quotes(tokens[i], &res))
			return (tokens[i]);
		if (handle_brackets(tokens[i], &brackets, &unmatched))
			return (tokens[i]);
	}
	return (res);
}
