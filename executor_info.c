#include "minishell.h"

void	set_info(t_execute *info)
{
	info->com = NULL;
	info->file_in = 0;
	info->file_out = 0;
	info->pipe = 0;
	info->args = calloc(1, sizeof(char *));
	info->filename = NULL;
}

void	print_info(t_execute *info)
{
	int i;

	i = 0;
	printf("com: %s\n", info->com);
	while (info->args[i])
	{
		printf("arg %d: %s\n", i, info->args[i]);
		i++;
	}
	printf("pipe: %d\n", info->pipe);
	printf("file in: %d\n", info->file_in);
	printf("file out: %d\n\n", info->file_out);
}