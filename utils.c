#include "minishell.h"

char	**copy_array(char **array)
{
	char	**copy;
	int		n;

	n = 0;
	while (array[n])
		n++;
	copy = ft_calloc(n + 1, sizeof(char *));
	n = 0;
	while (array[n])
	{
		copy[n] = ft_strdup(array[n]);
		n++;
	}
	copy[n] = NULL;
	return (copy);
}