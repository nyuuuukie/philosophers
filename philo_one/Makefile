.PHONY: all re fclean clean obj_dir

NAME = philo_one

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include

OBJDIR = .obj
SRC_DIR = src

SOURCES = 	main.c \
			ft_time.c \
			ft_atoi.c \
			ft_cycle.c \
			ft_philo.c \
			ft_mutex.c \
			ft_strlen.c \
			ft_errors.c \
			ft_threads.c \
			ft_print_status.c \
 			ft_get_arguments.c 

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
