SOURCE_FILES =	ft_quotes.c \
				ft_take_comm.c \
				ft_utils_quotes.c \
				ft_double_quotes.c \
				# ft_remove_quotes.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

OBJECTS = $(SOURCE_FILES:.c=.o)

NAME = Quotes

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all bonus