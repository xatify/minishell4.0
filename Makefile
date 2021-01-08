# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 22:48:36 by abbouzid          #+#    #+#              #
#    Updated: 2021/01/07 18:11:34 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
GCC				= gcc -Wall -Wextra -Werror

SRCS			= minishell.c get_command.c strings.c lexer.c stack.c parser.c strlistmethodes.c cmdslistmethodes.c pipelinelistmethodes.c tokenslistmethodes.c
# GNL				= get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c
all:
	$(GCC) -g -o $(NAME) $(SRCS) libftprintf.a gnl.a
	#$(GCC) -g test.c -o test
	./minishell

clean:
	rm $(NAME)

fclean:
	rm -rf *.dSYM

re: clean all

.PHONY: clean re all
