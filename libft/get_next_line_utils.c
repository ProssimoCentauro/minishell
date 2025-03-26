/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:37:23 by ldei-sva          #+#    #+#             */
/*   Updated: 2024/12/24 04:07:12 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freestack(char *stack, char *fileread)
{
	char	*temp;

	temp = stack;
	stack = get_strjoin(stack, fileread);
	if (temp)
		free (temp);
	return (stack);
}

int	is_there_newline(char *stack)
{
	int	i;

	i = 0;
	if (!stack)
		return (0);
	while (stack[i])
	{
		if (stack[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_strjoin(char *stack, char *fileread)
{
	char	*temp;
	int		size;
	int		i;
	int		i2;

	size = get_strlen(stack) + get_strlen(fileread);
	i = 0;
	i2 = 0;
	temp = malloc ((size + 1) * (sizeof(char)));
	while (stack && stack[i])
	{
		temp[i] = stack[i];
		i++;
	}
	while (fileread[i2])
	{
		temp[i] = fileread[i2];
		i2++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

int	get_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		i++;
		str++;
	}
	return (i);
}
