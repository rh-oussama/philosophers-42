NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = main.c utils.c creat_philo.c philo_eat.c utils_2.c
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -rf $(NAME)

clean: 
	rm -rf $(OBJS)

re: fclean all
