#include "minishell.h"

char	*set_prompt()
{
	char	*buf;
	char	*end;
	int		len;
	int		copy;
	char	*prompt;

	copy = 0;
	buf = malloc(1024 * sizeof(char));
	getcwd(buf, 1024);
	len = ft_strlen(buf);
	end = buf + ft_strlen(buf);
	while (*end != '/')
	{
		end--;
		copy++;
	}
	prompt = ft_substr(buf, len - copy, len - copy);
	return (free(buf), prompt);
}	
