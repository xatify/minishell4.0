# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 09:05:19 by abbouzid          #+#    #+#              #
#    Updated: 2021/01/22 08:43:33 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../gnl.a
BUFSIZE		= 100
SRCS		= get_next_line.c		\
			get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	gcc -D BUFFER_SIZE=$(BUFSIZE) -c $(SRCS)
	ar rs $(NAME) $(OBJS)

clean:
	rm $(NAME)

fclean:	clean
	rm $(OBJS)

re: fclean all

.PHONY: all cleanfclean re
