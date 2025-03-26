#include "minishell.h"

void check_error(int n)
{
	if (n == -1)
		perror("Error");
}