#include "minishell.h"

char	**copy_array(char **array)
{
	char	**copy;
	int		n;
	int		len;

	n = 0;
	len = 0;
	while (array[n])
	{
		if (array[n][0] != '\0')
			len++;
		n++;
	}
	copy = ft_calloc(len + 1, sizeof(char *));
	n = 0;
	len = 0;
	while (array[n])
	{
		if (array[n][0] != '\0')
		{
			copy[len] = ft_strdup(array[n]);
			len++;
		}
		n++;
	}
	copy[len] = NULL;
	return (copy);
}