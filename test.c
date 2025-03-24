#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main()
{
	char	*line;

	while (42)
	{
		printf("~~~~~~~>");
		line = readline(NULL);
		printf("%s\n", line);
	}
	return (0);
}
