NAME = minishell

LEXF = ./parser/

SRC = main.c echo.c cd.c error.c free.c pwd.c export.c exit.c env.c utils.c \
	  ft_getenv.c unset.c wildcards.c $(LEXF)tokens_utils.c $(LEXF)tokens_utils2.c $(LEXF)tokens_reorder.c \
	  $(LEXF)tree_builder.c $(LEXF)tokenizer.c $(LEXF)token_args_utils.c $(LEXF)tokens_final_funcs.c\
	  executor.c path.c executor_info.c pipex.c $(LEXF)check_input.c errors_utils.c set_prompt.c\
	  signal_handlers.c expand_input.c ft_arrayjoin.c initial_configuration.c\

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -gdwarf-4

INCLUDE = -Ilibft/header_files -I/usr/include -I./includes

LIBFLAGS = -Llibft -lft -L/usr/lib

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
#	make bonus -C libft
	$(CC) $(OBJ) $(LIBFLAGS) -o $(NAME) -lreadline -lncurses -g

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
