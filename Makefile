# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 12:43:22 by abbouzid          #+#    #+#              #
#    Updated: 2021/04/04 16:59:50 by abbouzid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

GCC				= gcc -Wall -Wextra -Werror -ltermcap

STR				= strings

BUILTINS		= builtins

M_UTILS			= minishell_utils

lST_M			= lst_methodes

STACK			= stack

PARSER			= parsing

S_SH			= start_shell

PP				= piping

EXPN			= expansion

EXCT			= execution

LEXER			= lexer

ENV				= environment

HIST			= history

SRCS			= minishell.c						\
				$(STR)/strings.c					\
				$(STR)/strings_2.c					\
				$(STR)/strings_3.c					\
				$(STR)/ft_split.c					\
				$(STR)/ft_strjoin.c					\
				$(STR)/ft_putstr_fd.c				\
				$(STR)/ft_itoa.c					\
				$(STR)/ft_strrchr.c					\
				$(STR)/putchar.c					\
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
				$(PARSER)/parser.c					\
				$(S_SH)/start_shell.c				\
				$(S_SH)/new_input.c					\
				$(PP)/piping.c						\
				$(PP)/piping_2.c					\
				$(EXPN)/expansions.c				\
				$(EXPN)/expan_quoted.c				\
				$(EXPN)/expan_unquoted.c			\
				$(EXPN)/expan_special.c				\
				$(EXPN)/expan_token.c				\
				$(EXCT)/execute_cmd.c				\
				$(EXCT)/execute_pipeline.c			\
				$(LEXER)/lexer.c					\
				$(LEXER)/tokenizer.c				\
				$(ENV)/build_env_var.c				\
				$(ENV)/manip_env.c					\
				$(ENV)/get_env_var.c				\
				$(BUILTINS)/builtin_methodes.c		\
				$(BUILTINS)/cd.c					\
				$(BUILTINS)/echo.c					\
				$(BUILTINS)/env.c					\
				$(BUILTINS)/exit.c					\
				$(BUILTINS)/export.c				\
				$(BUILTINS)/export_utils.c			\
				$(BUILTINS)/pwd.c					\
				$(BUILTINS)/unset.c					\
				$(HIST)/history.c


all:	$(NAME)

get_next_line/gnl.a:
	$(MAKE) -C get_next_line

$(NAME) : $(SRCS) get_next_line/gnl.a
	$(MAKE) -C get_next_line
	$(GCC) -g  -o $(NAME) $(SRCS) get_next_line/gnl.a

clean:
	rm $(NAME)

fclean: clean
	rm -rf *.o get_next_line/gnl.a *.dSYM

re: fclean all

.PHONY: clean fclean re all
