/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:32:34 by ldei-sva          #+#    #+#             */
/*   Updated: 2024/12/24 05:09:35 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*setmemory(char *stack, int len)
{
	char	*temp;
	int		i;

	i = 0;
	if (stack && len == ft_strlen(stack))
	{
		free (stack);
		stack = NULL;
	}
	else if (stack)
	{
		temp = stack;
		stack = malloc ((ft_strlen(stack) + 1) * (sizeof(char)));
		while (temp[len])
		{
			stack[i] = temp[len];
			i++;
			len++;
		}
		stack[i] = '\0';
		free (temp);
	}
	return (stack);
}

char	*createstr(int index, char *fileread, char *line)
{
	int		i;

	line = malloc((index + 2) * (sizeof(char)));
	i = 0;
	while (fileread[i] != '\n' && fileread[i] != '\0')
	{
		line[i] = fileread[i];
		i++;
	}
	if (fileread[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else if (fileread[i] == '\0')
		line[i] = '\0';
	return (line);
}

char	*search_for_newline(char *stack, char *line)
{
	int		index;

	index = 0;
	while (stack[index] != '\n' && stack[index] != '\0')
		index++;
	line = createstr(index + 1, stack, line);
	return (line);
}

int	readfile(int fd, char *fileread)
{
	int	byte_read;

	byte_read = read(fd, fileread, BUFFER_SIZE);
	if (byte_read < 0)
		return (-1);
	fileread[byte_read] = '\0';
	return (byte_read);
}

char	*get_next_line(int fd)
{
	static char		*stack[1024];
	char			*fileread;
	int				byte_read;
	char			*line;

	line = NULL;
	fileread = malloc (BUFFER_SIZE + 1);
	if (fileread == NULL || fd < 0)
		return (free(fileread), NULL);
	byte_read = 1;
	while (is_there_newline(stack[fd]) == 0)
	{
		byte_read = readfile(fd, fileread);
		if (byte_read == -1 || (!stack[fd] && byte_read == 0))
			return (free (fileread), NULL);
		if (byte_read == 0)
			break ;
		stack[fd] = freestack(stack[fd], fileread);
	}
	line = search_for_newline(stack[fd], line);
	stack[fd] = setmemory(stack[fd], ft_strlen(line));
	return (free (fileread), line);
}
