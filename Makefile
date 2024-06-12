# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 12:55:56 by qordoux           #+#    #+#              #
#    Updated: 2024/06/12 17:41:24 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
BUILD_DIR := .build
LIBFT := ./libft
LIBS := ./libft/libft.a
SRC := $(wildcard *.c) $(wildcard utils/*.c) $(wildcard execution/*.c) $(wildcard parsing/*.c)
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