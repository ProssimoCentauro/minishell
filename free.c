#include "minishell.h"

void free_array(char **str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		free (str[n]);
		n++;
	}
	free(str);
}