NAME = minishell
CC = cc
CFLAGS = -g -Wall -Werror -Wextra
LIBFLAGS = -lreadline
RM = rm -rf

SRCS = $(wildcard *.c) $(wildcard execution/*.c)
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(OBJS) -o $(NAME) libft/libft.a $(LIBFLAGS)

all: $(NAME)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C libft

re: fclean all

%.o: %.c libft/*.c minishell.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re