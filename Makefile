CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 

SRC = main.c \
	srcs/exec.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

OBJDIR = obj

PRINTF = printf/printf.a

LIBFT = libft/libft.a

INCLUDES = -I. -Iftprintf

NAME = minishell

RED=\033[1;31m]
GREEN=\033[1;32m]
YELLOW=\033[1;33m]
BLUE=\033[1;34m]
MAGENTA=\033[1;35m]
CYAN=\033[1;36m]
WHITE=\033[1;37m]


$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	@printf "🟡 ${YELLOW}[MINISHELL] Compiling minishell...${WHITE}\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)
	@printf "✅ ${GREEN}[MINISHELL] Compiled !${WHITE}\n"

$(OBJDIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(PRINTF): $(LIBFT)
	@$(MAKE) -s -C printf

$(LIBFT):
	@$(MAKE) -s -C libft

# Command #

all: $(NAME)

clean:
	@echo "Suppression des objets $(NAME)"
	@rm -rf $(OBJ)
	@$(MAKE) -s -C printf clean
	@$(MAKE) -s -C libft clean

fclean: clean
	@echo "Suppression de $(NAME)"
	@rm -rf $(NAME)
	@$(MAKE) -s -C printf fclean
	@$(MAKE) -s -C libft fclean

re: fclean all

.PHONY: all clean fclean re