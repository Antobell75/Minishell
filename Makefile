CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -O3

SRC = main.c

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

LIBFT = libft/libft.a

NAME = minishell

INCLUDES = -Iincludes -lreadline

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(INCLUDES)
	@echo "Compilation de $(NAME) terminée."

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
		@$(MAKE) -s -C libft

all: $(NAME)

clean:
	@echo "Suppression des fichiers objets..."
	@rm -rf $(OBJDIR)
	@$(MAKE) -s -C libft clean

fclean: clean
	@echo "Suppression de l'exécutable $(NAME)..."
	@rm -f $(NAME)
	@$(MAKE) -s -C libft fclean

re: fclean all

.PHONY: all clean fclean re