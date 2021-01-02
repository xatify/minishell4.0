# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 22:48:36 by abbouzid          #+#    #+#              #
#    Updated: 2021/01/02 16:52:36 by abbouzid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
GCC				= gcc -Wall -Wextra -Werror

SRCS			= minishell.c		\
				get_command.c		\
				strings.c			\
				lexer.c				\
				stack.c				\
				parser.c

all:
	$(GCC) -g -o $(NAME) $(SRCS) libftprintf.a
	#$(GCC) -g test.c -o test
	./minishell

clean:
	rm $(NAME)

re: clean all

.PHONY: clean re all

