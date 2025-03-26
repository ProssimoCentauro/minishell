#include "minishell.h"

void **create_mat() {
    static void *mat[9][3]; // Matrice statica 9x3 di void *

    // Assegna stringhe alla prima colonna
    mat[0][0] = "<";
    mat[1][0] = ">";
    mat[2][0] = "<<";
    mat[3][0] = ">>";
    mat[4][0] = "|";
    mat[5][0] = "(";
    mat[6][0] = ")";
    mat[7][0] = "&&";
    mat[8][0] = "||";

    // Assegna valori dell'enum alla seconda colonna
    mat[0][1] = (void *)(long)REDIRECT;
    mat[1][1] = (void *)(long)REDIRECT;
    mat[2][1] = (void *)(long)REDIRECT;
    mat[3][1] = (void *)(long)REDIRECT;
    mat[4][1] = (void *)(long)REDIRECT;
    mat[5][1] = (void *)(long)OPEN;
    mat[6][1] = (void *)(long)CLOSE;
    mat[7][1] = (void *)(long)DELIMETER;
    mat[8][1] = (void *)(long)DELIMETER;

    // Assegna valori dell'enum alla terza colonna
    mat[0][2] = (void *)(long)IN;
    mat[1][2] = (void *)(long)OUT;
    mat[2][2] = (void *)(long)HEREDOC;
    mat[3][2] = (void *)(long)APPEND;
    mat[4][2] = (void *)(long)PIPE;
    mat[5][2] = (void *)(long)OPEN;
    mat[6][2] = (void *)(long)CLOSE;
    mat[7][2] = (void *)(long)AND;
    mat[8][2] = (void *)(long)OR;

    return (void **)mat;
}

void    jump_spaces(char *line, size_t *i, size_t *j)
{
    while (line[*j] == ' ')
        (*j)++;
    *i = *j;
}

int special_char(char c)
{
    if (c == '|' || c == '&')
        return (1);
    if (c == '<'|| c == '>')
        return (2);
    if ( c == '(' || c == ')')
        return (3);
    /*if (c == '\0')
        return (4);*/
    return (0);
}

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

t_token    *create_cmd(char *line, size_t *i,
        size_t *j, int index)
{
    t_token *cmd;

    while (line[*j] != ' ' && line[*j] && !special_char(line[*j]))
    {
        (*j)++;
    }
    cmd = create_token(create_str(line, *i, *j - 1),
            CMD, CMD, index);
    return(cmd);
}

t_token    *create_filename(char *line, size_t *i,
        size_t *j, int index)
{
    t_token *cmd;

    while (line[*j] != ' ' && line[*j] && !special_char(line[*j]))
    {
        (*j)++;
    }
    cmd = create_token(create_str(line, *i, *j - 1),
            FILENAME, FILENAME, index);
    return(cmd);
}

t_token    *create_special(char *line,
        size_t *i, size_t *j, int index)
{
    t_token *special;
    
    if (line[*j] == '&')
    {
        if (line[*j + 1] == '&')
        {
            special = create_token(ft_strdup("&&"),
                    DELIMETER, AND, index);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup("&"),
                    DELIMETER, AND, index);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '|')
    {
        if (line[*j + 1] == '|')
        {
            special = create_token(ft_strdup("||"),
                    DELIMETER, OR, index);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup("|"),
                    REDIRECT, PIPE, index);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '<')
    {
        if (line[*j + 1] == '<')
        {
            special = create_token(ft_strdup("<<"),
                    DELIMETER, HEREDOC, index);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup("<"),
                    REDIRECT, IN, index);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '>')
    {
        if (line[*j + 1] == '>')
        {
            special = create_token(ft_strdup(">>"),
                    DELIMETER, APPEND, index);
            *j = *j + 2;
            *i = *j;
        }
        else
        {
            special = create_token(ft_strdup(">"),
                    REDIRECT, OUT, index);
            (*j)++;
            *i = *j;
        }
    }
    else if (line[*j] == '(')
    {
        special = create_token(ft_strdup("("),
                OPEN, OPEN, index);
        (*j)++;
        *i = *j;
    }
    else if (line[*j] == ')')
    {
        special = create_token(ft_strdup(")"),
                CLOSE, CLOSE, index);
        (*j)++;
        *i = *j;
    }
    return (special);
}

int    tokenizer(char *line, t_token ***tokens)
{
    size_t  i;
    size_t  j;
    int index;
    t_token **mat = *tokens;

    i = 0;
    j = 0;
    index = 0;
    while(line[j])
    {
        jump_spaces(line, &i, &j);
        while (line[j] && !special_char(line[j]))
        {
            if (mat != NULL && 
                    mat[count_tokens(*tokens) - 1]->sub_type & 
                    (IN | OUT | HEREDOC | APPEND))
            {
                *tokens = add_token(*tokens,
                        create_filename(line, &i, &j, index));
            }
            else
            {
                *tokens = add_token(*tokens,
                        create_cmd(line, &i, &j, index));
            }
            jump_spaces(line, &i, &j);
        }
        index++;
        while (line[j] && special_char(line[j]))
        {
            *tokens = add_token(*tokens,
                    create_special(line, &i, &j, index));
            jump_spaces(line, &i, &j);
            index++;
        }
    }
    return (0);
}
