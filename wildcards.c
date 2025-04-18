/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:30:18 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/18 11:52:36 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_compare(char **str, char **file)
{
	char	c;

	if (**str == '\'' || **str == '"')
	{
		c = **str;
		(*str)++;
		while (**str != c)
		{
			if (**str != **file)
				return ;
			(*str)++;
			(*file)++;
		}
		(*str)++;
	}
}

int	check_corrispondency(char *str, char *file)
{
	char	c;

	while (*str != '*')
	{
		quote_compare(&str, &file);
		if (*str == '*')
			break ;
		if (*str != *file)
			return (1);
		if (!(*str))
			return (0);
		file++;
	}
	while (*str == '*')
		str++;
	c = *str;
	if (*str == '\'' || *str == '"')
		c = *(str + 1);
	while (*file != c)
	{
		if (!(*file))
			return (1);
		file++;
	}
	return (check_corrispondency(str, file));
}

int	len_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	int				len;

	len = 0;
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	while (info != NULL)
	{
		if (info->d_type == DT_REG || info->d_type == 0 || info->d_name[0] == '.')
			if (check_corrispondency(str, info->d_name) == 0)
				if (info->d_name[0] != '.' || (info->d_name[0] == '.' && str[0] == '.'))
					len++;
		info = readdir((curr_dir));
	}
	closedir(curr_dir);
	if (len == 0)
		return (1);
	return (len);
}

void	insert_wildcards(char	**results, struct dirent *info, char *str, DIR *curr_dir)
{
	int	len;

	len = 0;
	while (info != NULL)
	{
		if (info->d_type == DT_REG || info->d_type == 0 || info->d_name[0] == '.')
		{
			if (check_corrispondency(str, info->d_name) == 0)
			{
				if (info->d_name[0] != '.' || (info->d_name[0] == '.' && str[0] == '.'))
				{
					results[len] = ft_strdup(info->d_name);
					len++;
				}
			}
		}
		info = readdir((curr_dir));
	}
	results[len] = NULL;
	if (!(*results))
	{
		remove_quotes(str);
		results[0] = ft_strdup(str);
		results[1] = NULL;
	}
}


char	**find_wildcards(char *str)
{
	DIR				*curr_dir;
	struct dirent	*info;
	char			**results;
	int				len;

	len = len_wildcards(str);
	results = malloc((len + 1) * (sizeof(char *)));
	curr_dir = opendir(".");
	if (curr_dir == NULL)
		perror("opendir");
	info = readdir((curr_dir));
	insert_wildcards(results, info, str, curr_dir);
	closedir(curr_dir);
	return (sort_array(results));
}
