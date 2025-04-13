#include "minishell.h"

static void handle_cmd(t_token **tokens, t_token **root, t_token **last, size_t *i)
{
    if (*root == NULL)
        *root = tokens[*i];
    else if (*i > 0 && tokens[*i - 1]->type != CMD)
        (*last)->right = tokens[*i];
    *last = tokens[*i];
}

static void handle_delimiter(t_token **tokens, t_token **root, t_token **last, size_t *i)
{
    t_token *temp;

    temp = *root;
    *root = tokens[*i];
    (*root)->left = temp;
    *last = *root;
}

static void handle_pipe(t_token **tokens, t_token **root, t_token **last, size_t *i)
{
    t_token *temp;
   if ((*root)->type & (CMD | REDIRECT))
   {
           temp = *root;
           *root = tokens[*i];
           tokens[*i]->left = temp;
           *last = *root;
           return ;
   }
    temp = (*root)->right;
    (*root)->right = tokens[*i];
    tokens[*i]->left = temp;
    *last = tokens[*i];
}

static void handle_arrows(t_token **tokens, t_token **root, t_token **last, size_t *i)
{
        t_token *temp;

        if (*root == NULL)
                *root = tokens[*i];
        else
        {
                temp = (*last)->right;
                (*last)->right = tokens[*i];
                (tokens[*i])->right = temp;
        }
        *last = tokens[*i];
        *i = *i + 1;
        (*last)->left = tokens[*i];
}

static void handle_open(t_token **tokens, t_token **root, t_token **last, size_t *i)
{
	if (*root == NULL)
		*root = tokens[*i];
	else if (*i > 0 && tokens[*i - 1]->type != CMD)
		(*last)->right = tokens[*i];
	*last = tokens[*i];
}

static void handle_close(t_token **tokens, t_token **root, t_token **last, size_t *i)
{
	size_t j;

	j = *i - 1;
	if (*root == NULL)
		*root = tokens[*i];
	while (tokens[j]->index == tokens[j - 1]->index)
		j--;
	*last = tokens[j];
	(*last)->right = tokens[*i];
	*last = tokens[*i];
}

t_token *build_tree(t_token **tokens, size_t *i)
{
    t_token *root = NULL;
    t_token *last = NULL;

    while (tokens[*i])
    {
        if (tokens[*i]->type == CMD)
            handle_cmd(tokens, &root, &last, i);
        else if (tokens[*i]->type & DELIMETER)
            handle_delimiter(tokens, &root, &last, i);
        else if (tokens[*i]->sub_type & PIPE)
            handle_pipe(tokens, &root, &last, i);
        else if (tokens[*i]->sub_type & (IN | OUT | APPEND | HEREDOC))
            handle_arrows(tokens, &root, &last, i);
        else if (tokens[*i]->sub_type & (OPEN))
        {
		handle_open(tokens, &root, &last, i);
                (*i)++;
                if (!root)
                        root = build_tree(tokens, i);
                else
                        last->right = build_tree(tokens, i);
		handle_close(tokens, &root, &last, i);
        }
        else if (tokens[*i]->sub_type & (CLOSE))
                return (root);
        (*i)++;
    }

    return (root);
}
