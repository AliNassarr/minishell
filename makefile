# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: invader <invader@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 16:55:00 by invader           #+#    #+#              #
#    Updated: 2025/12/20 00:51:38 by invader          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRCS =	minishell.c \
		functions/functions.c \
		gc/gc.c \
		tokenization/helperr.c \
		tokenization/helper.c \
		tokenization/expanding.c \
		tokenization/joining.c \
		tokenization/stage1.c \
		parsing/ast.c \
		parsing/preparation.c \
		parsing/stage2.c \
		debug/astprint.c


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