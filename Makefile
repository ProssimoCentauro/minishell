NAME = minishell

PARSER = ./parser/

SRC = main.c echo.c cd.c error.c free.c pwd.c export.c exit.c env.c utils.c \
	  ft_getenv.c unset.c wildcards.c $(PARSER)tokens_utils.c $(PARSER)tokens_utils2.c $(PARSER)tokens_reorder.c \
	  $(PARSER)tree_builder.c $(PARSER)tokenizer.c $(PARSER)token_args_utils.c $(PARSER)tokens_final_funcs.c\
	  executor.c path.c executor_info.c pipex.c $(PARSER)check_input.c errors_utils.c set_prompt.c\
	  signal_handlers.c expand_input.c ft_arrayjoin.c initial_configuration.c $(PARSER)quotes_utils.c\
	  fd_utils.c export_utils.c $(PARSER)check_next.c $(PARSER)create_special.c \
	  $(PARSER)create_cmd.c $(PARSER)tokenizer_utils.c $(PARSER)select_handler.c \
	  $(PARSER)write_on_file.c $(PARSER)check_heredoc.c $(PARSER)tokens_final_funcs_utils.c\
	  $(PARSER)process_string.c

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
