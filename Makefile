NAME = life

CC = cc
FLAGS = -Wall -Werror -Wextra
SRC = life.c main.c
OBJ = $(SRC:.c=.o)

#INPUT
INPUT ?= ssdxdd
ARGS  ?= 5 5 5

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c life.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	echo '$(INPUT)' | valgrind ./$(NAME) $(ARGS) | cat -e