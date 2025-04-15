#include "minishell.h"

// Jump space chars
void    jump_spaces(char *line, size_t *i, size_t *j)
{
    while (line[*j] == ' ')
        (*j)++;
    *i = *j;
}

// Detect special chars
int special_char(char c)
{
    if (c == '|' || c == '&')
        return (1);
    if (c == '<'|| c == '>')
        return (2);
    if ( c == '(' || c == ')')
        return (3);
    return (0);
}

int	search_special(char *line, size_t i)
{
	while (line[i] && line[i] == ' ')
		i++;
	return (special_char(line[i]));
}

// Create the string for the token
char    *create_str(char *line, size_t i, size_t j)
{
    char *res;
    size_t  k;


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

// Create a cmd type token
//logica delle due quotes se trovo uno spazio e q sta a zero allora la parola è finita
t_token    *create_cmd(char *line, size_t *i, size_t *j, t_type type)
{
	t_token *cmd;
	char	temp;
	int	q;
	
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
		if ((line[*j] == '"' || line[*j] == '\'') && q == 0)
		{
			temp = line[*j];
			q++;
		}
		else if (line[*j] == temp && q == 1)
			q--;
		else if ((line[*j] == ' ' || line[*j] == '\n' || special_char(line[*j])) && q == 0)
			break ;
		(*j)++;
	}
    cmd = create_token(create_str(line, *i, *j - 1), type, type);
    return(cmd);
}

// Create a special type token
t_token    *create_special(char *line,
        size_t *i, size_t *j)
{
    t_token *special = NULL;
    
    if (line[*j] == '&')
    {
        if (line[*j + 1] == '&')
        {
            special = create_token(ft_strdup("&&"),
                    DELIMETER, AND);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup("&"),
                    DELIMETER, AND);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '|')
    {
        if (line[*j + 1] == '|')
        {
            special = create_token(ft_strdup("||"),
                    DELIMETER, OR);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup("|"),
                    REDIRECT, PIPE);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '<')
    {
        if (line[*j + 1] == '<')
        {
            special = create_token(ft_strdup("<<"),
                    REDIRECT, HEREDOC);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup("<"),
                    REDIRECT, IN);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '>')
    {
        if (line[*j + 1] == '>')
        {
            special = create_token(ft_strdup(">>"),
                    REDIRECT, APPEND);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup(">"),
                    REDIRECT, OUT);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '(')
    {
        special = create_token(ft_strdup("("),
                OPEN, OPEN);
        (*j)++;
        *i = *j;
    }
    else if (line[*j] == ')')
    {
        special = create_token(ft_strdup(")"),
                CLOSE, CLOSE);
        (*j)++;
        *i = *j;
    }
    return (special);
}

// Detect if last token is a redirection (pipe excluded)
static int is_arrow(t_token **mat)
{
    size_t  count;

    if (mat == NULL)
        return (0);
    count = count_tokens(mat) - 1;
    if (mat[count]->sub_type & (IN | OUT | APPEND))
        return (1);
    else if (mat[count]->sub_type & HEREDOC)
        return (2);
    return (0);
}

// Select the type of token to create
static t_token *select_creation(char *line, size_t *i,
        size_t *j, t_token **tokens)
{
    t_token *token = NULL;

    if (!is_arrow(tokens))
        token = create_cmd(line, i, j, CMD);
    else if (is_arrow(tokens) == 1)
        token = create_cmd(line, i, j, FILENAME);
    else if (is_arrow(tokens) == 2)
	    token = create_cmd(line, i, j, LIMITER);
    return (token);
} 

// Transform the received line 
int    tokenizer(char *line, t_token ***tokens)
{
    size_t  i;
    size_t  j;
    t_token	*final;

    i = 0;
    j = 0;
    if (!line[0])
        return (1);
    while(line[j])
    {
        jump_spaces(line, &i, &j);
        while (line[j] && !special_char(line[j]))
        {
                *tokens = add_token(*tokens,
                        select_creation(line, &i, &j, *tokens));
            jump_spaces(line, &i, &j);
        }
        while (line[j] && special_char(line[j]))
        {
            *tokens = add_token(*tokens,
                    create_special(line, &i, &j));
            jump_spaces(line, &i, &j);
        }
    }
    final = create_token(ft_strdup("newline"), END, END);
    *tokens = add_token(*tokens, final);
    return (0);
}
