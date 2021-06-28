# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 12:43:22 by abbouzid          #+#    #+#              #
#    Updated: 2021/06/28 14:35:23 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

LDFLAGS			= -L/goinfre/abbouzid/homebrew/opt/readline/lib
CPPFLAGS        = -I/goinfre/abbouzid/homebrew/opt/readline/include

GCC				= gcc -g -Wall -Wextra -Werror -lreadline $(LDFLAGS) $(CPPFLAGS)

STR				= strings

BUILTINS		= builtins

M_UTILS			= minishell_utils

lST_M			= lst_methodes

STACK			= stack

PARSER			= parsing

S_SH			= start_shell

EXPN			= expansion

EXCT			= execution

LEXER			= lexer

ENV				= environment

SRCS			= minishell.c						\
				$(STR)/strings.c					\
				$(STR)/strings_2.c					\
				$(STR)/strings_3.c					\
				$(STR)/ft_split.c					\
				$(STR)/ft_strjoin.c					\
				$(STR)/ft_putstr_fd.c				\
				$(STR)/ft_itoa.c					\
				$(STR)/ft_strrchr.c					\
				$(STR)/strings_4.c					\
				$(M_UTILS)/command.c				\
				$(M_UTILS)/find_binary_path.c		\
				$(M_UTILS)/arguments_array.c		\
				$(M_UTILS)/pipeline.c				\
				$(M_UTILS)/redirections.c			\
				$(M_UTILS)/redirections_2.c			\
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
				$(EXPN)/expansions.c				\
				$(EXPN)/expan_env.c					\
				$(EXPN)/expan_quotes.c				\
				$(EXPN)/expansion_err.c				\
				$(EXCT)/execute_builtins.c			\
				$(EXCT)/execute_pipeline.c			\
				$(EXCT)/execute_pipeline2.c			\
				$(EXCT)/execute_cmd.c				\
				$(LEXER)/lexer.c					\
				$(LEXER)/tokenizer.c				\
				$(ENV)/build_env_var.c				\
				$(ENV)/build_env_var2.c				\
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


all:	$(NAME)

$(NAME) : $(SRCS)
	$(GCC) -o $(NAME) $(SRCS)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: clean fclean re all
