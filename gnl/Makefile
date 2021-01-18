# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouzid <abbouzid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/18 09:05:19 by abbouzid          #+#    #+#              #
#    Updated: 2021/01/18 09:15:01 by abbouzid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../gnl.a
BUFSIZE		= 100
SRCS		= get_next_line.c		\
			get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	gcc -D BUFFER_SIZE=$(BUFSIZE) -c $(SRCS)
	ar rs $(NAME) $(OBJS)

clean:
	rm $(NAME)

fclean:	clean
	rm $(OBJS)

re: fclean all

.PHONY: all cleanfclean re