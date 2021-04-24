NAME = Minishell

DIR = ./srcs

SRCS = *.c

HEAD = -I include/

FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

MY_VAR = $(shell if [ `uname -s` = "Linux" ]; then echo "$(LINUX)"; else echo "$(OTHER)"; fi)

all: ${NAME}

$(NAME):
	@echo "Création de l'executable..."
	@gcc $(FLAGS) $(HEAD) ${MY_VAR} $(DIR)/$(SRCS) -o $(NAME) -lncurses
	@echo "Compilation terminée !"

LINUX = -D ENABLE_CANON=1

OTHER = -D ENABLE_CANON=2

clean:
	@echo "Clean..."
	@rm -rf $(NAME)
	@echo "Clean !"

fclean:
	@echo "Full clean..."
	@rm -rf $(NAME) $(SRCS)
	@echo "Fclean !"

re:	clean all

run: re
	@(clear)
	@(./$(NAME))

leaks:
	@(while true; do leaks $(NAME); done;)

.PHONY:	all clean fclean re