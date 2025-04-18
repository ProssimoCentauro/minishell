/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:34:46 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/17 20:34:48 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_prompt(void)
{
	char	*buf;
	char	*end;
	int		len;
	int		copy;
	char	*prompt;

	copy = 0;
	buf = malloc(1024 * sizeof(char));
	getcwd(buf, 1024);
	len = ft_strlen(buf);
	end = buf + ft_strlen(buf);
	while (*end != '/')
	{
		end--;
		copy++;
	}
	prompt = ft_substr(buf, len - copy, len - copy);
	free(buf);
	buf = NULL;
	buf = ft_strjoin(prompt, " ---> ");
	return (free(prompt), buf);
}
