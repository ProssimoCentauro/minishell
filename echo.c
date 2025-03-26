#include "minishell.h"

void	ft_echo(char **str)
{
	int	n;
	int	newline;

	n = 0;
	newline = 1;
	if (!str || !str[n])
		return ;
	while (ft_strncmp(str[n], "-n", ft_strlen("-n")) == 0)
	{
		n++;
		newline = 0;
	}
	while (str[n])
	{
		ft_printf("%s", str[n]);
		if (str[n + 1] != NULL)
			ft_printf("%s", " ");
		n++;
	}
	if (newline == 1)
		ft_printf("%s", "\n");
	free_array(str);
}