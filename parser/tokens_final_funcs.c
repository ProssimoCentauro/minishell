#include "minishell.h"

int			write_on_file(int fd2, char *delimiter, t_token **tokens,
				t_data *data);

int	forbidden_symbols(char c)
{
	const char	*special_symbols = "-!@$#%^&*()+={}[]|\\:;\"'<>,.? ";

	if (ft_strchr(special_symbols, c) != NULL)
		return (1);
	return (0);
}

int	ft_numlen(int n)
{
	int	i;

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

static int	check_quotes_in_delimiter(char *delimiter)
{
	return (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''));
}

static void	print_warning(char *delimiter)
{
	printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
		delimiter);
}

static char	*get_line(char *delimiter)
{
	char	*line;

	line = readline(">");
	if (!line)
	{
		print_warning(delimiter);
		return (NULL);
	}
	return (line);
}

static void	process_line(int fd, char *line, int flag, t_data *data)
{
	if (flag == 0)
		line = check_export2(line, data);
	write(fd, line, ft_strlen(line));
	free(line);
}

int	write_on_file(int fd, char *delimiter, t_token **tokens, t_data *data)
{
	char	*line;
	int		ret;
	int		flag;

	(void)tokens;
	ret = 0;
	flag = check_quotes_in_delimiter(delimiter);
	remove_quotes(delimiter);
	while (1)
	{
		line = get_line(delimiter);
		if (!line)
			return (0);
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		process_line(fd, line, flag, data);
	}
	return (ret);
}

static char	*generate_temp_filename(size_t *i)
{
	char	*str_i;
	char	*temp_file;

	str_i = ft_itoa((int)*i);
	temp_file = ft_strjoin("./temp_files/temp_", str_i);
	free(str_i);
	return (temp_file);
}

static int	handle_heredoc_child(int fd, t_token **tokens, size_t *i,
		t_data *data)
{
	g_last_signal = 0;
	signal_manager(SIGINT, handle_heredoc);
	return (write_on_file(fd, (char *)tokens[*i]->content, tokens, data));
}

static void	handle_heredoc_parent(int pid, int *ret)
{
	waitpid(pid, ret, 0);
}

static void	update_token_content(t_token **tokens, size_t *i, char *temp_file)
{
	free(tokens[*i]->content);
	tokens[*i]->content = ft_strdup(temp_file);
	free(temp_file);
}

int	check_heredoc(t_token **tokens, size_t *i, t_data *data)
{
	int		fd;
	char	*temp_file;
	int		ret;
	pid_t	pid;

	(*i)++;
	temp_file = generate_temp_filename(i);
	fd = open(temp_file, O_CREAT | O_RDWR, 0644);
	pid = fork();
	if (pid == 0)
	{
		ret = handle_heredoc_child(fd, tokens, i, data);
		exit(ret);
	}
	else
	{
		(*i)++;
		handle_heredoc_parent(pid, &ret);
	}
	(*i)--;
	close(fd);
	update_token_content(tokens, i, temp_file);
	g_last_signal = 0;
	signal_manager(SIGINT, sigint_handler);
	return (ret);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
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
	return (dest);
}

char	*replace_range(char *s1, char *s2, size_t i, size_t j)
{
	size_t	len1;
	size_t	len2;
	size_t	new_len;
	char	*result;

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

static int	move_index(char *line, long *j)
{
	while (line[*j] && !forbidden_symbols(line[*j]))
		(*j)++;
	return (*j);
}

static char	*replace_env_var(char *line, long k, long j, t_data *data)
{
	char	*sub_str;
	char	*var;

	sub_str = create_str(line, k, j - 1);
	var = ft_getenv(sub_str, data->env);
	if (!var)
		var = ft_strdup("");
	free(sub_str);
	line = replace_range(line, var, k - 1, j - 1);
	return (line);
}

static char	*replace_exit_status(char *line, long k, long j, t_data *data)
{
	char	*var;

	var = ft_itoa(data->exit_status);
	return (replace_range(line, var, k - 1, j));
}

char	*process_string(char *line, t_data *data, long *j, long *k)
{
	*k = *j + 1;
	*j = *k;
	if (line[*j] && line[*j] != '?')
		move_index(line, j);
	else if (!line[*j] || !forbidden_symbols(line[*j]))
		return (NULL);
	if (*j != *k)
		line = replace_env_var(line, *k, *j, data);
	else if (line[*j] == '?' && line[*k] == '?')
		line = replace_exit_status(line, *k, *j, data);
	else if (line[*j] == line[*k])
	{
		(*j)++;
		(*k)++;
	}
	*j = -1;
	return (line);
}

static void	skip_single_quotes(char *line, long *j)
{
	(*j)++;
	while (line[*j] && line[*j] != '\'')
		(*j)++;
}

int	iterate_double_quotes(char **line, t_data *data, long *j, long *k)
{
	char	*temp_line;

	while ((*line)[++(*j)] && (*line)[*j] != '"')
	{
		if ((*line)[*j] == '$')
		{
			temp_line = process_string(*line, data, j, k);
			if (!temp_line)
				return (0);
			*line = temp_line;
			return (1);
		}
	}
	return (0);
}

char	*check_export2(char *line, t_data *data)
{
	long	j;
	long	k;
	char	*temp_line;

	j = -1;
	k = 0;
	while (line[++j])
	{
		if (line[j] == '$')
		{
			temp_line = process_string(line, data, &j, &k);
			if (!temp_line)
				continue ;
			line = temp_line;
		}
		else if (line[j] == '"')
		{
			if (iterate_double_quotes(&line, data, &j, &k))
				continue ;
		}
		else if (line[j] == '\'')
			skip_single_quotes(line, &j);
	}
	return (line);
}

int	finalize_tokens(t_token **tokens, t_data *data)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->sub_type == HEREDOC)
		{
			if (check_heredoc(tokens, &i, data) == 256)
			{
				data->exit_status = 130;
				return (256);
			}
		}
		else
			i++;
	}
	return (0);
}
