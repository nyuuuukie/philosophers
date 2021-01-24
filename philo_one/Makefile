.PHONY: all re fclean clean obj_dir

NAME = philo_one

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include

OBJDIR = .obj
SRC_DIR = src

SOURCES = main.c ft_atoi.c
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -lpthread -o $@

$(OBJDIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $? $(INCLUDE) -o $@ 

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
