/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:59:28 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/04/19 15:02:59 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token **tokens, t_token *check)
{
	if (!check)
		return (0);
	if (check->quotes == 1)
		ft_putstr_fd("minishell: syntax error \
unclosed quotes\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: syntax error near \
unexpected token `", STDERR_FILENO);
		ft_putstr_fd((char *)check->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	free_tokens(tokens);
	return (1);
}
