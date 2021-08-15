.PHONY: all re fclean clean obj_dir

NAME = philo_one

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include

OBJDIR = .obj
SRC_DIR = src

SOURCES = 	cycle.c  data.c   error.c  main.c   mutex.c \
			parser.c philo.c  print.c  thread.c time.c \
			utils.c

OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: objdir $(NAME)

objdir:
	@if ! [ -d ${OBJDIR} ] ; then mkdir ${OBJDIR} ; fi

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -lpthread -o $@

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $? $(INCLUDE) -o $@ 

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
