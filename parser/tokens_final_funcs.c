#include "minishell.h"

int	write_on_file(int fd2, char *delimiter, t_token **tokens);


int forbidden_symbols(char c)
{
    const char *special_symbols = "-!@$#%^&*()+={}[]|\\:;\"'<>,.?";

    if (ft_strchr(special_symbols, c) != NULL)
	    return (1);
    return (0);
}

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

/* bisogna implementare la funzione che leva le virgolette per il delimiter*/
int     write_on_file(int fd, char *delimiter, t_token **tokens)
{
        (void)tokens;
        char    *line;
        int     ret;

        ret = 0;
        while (1)
        {
                line = readline(">");
                //line = get_next_line(0);
                //printf("\"%s\"", line);
                if (!line)
                {
                        printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
                        return (1);
                }
                /*if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
                && *(line + ft_strlen(delimiter)) == '\n')*/
                if (!ft_strcmp(line, delimiter))
                {
                        free (line);
                        break ;
                }
                write(fd, line, ft_strlen(line));
                free (line);
        }
        return (ret);
}


static int check_heredoc(t_token **tokens, size_t *i)
{
    int fd;
    char    *temp_file;
    char    *str_i;
    int ret;
    pid_t       pid;

    (*i)++;
    str_i = ft_itoa((int)*i);
    temp_file = ft_strjoin("./temp_files/temp_", str_i);
    free(str_i);
    fd = open(temp_file, O_CREAT | O_RDWR, 0644);
    pid = fork();
    if (pid == 0)
    {
        g_last_signal = 0;
        signal_manager(SIGINT, handle_heredoc);
        ret = write_on_file(fd, (char *)tokens[*i]->content, tokens);
        close(fd);
        free(tokens[*i]->content);
        tokens[*i]->content = ft_strdup(temp_file);
        free(temp_file);
    }
    waitpid(pid, &ret, 0);
    if (ret == 256)
    {
            ret = 512;
            close(fd);
            free(tokens[*i]->content);
            tokens[*i]->content = ft_strdup(temp_file);
            free(temp_file);
            g_last_signal = 0;
    }
    else
            (*i)++;
    return (ret);
}


char *ft_strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
	i++;
    }
    return dest;
}


char *replace_range(char *s1, char *s2, size_t i, size_t j)
{
    size_t len1;
    size_t len2;
    size_t new_len;
    char *result;

    len1 = ft_strlen(s1);
    if (i > j || j >= len1)
        return (NULL);
    len2 = ft_strlen(s2);
    new_len = i + len2 + (len1 - j - 1);
    result = malloc(new_len + 1);
    if (!result)
	    return (NULL);
    ft_strncpy(result, s1, i);
    ft_strcpy(result + i, s2);
    ft_strcpy(result + i + len2, s1 + j + 1);
    free(s1);
    free(s2);
    return (result);
}

static int	check_export(t_token **tokens, size_t *i, t_data *data)
{
	char	*line;
	char	*var;
	char	*sub_str;
	size_t	j;
	size_t	k;
	//size_t	temp;

	line = (char *)tokens[*i]->content;
	j = 0;
	k = 0;

	while (line[j])
	{
		if (line[j] == '$')
		{
			k = ++j;
			if (line[j] && line[j] != '?')
			{
				while  (line[j] && line[j] != ' ' && line[j] != '\'' && line[j] != '"'
					&& line[j] != '$' && !forbidden_symbols(line[j]))
				j++;
			}
			else if (!line[j] || line[j] == ' ' || line[j] == '\'' || line[j] == '"'
					|| line[j] == '$' || !forbidden_symbols(line[j]))
				continue ;
			if (j != k)
			{
				sub_str = create_str(line, k, j - 1);
				var = ft_getenv(sub_str, data->env);
				if (!var)
					var = ft_strdup("");
				free(sub_str);
				line = replace_range(line, var, k - 1, j - 1);
			}
			else if (line[j] == '?' && line[k] == '?')
			{
				var = ft_itoa(WEXITSTATUS(data->exit_status));
				line = replace_range(line, var, k - 1, j);
			}
			else if (line[j] == line[k])
			{
				j++;
				k++;
			}
			else
				j = 0;
		}
		else if (line[j] == '"')
		{
			while(line[++j] && line[j] != '"' && !forbidden_symbols(line[j]))// && line[j] != '\'')
			{
				if (line[j] == '$')
                		{
                        		k = ++j;
					if (line[j] && line[j] != '?')
					{
						while  (line[j] && line[j] != ' ' && line[j] != '\'' && line[j] != '"'
							&& line[j] != '$' && !forbidden_symbols(line[j]))
						j++;
					}
					else if (!line[j] || line[j] == ' ' || line[j] == '\'' || line[j] == '"'
							|| line[j] == '$' || !forbidden_symbols(line[j]))
						continue ;
					if (j != k)
					{
						sub_str = create_str(line, k, j - 1);
						var = ft_getenv(sub_str, data->env);
						if (!var)
							var = ft_strdup("");
						free(sub_str);
						line = replace_range(line, var, k - 1, j - 1);
					}
					else
					{
						var = ft_itoa(WEXITSTATUS(data->exit_status));
						line = replace_range(line, var, k - 1, j);
					}
					j = 0;
				}
			}
			if (line[j] == '"')
				j++;
		}
		else if (line[j] == '\'')
		{
			j++;
			while (line[j] && line[j] != '\'')
				j++;
			j++;
		}
		else
			j++;
		tokens[*i]->content = line;
	}
	return (0);
}


int	finalize_tokens(t_token **tokens, t_data *data)
{
	size_t	i;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->sub_type & (CMD | FILENAME))
			check_export(tokens, &i, data);
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->sub_type == HEREDOC)
		{
			if (check_heredoc(tokens, &i) == 512)
				return (512);
		}
		else
			i++;
	}
	return (0);
}
