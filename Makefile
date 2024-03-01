SOURCE_FILES =	ft_here_doc.c \
				ft_minishell.c \
				ft_mini_utils.c \
				get_next_line.c \
				ft_main_bonus.c \
				ft_split_bonus.c \
				ft_childs_bonus.c \
				ft_command_bonus.c \
				get_next_line_utils.c \
				ft_pipex_utils_bonus.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(SOURCE_FILES:.c=.o)

NAME = Minishell

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

git: fclean
	git add .
	git status
	@read -p "Quieres continuar? [y/n]: " answer; \
	if [ "$$answer" = "y" ]; then \
		read -p "Mensaje para el commit: " message; \
		git commit -m "$$message"; \
		git push; \
	fi

.PHONY: re fclean clean all bonus