NAME = minishell

#compiler
AARCH64 = aarch64-linux-gnu-gcc -o mio_programma
CC = cc
CLFAGS = -Wall -Wextra -Werror
IFLAGS = -I ./libft/header_files

all: $(NAME)

minishell:
	$(CC) -Wall -Wextra -Werror $(IFLAGS) *.c -gdwarf-4 -lreadline ./libft/libft.a -o mini

