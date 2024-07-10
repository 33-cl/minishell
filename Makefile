# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: debian <debian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 12:55:56 by qordoux           #+#    #+#              #
#    Updated: 2024/07/08 18:41:14 by debian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
BUILD_DIR := .build
LIBFT := ./libft
LIBS := ./libft/libft.a
SRC := main.c utils/errors.c utils/free_main.c utils/get_path.c utils/prompt.c utils/reconvert_env.c utils/signals.c \
		parsing/add_spaces/add_space.c parsing/add_spaces/count_when_need_space.c parsing/add_spaces/init_for_space.c parsing/env/init_get_env.c parsing/expand/expand_argument.c parsing/expand/expand_utils.c parsing/expand/process_expand.c parsing/expand/replace_expand.c parsing/free/free_heredoc.c parsing/free/free_utils_a.c parsing/free/free_utils_b.c parsing/free/main_free.c parsing/heredoc/add_heredoc_delimiter_and_remove_quotes.c parsing/heredoc/add_heredoc_to_fd.c parsing/heredoc/init_and_process_heredoc.c parsing/heredoc/read_line_until_delimiter.c parsing/lexing/add_arg_to_list.c parsing/lexing/create_arg.c parsing/lexing/determine_arg_type.c parsing/lexing/handle_quotes.c parsing/lexing/init_new_arg.c parsing/lexing/lexing_utils.c parsing/lexing/split_space.c parsing/print_struct/print_struct.c parsing/print_struct/print_utils.c parsing/syntax_error/handle_quotes.c parsing/syntax_error/pipe_error.c parsing/syntax_error/redir_error.c parsing/syntax_error/syntax_error.c parsing/utils/ft_realloc_b.c parsing/utils/ft_realloc.c parsing/utils/ft_strtok.c parsing/utils/init.c parsing/utils/utils.c parsing/final_list/add_specifier_to_struct.c parsing/final_list/delimiter_handler.c parsing/final_list/handle_argument.c parsing/final_list/handle_heredoc.c parsing/final_list/handle_quoted_or_not_arg.c parsing/final_list/handle_redirection.c parsing/final_list/init_final_list.c parsing/final_list/unquote_result.c parsing/init_struct.c parsing/parsing.c \
		execution/builtin.c execution/cd.c execution/echo.c execution/environnement.c execution/execute.c execution/execution_utils.c execution/execve.c execution/exit.c execution/export.c execution/pwd.c execution/redirections.c execution/struct_manip.c
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