# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 22:48:36 by abbouzid          #+#    #+#              #
#    Updated: 2020/12/22 10:22:18 by abbouzid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
GCC				= gcc -Wall -Wextra -Werror

SRCS			= minishell.c		\
				  get_command.c		\
				  strings.c			\
				  tokens.c			\
				  stack.c


all:
	$(GCC) -g -o $(NAME) $(SRCS) libftprintf.a
	#$(GCC) -g test.c -o test
	./minishell

clean:
	rm $(NAME)

re: clean all

.PHONY: clean re all

