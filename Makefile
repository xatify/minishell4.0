# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 22:48:36 by abbouzid          #+#    #+#              #
#    Updated: 2021/01/13 16:31:17 by abbouzid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
GCC				= gcc -Wall -Wextra -Werror
BUILTINS		= builtins
SRCS			= minishell.c						\
				get_command.c						\
				strings.c							\
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
				$(BUILTINS)/builtin_methodes.c		\
				$(BUILTINS)/cd.c					\
				$(BUILTINS)/echo.c					\
				$(BUILTINS)/env.c					\
				$(BUILTINS)/exit.c					\
				$(BUILTINS)/export.c				\
				$(BUILTINS)/pwd.c					\
				$(BUILTINS)/unset.c
# GNL				= get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c
all:
	$(GCC) -g -o $(NAME) $(SRCS) libftprintf.a gnl.a libft.a
	#$(GCC) -g test.c -o test
	./minishell

clean:
	rm $(NAME)

fclean:
	rm -rf *.dSYM

re: clean all

.PHONY: clean re all
