/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:03:13 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/12 12:00:28 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_previous_directory(char *curr_dir)
{
	char	*end;
	char	*prev;
	int		len;

	len = ft_strlen(curr_dir);
	end = curr_dir + len;
	while (*end != '/')
	{
		end--;
		len--;
	}
	prev = ft_substr(curr_dir, 0, len);
	if (*prev == '\0')
	{
		prev = malloc(2 *(sizeof(char)));
		*prev = '/';
		*(prev + 1) = '\0';
	}
	return (prev);
}

void	cd(char **str, t_data *data)
{
	int		n;
	char	*new_dir;
	char	*curr_dir;

	n = 0;
	curr_dir = malloc(1024 * (sizeof(char)));
	getcwd(curr_dir, 1024);
	new_dir = NULL;
	if (!str || !str[n] || str[n][0] == '~')
	{
		chdir(getenv("HOME"));
		data->exit_status = 0;
	}
	else if (str[1] != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		data->exit_status = 1;
	}
	else if (ft_strncmp(str[n], "..", ft_strlen("..")) == 0)
	{
		new_dir = get_previous_directory(curr_dir);
		data->exit_status = 0;
		check_error(chdir(new_dir), "cd: ", new_dir, data);
		free(new_dir);
	}
	else
		check_error(chdir(str[n]), "cd: ", str[n], data);
	free(curr_dir);
}
