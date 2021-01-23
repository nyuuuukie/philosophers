.PHONY: all re fclean clean

NAME = philo_one

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = main.c ft_atoi.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $(SOURCES)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
