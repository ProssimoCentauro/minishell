/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtodaro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:18 by rtodaro           #+#    #+#             */
/*   Updated: 2025/04/14 16:32:01 by rtodaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create a new token
t_token	*create_token(void *content, t_type type, t_type sub_type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->quotes = 0;
    	token->args = NULL;
    	token->index = 0;
	token->content = content;
	token->type = type;
	token->sub_type = sub_type;
	token->left = NULL;
	token->right = NULL;
	return (token);
}

// Add a token to the array
t_token	**add_token(t_token **arr, t_token *token)
{
	size_t	size;
	t_token	**new_arr;

	size = count_tokens(arr);
	new_arr = ft_calloc(sizeof(t_token *), size + 2);
	if (!new_arr)
		return (NULL);
	copy_arr(new_arr, arr, size);
	new_arr[size] = token;
	new_arr[size + 1] = NULL;
	free(arr);
	return (new_arr);
}

// Copy the elements from arr to new_arr
void	copy_arr(t_token **new_arr, t_token **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		new_arr[i] = arr[i];
		i++;
	}
}

// Free tokens array
void	free_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
        	if (tokens[i]->args != NULL)
		{
			free(tokens[i]->args);
			tokens[i]->args = NULL;
		}
		free(tokens[i]->content);
		tokens[i]->content = NULL;
		free(tokens[i]);
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

t_token **add_token_at(t_token **arr, t_token *token, size_t index)
{
    size_t  size;
    t_token **new_arr;
    size_t  i;

    if (!token)
        return (arr);

    size = count_tokens(arr);

    if (index > size)
        index = size; // se index è troppo grande, aggiunge in fondo

    new_arr = ft_calloc(sizeof(t_token *), size + 2); // +1 per nuovo token, +1 per NULL
    if (!new_arr)
        return (NULL);

    // Copia gli elementi prima della posizione desiderata
    i = 0;
    while (i < index)
    {
        new_arr[i] = arr[i];
        i++;
    }

    // Inserisce il nuovo token
    new_arr[i] = token;
    i++;

    // Copia il resto degli elementi (dopo l'inserimento)
    while (i <= size)
    {
        new_arr[i] = arr[i - 1];
        i++;
    }

    new_arr[size + 1] = NULL;

    free(arr);
    return (new_arr);
}

t_token **remove_token_at(t_token **arr, size_t index)
{
    size_t  size;
    t_token **new_arr;
    size_t  i;
    size_t  j;

    if (!arr)
        return (NULL);

    size = count_tokens(arr);
    if (index >= size)
        return (arr); // indice fuori range, non fa nulla

    new_arr = ft_calloc(sizeof(t_token *), size); // -1 per il token rimosso, +1 per NULL
    if (!new_arr)
        return (NULL);

    i = 0;
    j = 0;
    while (i < size)
    {
        if (i != index)
        {
            new_arr[j] = arr[i];
            j++;
        }
        else
        {
            free_token(arr[i]);
        }
        i++;
    }

    new_arr[size - 1] = NULL;
    free(arr);
    return (new_arr);
}

