/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtodaro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:30:27 by rtodaro           #+#    #+#             */
/*   Updated: 2025/03/25 16:30:28 by rtodaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the number of tokens
size_t	count_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
		i++;
	return (i);
}

// Print tokens
void	print_tokens(t_token **tokens)
{
	size_t	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (tokens[i]->content)
			printf("%s\n", (char *)tokens[i]->content);
		else
			printf("(null)\n");
		i++;
	}
}
