NAME = minishell

SRCS = srcs/main.c srcs/env.c srcs/get_env.c srcs/gnl.c srcs/analysis_input.c \
	srcs/line.c srcs/utils.c srcs/error.c srcs/process_end.c srcs/prompt.c \
	srcs/char.c srcs/char_escaped.c srcs/quote.c srcs/dollar.c srcs/word.c \
	srcs/redir.c srcs/cmd.c srcs/print.c srcs/split_cmd.c srcs/process_shell.c \
	srcs/edit_arg.c srcs/dollar_utils.c srcs/builtin/built.c srcs/builtin/pwd.c \
	srcs/builtin/echo.c srcs/builtin/cd.c srcs/builtin/add_or_delete_var_env.c \
	srcs/builtin/utils.c srcs/builtin/unset.c srcs/builtin/env.c \
	srcs/builtin/export.c srcs/builtin/exit.c srcs/pipe.c srcs/path.c \
	srcs/redirect.c 

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

