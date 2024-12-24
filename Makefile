NAME = philo
SRC = main.c error.c free.c init.c utils.c eat.c think.c monitoring.c \
	  one_philo_simulation.c simulation.c status.c
SRC_FILES = $(addprefix src/, $(SRC))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
INCLUDE = -I./include -I./libft
LINKING = -Llibft -lft

all: $(NAME)

$(NAME): $(SRC_FILES)
	make -C ./libft
	$(CC) $(INCLUDE) $(CFLAGS) $(SRC_FILES) -o $(NAME) $(LINKING)

clean:
	make -C ./libft clean
	$(RM) *.o

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHOMY: all clean fclean re
