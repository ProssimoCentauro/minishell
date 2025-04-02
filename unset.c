#include "minishell.h"

void	ft_unset(char **var, char ***env)
{
	int		i;
	int		len;
	//char	**temp;
	char	*to_delete;

	i = 0;
	if (!(*var))
		return ;
	if (ft_getenv(*var, *env))
	{
		len = ft_strlen(*var);
		while (ft_strncmp((*env)[i], *var, len) != 0 && \
		((*env)[i][len + 1] != '=' || (*env)[i][len + 1] != '\0'))
			i++;
		to_delete = (*env)[i];
		(*env)[i] = ft_strdup("");
		free(to_delete);
		//temp = *env;
		*env = copy_array(*env);
		//free_array(temp);
	}
}