# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 22:48:36 by abbouzid          #+#    #+#              #
#    Updated: 2021/01/14 09:36:00 by keddib           ###   ########.fr        #                                                                            #
# **************************************************************************** #

NAME			= minishell
GCC				= gcc -Wall -Wextra -Werror
STR				= strings
BUILTINS		= builtins
SRCS			= minishell.c						\
				get_command.c						\
				$(STR)/strings.c					\
				$(STR)/strings_2.c					\
				$(STR)/ft_split.c					\
				$(STR)/ft_strjoin.c					\
				$(STR)/ft_putstr_fd.c				\
				$(STR)/ft_itoa.c					\
				$(STR)/ft_strrchr.c					\
				lexer.c								\
				stack.c								\
				parser.c							\
				strlistmethodes.c					\
				cmdslistmethodes.c					\
				pipelinelistmethodes.c				\
				tokenslistmethodes.c				\
				expansion.c							\
				env_var.c							\
				start_shell.c						\
				execution.c							\
				build_arguments_array.c				\
				find_binary_path.c					\
				variables.c							\
				$(BUILTINS)/builtin_methodes.c		\
				$(BUILTINS)/cd.c					\
				$(BUILTINS)/echo.c					\
				$(BUILTINS)/env.c					\
				$(BUILTINS)/exit.c					\
				$(BUILTINS)/export.c				\
				$(BUILTINS)/pwd.c					\
				$(BUILTINS)/unset.c					\
				sort.c								\
				redirections.c
# GNL				= get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c
all:
	$(MAKE) -C get_next_line
	$(GCC) -g  -o $(NAME) $(SRCS) gnl.a

test:
	./minishell

clean:
	rm $(NAME)

fclean: clean
	rm -rf *.dSYM

re: clean all

.PHONY: clean re all
