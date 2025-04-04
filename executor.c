/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:07:01 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/04 13:25:36 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_token *tree, char **env)
{
	char	*path;

	if (!tree)
		return ;
	executor(tree->left, env);
	if (tree->type == CMD)
	{
		printf("%s\n", (char *)tree->content);
		path = findpath(env, (char *)tree->content);
		ft_printf("%s\n", path);
	}
	executor(tree->right, env);
}
