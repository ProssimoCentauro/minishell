#include "minishell.h"

int	syntax_error(t_token **tokens, t_token *check)
{
	if (!check)
		return (0);
	if (check->quotes == 1)
		ft_putstr_fd("minishell: syntax error unclosed quotes\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd((char *)check->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	free_tokens(tokens);
	return (1);
}
