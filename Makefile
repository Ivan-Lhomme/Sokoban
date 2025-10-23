NAME = Sokoban

SRCS = 	main.c \
		Functions/level.c

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all