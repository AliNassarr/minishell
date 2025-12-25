# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alnassar <alnassar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 16:55:00 by invader           #+#    #+#              #
#    Updated: 2025/12/25 01:13:17 by alnassar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRCS =	minishell.c \
		minishell_main.c \
		minishell_helpers.c \
		minishell_helpers2.c \
		gc/gc.c \
		tokenization/helperr.c \
		tokenization/helperr_split.c \
		tokenization/helperr_utils.c \
		tokenization/helper.c \
		tokenization/expanding.c \
		tokenization/expanding_helpers.c \
		tokenization/joining.c \
		tokenization/joining_helpers.c \
		tokenization/stage1.c \
		parsing/ast.c \
		parsing/ast_helpers.c \
		parsing/ast_redir.c \
		parsing/preparation.c \
		parsing/preparation_helpers.c \
		parsing/stage2.c \
		parsing/stage2_helpers.c \
		debug/astprint.c \
		debug/astprint_helpers.c \
		execution/executor.c \
		execution/executor_helpers.c \
		execution/executor_simple.c \
		execution/executor_redir.c \
		execution/executor_pipe.c \
		execution/executor_pipe_helpers.c \
		execution/heredoc_prepare.c \
		execution/heredoc_expand.c \
		execution/heredoc_expand_utils.c \
		builtins/builtin_dispatch.c \
		builtins/builtin_dispatch_helpers.c \
		builtins/builtin_dispatch_join.c \
		builtins/builtin_cd.c \
		builtins/builtin_cd_helpers.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_env_helpers.c \
		builtins/builtin_env_helpers2.c \
		builtins/builtin_exit.c \
		builtins/builtin_exit_helpers.c \
		builtins/builtin_exit_helpers2.c \
		builtins/builtin_exit_utils.c \
		builtins/builtin_export.c \
		builtins/builtin_export_helpers.c \
		builtins/builtin_export_special.c \
		builtins/builtin_export_utils.c \
		builtins/builtin_pwd.c \
		builtins/builtin_pwd_helpers.c \
		builtins/builtin_unset.c \
		signals/signal_handlers.c \
		signals/signal_setup.c \
		signals/signal_utils.c \
		utils/ft_utils.c \
		utils/ft_utils2.c \
		utils/ft_utils3.c \
		utils/env_utils.c \
		utils/env_utils_shlvl.c \
		utils/env_utils2.c \
		utils/env_utils3.c


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