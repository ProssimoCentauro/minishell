#include "minishell.h"

int	free_data(t_data *data)
{
	if (variables)
		free_array(data->variables);
	if (variables)
		free_array(data->env);
	if (tokens)
		free_tokens(data->tokens);
	return (0);
}
