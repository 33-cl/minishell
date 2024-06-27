# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:37:18 by maeferre          #+#    #+#              #
#    Updated: 2024/06/20 17:54:09 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Werror -Wextra -g
BUILD_DIR := ../.build/libft
SRC = ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_strjoin_free.c ft_substr.c ft_calloc.c ft_strdup.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_strchr.c ft_strcat.c ft_strlcat.c ft_strcpy.c ft_strlcpy.c ft_strlen.c ft_tablen.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memmove.c ft_atoi.c ft_free_tab.c ft_is_space.c ft_isnumber.c
OBJ = $(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))
DEP = $(addprefix $(BUILD_DIR)/,$(SRC:.c=.d))
NAME = libft.a

.PHONY : all clean fclean re

all : $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o : %.c | $(BUILD_DIR) libft.h Makefile
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEP) 

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean :
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all