NAME = minishell

SRCS = srcs/main.c srcs/env.c srcs/get_env.c srcs/gnl.c srcs/analysis_input.c \
	srcs/line.c srcs/utils.c srcs/error.c srcs/process_end.c srcs/prompt.c \
	srcs/char.c srcs/char_escaped.c srcs/quote.c srcs/dollar.c srcs/word.c \
	srcs/redir.c srcs/cmd.c srcs/print.c srcs/split_cmd.c

OBJS = $(SRCS:.c=.o)

INCLD = -I includes -I libft

CC = clang

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -L libft

LIBS = -lft

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLD) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/$(NAME)

re: fclean all

.PHONY: all clean fclean re

