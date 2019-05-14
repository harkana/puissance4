NAME=puissance4
CC=gcc
SRC=	src/main.c \
	src/game.c \
	src/readline.c \
	src/empty.c
OBJ=$(SRC:%.c=%.o)
RM=rm -f
CFLAGS=-W -Wall -Werror -Wextra

all:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
