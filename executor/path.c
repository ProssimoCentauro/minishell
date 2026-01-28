/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:03 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/04 13:03:17 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**look_for_path(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4) != NULL)
		{
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*look_for_rightpath(char **paths, char *com)
{
	int		n;
	char	*temp;
	char	*path;

	n = 0;
	while (paths && paths[n])
	{
		if (access(com, F_OK) == 0 && ft_strncmp(com, "./", 2) == 0)
		 	return (ft_strdup(com));
		if (ft_strcmp(com, "..") == 0)
			return (NULL);
		temp = ft_strjoin(paths[n], "/");
		path = ft_strjoin(temp, com);
		if (access(path, F_OK) == 0)
			return (path);
		free(temp);
		free(path);
		n++;
	}
	return (NULL);
}

char	*findpath(char **env, char *com)
{
	char	**paths;
	char	*right_path;

	paths = look_for_path(env);
	right_path = look_for_rightpath(paths, com);
	free_array(paths);
	return (right_path);
}
