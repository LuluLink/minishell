NAME = Minishell

DIR = ./srcs

SRCS = *.c

HEAD = -I include/

FLAGS = -Wall -Werror -Wextra -lncurses# -g3 -fsanitize=address

all: ${NAME}

$(NAME):
	@echo "Création de l'executable..."
	@gcc $(FLAGS) $(HEAD) $(DIR)/$(SRCS) -o $(NAME)
	@echo "Compilation terminée !"

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