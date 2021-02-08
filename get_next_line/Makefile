
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 09:05:19 by abbouzid          #+#    #+#              #
#    Updated: 2021/02/06 10:52:45 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= gnl.a
BUFSIZE		= 100
SRCS		= get_next_line.c		\
			get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	gcc -g -D BUFFER_SIZE=$(BUFSIZE) -c $(SRCS)
	ar rs $(NAME) $(OBJS)
	rm -rf *.o

clean:
	rm $(NAME)

fclean:	clean
	rm $(OBJS)

re: fclean all

.PHONY: all cleanfclean re
