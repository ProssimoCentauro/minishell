NAME = minishell

#compiler
CC = cc
CLFAGS = -Wall -Wextra -Werror
IFLAGS = -I ./libft/header_files

all: $(NAME)

minishell:
	$(CC) $(CFLAGS) $(IFLAGS) *.c -g -lreadline

