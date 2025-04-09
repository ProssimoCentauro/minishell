#include "minishell.h"


t_token	*check_next(t_token **tokens, size_t i, t_token **res)
{
	if (tokens[i]->sub_type & (CMD))
	{
		if (tokens[i + 1]->sub_type & (OPEN))
			*res = tokens[i + 1];
	}
	else if (tokens[i]->sub_type & (AND | OR | PIPE))
	{
		if (tokens[i + 1]->sub_type & (AND | OR | PIPE | CLOSE | NEW_LINE))
			*res = tokens[i + 1];
	}
	else if (tokens[i]->sub_type & (OPEN))
	{
		if (tokens[i + 1]->sub_type & (AND | OR | PIPE | CLOSE | NEW_LINE))
			*res = tokens[i + 1];
	}
	else if (tokens[i]->sub_type & (CLOSE))
	{
		if (tokens[i + 1]->sub_type & (CMD))
			*res = tokens[i + 1];
	}
	return (*res);
}

int	search_quotes(char *str, size_t *i, char to_search)
{
	static	size_t	d_q = 0;
	static	size_t	s_q = 0;

	while(str[*i])
	{
		if ((str[*i] == '"' || str[*i] == '\'') && str[*i] != to_search)
		{
			if (str[*i] == '"')
				d_q++;
			else if (str[*i] == '\'')
				s_q++;
			to_search = str[*i];
			(*i)++;
			if (search_quotes(str, i, to_search))
				return (1);
			(*i)++;
		}
		else if ((str[*i] == '"' || str[*i] == '\'') && str[*i] == to_search)
		{
			if (str[*i] == '"')
				d_q--;
			else if (str[*i] == '\'')
				s_q--;
			return(0);
		}
		else
			(*i)++;
	}
	if (s_q != 0 || d_q != 0)
		return (1);
	return (0);
}

t_token	*check_quotes(t_token *token, t_token **res)
{
	size_t	i;

	i = 0;
	if (search_quotes((char *)token->content, &i, 0))
	{
		token->quotes = 1;
		*res = token;
	}
	return (*res);
}

t_token	*check_args(t_token **tokens)
{
	t_token	*res;
	size_t	i;
	size_t	brackets;

	res = NULL;
	i = -1;
	brackets = 0;

	if (tokens[0]->sub_type & (AND | OR | PIPE | CLOSE))
		return (tokens[0]);
	while (tokens[++i])
	{
		if (tokens[i] && check_next(tokens, i, &res))
			break ;
		if (tokens[i] && check_quotes(tokens[i], &res))
		{
			tokens[i]->quotes = 1;
			return (tokens[i]);
		}
		if (tokens[i] && tokens[i]->type == OPEN)
			brackets++;
		else if (tokens[i] && tokens[i]->type == CLOSE && brackets == 0)
			return(tokens[i]);
		else if (tokens[i] && tokens[i]->type == CLOSE)
			brackets--;
	}
	return (res);
}
