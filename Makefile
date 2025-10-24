NAME = Sokoban

SRCS = 	main.c \
		Functions/level.c \
		Functions/entity.c

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all