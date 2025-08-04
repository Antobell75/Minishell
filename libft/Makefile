# ============================ #
#           COULEURS          #
# ============================ #

RESET = "\033[0m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"

# ============================ #
#         COMPILATION         #
# ============================ #

NAME = libft.a
NORM = norminette -R
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_P1 = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_atoi.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

OBJ_P1 = $(SRC_P1:.c=.o)

# ============================ #
#            RÈGLES           #
# ============================ #

all: $(NAME)
	@echo $(GREEN)✔ Compilation terminée avec succès !$(RESET)

$(NAME): $(OBJ_P1) $(OBJ_P2)
	@ar -rcs $(NAME) $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

norm:
	@echo $(BLUE)→ Vérification avec norminette...$(RESET)
	@$(NORM) *.h *.c

clean:
	@rm -f $(OBJ_P1) $(OBJ_P2)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
