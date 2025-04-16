#include "minishell.h"

int	len_w_quote(char *str)
{
	char	c;
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str != c)
			{
				str++;
				len++;
			}
		}
		len++;
		str++;
	}
	return (len);
}

char	*ft_strdup_quote(char *str)
{
	int		len;
	char	c;
	char	*result;
	int		i;

	i = 0;
	len = len_w_quote(str);
	result = malloc(len + 1);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str != c)
			{
				result[i] = *str;
				i++;
			}
			str++;
		}
		if (!(*str))
			break ;
		result[i] = *str;
		i++;
		str++;
	}
	result[i] = '\0';
	return (result);
}
