NAME = minishell

SRC = main.c echo.c cd.c error.c free.c pwd.c export.c exit.c env.c utils.c \
	  ft_getenv.c unset.c wildcards.c tokens_utils.c tokens_utils2.c tokens_reorder.c \
	  tree_builder.c tokenizer.c token_args_utils.c executor.c path.c executor_info.c\
	  pipex.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4

INCLUDE = -Ilibft/header_files -I/usr/include

LIBFLAGS = -Llibft -lft -L/usr/lib

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
#	make bonus -C libft
	$(CC) $(OBJ) $(CFLAGS) $(LIBFLAGS) -o $(NAME) -lreadline -lncurses

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean:
	rm -f $(OBJ) $(NAME)
	make fclean -C libft

re: fclean $(NAME)

.PHONY: all clean fclean re
