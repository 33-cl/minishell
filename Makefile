# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 12:55:56 by qordoux           #+#    #+#              #
#    Updated: 2024/06/25 15:41:06 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
BUILD_DIR := .build
LIBFT := ./libft
LIBS := ./libft/libft.a
SRC := main.c utils/errors.c utils/free_main.c utils/get_path.c utils/prompt.c utils/reconvert_env.c utils/signals.c \
		parsing/add_space.c parsing/env.c parsing/expand_utils.c parsing/expand.c parsing/fill_redirection.c parsing/final_list.c parsing/free.c parsing/handle_redir_final.c parsing/heredoc.c parsing/init_struct.c parsing/parsing.c parsing/print_struct.c parsing/quoted_or_not_final.c parsing/syntax_error.c parsing/utils_final.c parsing/utils.c \
		execution/builtin.c execution/cd.c execution/echo.c execution/environnement.c execution/execute.c execution/execution_utils.c execution/execve.c execution/exit.c execution/export.c execution/pwd.c execution/redirections.c execution/struct_manip.c
#SRC := $(wildcard *.c) $(wildcard utils/*.c) $(wildcard parsing/*.c)
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(SRC:%.c=$(BUILD_DIR)/%.d)
CC := cc

all: $(LIBFT) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/execution
	@mkdir -p $(BUILD_DIR)/parsing
	@mkdir -p $(BUILD_DIR)/utils

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(CFLAGS) -lreadline -o $(NAME)
	@echo "\033[1;32mMinishell Created!\n"

$(LIBFT)/libft.a : FORCE
	@make -C $(LIBFT)
	@echo "\033[1;32mLibft Created\n"

-include $(DEP)

clean:
	rm -rf $(BUILD_DIR)
	make clean -sC $(LIBFT)

fclean: clean
	rm -f $(NAME) $(LIBS)
	make fclean -C $(LIBFT)

re: fclean all

FORCE:

.PHONY: all clean fclean re