#include "minishell.h"

void	write_on_file(int fd2, char *delimiter);


int ft_numlen(int n)
{
    int i;

    i = 0;
    if (n == 0)
        return (1);
    if (n < 0)
        n = -n;
    while (n > 0)
    {
        n = n / 10;
        i++;
    }
    return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*ret;
	const char	*digits = "0123456789";

	len = ft_numlen(n);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = 0;
	if (n == 0)
		ret[0] = '0';
	if (n < 0)
		ret[0] = '-';
	while (n)
	{
		if (n > 0)
			ret[--len] = digits[n % 10];
		else
			ret[--len] = digits[n % 10 * -1];
		n /= 10;
	}
	return (ret);
}

int check_heredoc(t_token **tokens)
{
    size_t  i;
    int fd;
    char    *temp_file;
    char    *str_i;

    i = 0;
    while (tokens[i])
    {
        if (tokens[i] && tokens[i]->sub_type == HEREDOC)
        {
            i++;
            str_i = ft_itoa((int)i);
            temp_file = ft_strjoin("./temp_file/temp_", str_i);
            free(str_i);
            fd = open(temp_file, O_CREAT | O_RDWR, 0644);
            write_on_file(fd, (char *)tokens[i]->content);
            close(fd);
            free(tokens[i]->content);
            tokens[i]->content = ft_strdup(temp_file);
            free(temp_file);
            i++;
        }
        else
            i++;
    }
    return (0);
}

void	write_on_file(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			return ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
                && *(line + ft_strlen(delimiter)) == '\n')
		{
			free (line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free (line);
	}
}
