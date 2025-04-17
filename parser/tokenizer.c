#include "minishell.h"

void	jump_spaces(char *line, size_t *i, size_t *j)
{
	while (line[*j] == ' ')
		(*j)++;
	*i = *j;
}

int	special_char(char c)
{
	if (c == '|' || c == '&')
		return (1);
	if (c == '<' || c == '>')
		return (2);
	if (c == '(' || c == ')')
		return (3);
	return (0);
}

int	search_special(char *line, size_t i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (special_char(line[i]));
}

char	*create_str(char *line, size_t i, size_t j)
{
	char	*res;
	size_t	k;

	res = (char *)malloc(j - i + 2);
	k = 0;
	while (i <= j)
	{
		res[k] = line[i];
		i++;
		k++;
	}
	res[k] = '\0';
	return (res);
}

static int	is_quote_open(char c, int q, char *temp)
{
	if ((c == '"' || c == '\'') && q == 0)
	{
		*temp = c;
		return (1);
	}
	return (0);
}

static int	is_quote_close(char c, int q, char temp)
{
	return (c == temp && q == 1);
}

static int	is_end_char(char c, int q)
{
	if (q != 0)
		return (0);
	return (c == ' ' || c == '\n' || special_char(c));
}

t_token	*create_cmd(char *line, size_t *i, size_t *j, t_type type)
{
	t_token	*cmd;
	char	temp;
	int		q;

	q = 0;
	temp = 0;
	if (line[*j] == '\n')
	{
		cmd = create_token(ft_strdup("newline"), NEW_LINE, NEW_LINE);
		(*j)++;
		return (cmd);
	}
	while (line[*j])
	{
		if (is_quote_open(line[*j], q, &temp))
			q++;
		else if (is_quote_close(line[*j], q, temp))
			q--;
		else if (is_end_char(line[*j], q))
			break ;
		(*j)++;
	}
	cmd = create_token(create_str(line, *i, *j - 1), type, type);
	return (cmd);
}

static t_token	*handle_and(char *line, size_t *i, size_t *j)
{
	if (line[*j + 1] == '&')
	{
		*j += 2;
		*i = *j;
		return (create_token(ft_strdup("&&"), DELIMETER, AND));
	}
	(*j)++;
	*i = *j;
	return (create_token(ft_strdup("&"), DELIMETER, AND));
}

static t_token	*handle_or(char *line, size_t *i, size_t *j)
{
	if (line[*j + 1] == '|')
	{
		*j += 2;
		*i = *j;
		return (create_token(ft_strdup("||"), DELIMETER, OR));
	}
	(*j)++;
	*i = *j;
	return (create_token(ft_strdup("|"), REDIRECT, PIPE));
}

static t_token	*handle_less(char *line, size_t *i, size_t *j)
{
	if (line[*j + 1] == '<')
	{
		*j += 2;
		*i = *j;
		return (create_token(ft_strdup("<<"), REDIRECT, HEREDOC));
	}
	(*j)++;
	*i = *j;
	return (create_token(ft_strdup("<"), REDIRECT, IN));
}

static t_token	*handle_greater(char *line, size_t *i, size_t *j)
{
	if (line[*j + 1] == '>')
	{
		*j += 2;
		*i = *j;
		return (create_token(ft_strdup(">>"), REDIRECT, APPEND));
	}
	(*j)++;
	*i = *j;
	return (create_token(ft_strdup(">"), REDIRECT, OUT));
}

t_token	*create_special(char *line, size_t *i, size_t *j)
{
	if (line[*j] == '&')
		return (handle_and(line, i, j));
	if (line[*j] == '|')
		return (handle_or(line, i, j));
	if (line[*j] == '<')
		return (handle_less(line, i, j));
	if (line[*j] == '>')
		return (handle_greater(line, i, j));
	if (line[*j] == '(')
	{
		(*j)++;
		*i = *j;
		return (create_token(ft_strdup("("), OPEN, OPEN));
	}
	if (line[*j] == ')')
	{
		(*j)++;
		*i = *j;
		return (create_token(ft_strdup(")"), CLOSE, CLOSE));
	}
	return (NULL);
}

static int	is_arrow(t_token **mat)
{
	size_t	count;

	if (mat == NULL)
		return (0);
	count = count_tokens(mat) - 1;
	if (mat[count]->sub_type & (IN | OUT | APPEND))
		return (1);
	else if (mat[count]->sub_type & HEREDOC)
		return (2);
	return (0);
}

static t_token	*select_creation(char *line, size_t *i, size_t *j,
		t_token **tokens)
{
	t_token	*token;

	token = NULL;
	if (!is_arrow(tokens))
		token = create_cmd(line, i, j, CMD);
	else if (is_arrow(tokens) == 1)
		token = create_cmd(line, i, j, FILENAME);
	else if (is_arrow(tokens) == 2)
		token = create_cmd(line, i, j, LIMITER);
	return (token);
}

static int	is_empty_line(char *line)
{
	return (line[0] == '\0');
}

static void	process_non_special_chars(char *line, size_t *i, size_t *j,
		t_token ***tokens)
{
	while (line[*j] && !special_char(line[*j]))
	{
		*tokens = add_token(*tokens, select_creation(line, i, j, *tokens));
		jump_spaces(line, i, j);
	}
}

static void	process_special_chars(char *line, size_t *i, size_t *j,
		t_token ***tokens)
{
	while (line[*j] && special_char(line[*j]))
	{
		*tokens = add_token(*tokens, create_special(line, i, j));
		jump_spaces(line, i, j);
	}
}

int	tokenizer(char *line, t_token ***tokens)
{
	size_t	i;
	size_t	j;
	t_token	*final;

	i = 0;
	j = 0;
	if (is_empty_line(line))
		return (1);
	while (line[j])
	{
		jump_spaces(line, &i, &j);
		process_non_special_chars(line, &i, &j, tokens);
		process_special_chars(line, &i, &j, tokens);
	}
	final = create_token(ft_strdup("newline"), END, END);
	*tokens = add_token(*tokens, final);
	return (0);
}
