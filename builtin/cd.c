/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:03:13 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/20 19:36:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **str, t_data *data, t_execute *info)
{
	char	*new_dir;
	char	*curr_dir;
	char	*temp;

	curr_dir = malloc(1024 * (sizeof(char)));
	getcwd(curr_dir, 1024);
	temp = ft_getenv("HOME", data->env);
	if (!str || !*str || (**str == '~' && str[0][1] == '\0'))
		new_dir = ft_getenv("HOME", data->env);
	else if (str[1] != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		data->exit_status = 1;
		return (free(curr_dir), free(temp));
	}
	else if (**str == '~')
		new_dir = ft_strjoin(temp, *str + 1);
	else
		new_dir = ft_strdup(*str);
	check_error(chdir(new_dir), "cd: ", new_dir, data);
	update_pwd(new_dir, info, data);
	data->exit_status = 0;
	return (free(curr_dir), free(new_dir), free(temp));
}
