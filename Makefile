NAME = mini

SRC = main.c echo.c cd.c error.c free.c pwd.c export.c exit.c env.c utils.c \
		ft_getenv.c unset.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -Ilibft -I/usr/include

LIBFLAGS = -Llibft -lft -L/usr/lib

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make bonus -C libft
	$(CC) -lreadline $(OBJ) $(LIBFLAGS) -o $(NAME)

%.o:%.C
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean:
	rm -f $(OBJ) $(NAME)
	make fclean -C libft

re: fclean $(NAME)

.PHONY: all clean fclean re