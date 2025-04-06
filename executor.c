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

void	set_command(t_execute *info, t_token *tree)
{
	int	i;

	i = 0;
	info->com = (char *)tree->content;
	while (tree->args && tree->args[i])
		i++;
	info->args = malloc((i + 2) * (sizeof(char *)));
	i = 0;
	info->args[0] = (char *)tree->content;
	while (tree->args && tree->args[i])
	{
		info->args[i + 1] = (char *)(tree->args[i]->content);
		i++;
	}
	info->args[i + 1] = NULL;
}

void	executor(t_token *tree, char **env, t_execute *info)
{
	if (!tree)
		return ;
	executor(tree->left, env, info);
	if (tree->sub_type == PIPE)
		info->pipe = 1;
	if (tree->type == DELIMETER || tree->sub_type == PIPE)
	{
		print_info(info);
		execve_cmd(info, env);
		set_info(info);
	}
	if (tree->sub_type == IN && info->file_in != -1)
		info->file_in = open(info->filename, O_RDWR);
	if (tree->sub_type == OUT && info->file_in != -1)
		info->file_out = open(info->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tree->sub_type == APPEND && info->file_in != -1)
		info->file_out = open(info->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (tree->type == FILENAME && info->file_in != -1)
		info->filename = (char *)tree->content;
	if (tree->type == CMD)
		set_command(info, tree);
	executor(tree->right, env, info);
}
