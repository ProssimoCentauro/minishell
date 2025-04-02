#include "minishell.h"

// Reorder the tokens array with redirections
void    reorder_tokens(t_token **tokens)
{
    long  i;
    long  j;
    t_token *temp;

    j = 0;
    i = 0;
    while (tokens[i])
    {
        i = j;
        while (tokens[i] && tokens[i]->type == CMD)
            i++;
        if (tokens[i] && tokens[i]->sub_type
                & (IN | OUT | HEREDOC | APPEND | FILENAME | LIMITER))
        {
            temp = tokens[i];
            while (i > j)
            {
                tokens[i] = tokens[i - 1];
                i--;
            }
            tokens[i] = temp;
            j++;
        }
        else
        {
            if (tokens[i] != NULL)
            {
                i++;
                j = i;
            }
        }
    }
}

// Assign the right index to every token in the array
void    assign_index(t_token **tokens)
{
    size_t  i;
    size_t  index;
    t_type  temp_sub;
    
    i = 0;
    index = 0;
    tokens[i]->index = index;
    temp_sub = tokens[i]->sub_type;
    i++;
    while (tokens[i])
    {
	    if (temp_sub & (CMD) && tokens[i]->sub_type & (CMD))
            	tokens[i]->index = index;
	    else
	    {
            	tokens[i]->index = i;
		index = i;
            }	
	temp_sub = tokens[i]->sub_type;
        i++;
    }
}
/*
void	get_vars(t_token **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if ()
	}
}*/
