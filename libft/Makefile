# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 23:37:18 by maeferre          #+#    #+#              #
#    Updated: 2024/05/01 18:40:03 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_calloc.c ft_strdup.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_strchr.c ft_strcat.c ft_strlcat.c ft_strcpy.c ft_strlcpy.c ft_strlen.c ft_tablen.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memmove.c ft_atoi.c ft_free_tab.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
NAME = libft.a

.PHONY : all clean fclean re

all : $(NAME)

%.o : %.c libft.h Makefile
		$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEP) 

$(NAME) : $(OBJ)
		ar rcs $(NAME) $(OBJ)

bonus:
		$(MAKE) SRC="$(SRC)" DEP="$(DEP)"

clean :
		rm -rf $(OBJ) $(DEP)

fclean : clean
		rm -f $(NAME)

re : fclean all