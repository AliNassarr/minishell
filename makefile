# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 16:55:00 by invader           #+#    #+#              #
#    Updated: 2025/12/22 01:29:59 by alnassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRCS =	minishell.c \
		gc/gc.c \
		tokenization/helperr.c \
		tokenization/helper.c \
		tokenization/expanding.c \
		tokenization/joining.c \
		tokenization/stage1.c \
		parsing/ast.c \
		parsing/preparation.c \
		parsing/stage2.c \
		debug/astprint.c \
		execution/executor.c \
		builtins/builtin_dispatch.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		signals/signal_handlers.c \
		signals/signal_setup.c \
		signals/signal_utils.c \
		utils/ft_utils.c \
		utils/env_utils.c


OBJS = $(SRCS:.c=.o)

HEADERS =	minishell.h \
			functions/functions.h \
			gc/gc.h \
			tokenization/tokenization.h \
			parsing/parsing.h \
			debug/astprint.c


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re