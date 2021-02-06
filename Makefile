# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 12:43:22 by abbouzid          #+#    #+#              #
#    Updated: 2021/02/06 09:44:02 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

GCC				= gcc -Wall -Wextra -Werror

STR				= strings

BUILTINS		= builtins

M_UTILS			= minishell_utils

lST_M			= lst_methodes

STACK			= stack

SRCS			= minishell.c						\
				$(STR)/strings.c					\
				$(STR)/strings_2.c					\
				$(STR)/strings_3.c					\
				$(STR)/ft_split.c					\
				$(STR)/ft_strjoin.c					\
				$(STR)/ft_putstr_fd.c				\
				$(STR)/ft_itoa.c					\
				$(STR)/ft_strrchr.c					\
				$(M_UTILS)/command.c				\
				$(M_UTILS)/find_binary_path.c		\
				$(M_UTILS)/arguments_array.c		\
				$(M_UTILS)/pipeline.c				\
				$(M_UTILS)/redirections.c			\
				$(M_UTILS)/signals.c				\
				$(M_UTILS)/sort.c					\
				$(M_UTILS)/tokens.c					\
				$(M_UTILS)/variables.c				\
				$(lST_M)/lst_methodes.c				\
				$(lST_M)/lst_methodes_2.c			\
				$(STACK)/stack.c					\
				$(STACK)/stack_2.c					\
				lexer.c								\
				parser.c							\
				expansions.c						\
				env_var.c							\
				start_shell.c						\
				execution.c							\
				piping.c							\
				$(BUILTINS)/builtin_methodes.c		\
				$(BUILTINS)/cd.c					\
				$(BUILTINS)/echo.c					\
				$(BUILTINS)/env.c					\
				$(BUILTINS)/exit.c					\
				$(BUILTINS)/export.c				\
				$(BUILTINS)/export_utils.c			\
				$(BUILTINS)/pwd.c					\
				$(BUILTINS)/unset.c


all:	$(NAME)

gnl.a:
	$(MAKE) -C get_next_line

$(NAME) : $(SRCS) gnl.a
	$(MAKE) -C get_next_line
	$(GCC) -g  -o $(NAME) $(SRCS) gnl.a

clean:
	rm $(NAME)

fclean: clean
	rm -rf *.o gnl.a *.dSYM

re: fclean all

.PHONY: clean re all
