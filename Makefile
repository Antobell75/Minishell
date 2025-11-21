# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anbellar <anbellar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 13:59:21 by sle-bail          #+#    #+#              #
#    Updated: 2025/11/20 23:55:24 by anbellar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

SRCDIR      = src
OBJDIR      = obj
INCDIR      = includes
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFT_DIR) -g3
LDFLAGS     = -L$(LIBFT_DIR)
LIBS        = $(LIBFT) -lreadline

SRC = \
	main.c \
	exec/builtin/create_env.c \
	exec/builtin/ft_cd.c \
	exec/builtin/ft_echo.c \
	exec/builtin/ft_env.c \
	exec/builtin/ft_exit.c \
	exec/builtin/ft_export.c \
	exec/builtin/ft_export_utils.c \
	exec/builtin/ft_export_utils2.c \
	exec/builtin/ft_pwd.c \
	exec/builtin/ft_unset.c \
	exec/execv/builtins.c \
	exec/execv/env.c \
	exec/execv/heredoc.c \
	exec/execv/heredoc_utils.c \
	exec/execv/mainexec.c \
	exec/execv/mainexec_utils.c \
	exec/execv/path.c \
	exec/execv/process.c \
	exec/execv/redirect.c \
	exec/execv/utils.c \
	exec/parsing/cmd_builder.c \
	exec/parsing/tokenize.c \
	exec/parsing/lexer.c \
	exec/parsing/utiles_lexpars.c \
	exec/parsing/utiles_parce.c \
	exec/parsing/ft_expand.c \
	exec/parsing/parcer.c \
	exec/parsing/parcer_utils.c \
	exec/parsing/clean.c \
	exec/parsing/utiles_redir.c \
	exec/utils/error.c \
	exec/utils/free.c \
	exec/utils/signal.c

SRC := $(addprefix $(SRCDIR)/,$(SRC))
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEP := $(OBJ:.o=.d)

all: $(NAME) finish

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@printf 'coucou\n';

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: 
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re finish
.DEFAULT_GOAL := all

finish:
# 	@clear
	@printf '\033[1;37m'
	@printf '\n  __  __ _       _     _          _ _ \n'
	@printf ' |  \/  (_)     (_)   | |        | | |\n'
	@printf ' | \  / |_ _ __  _ ___| |__   ___| | |\n'
	@printf ' | |\/| | | |_ \| / __| |_ \ / _ \ | |\n'
	@printf ' | |  | | | | | | \__ \ | | |  __/ | |\n'
	@printf ' |_|  |_|_|_| |_|_|___/_| |_|\___|_|_|\n'
	@printf '\033[0m'
