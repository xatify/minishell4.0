# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abbouzid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/13 19:28:16 by abbouzid          #+#    #+#              #
#    Updated: 2019/10/21 22:19:06 by abbouzid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = 	ft_strlen.c			\
		ft_strncmp.c		\
		ft_strdup.c			\
		ft_strchr.c			\
		ft_strjoin.c		\
		ft_strlcat.c		\
		ft_strlcpy.c		\
		ft_strmapi.c		\
		ft_strnstr.c		\
		ft_strrchr.c		\
		ft_substr.c			\
		ft_strtrim.c		\
		ft_split.c			\
		ft_atoi.c			\
		ft_itoa.c			\
		ft_calloc.c			\
		ft_isalpha.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isdigit.c		\
		ft_isprint.c		\
		ft_tolower.c		\
		ft_toupper.c		\
		ft_bzero.c			\
		ft_memccpy.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_memmove.c		\
		ft_memset.c			\
		ft_putendl_fd.c		\
		ft_putchar_fd.c		\
		ft_putnbr_fd.c		\
		ft_putstr_fd.c

OBJ = $(SRC:.c=.o)

BSRC =	ft_lstadd_back_bonus.c		\
		ft_lstadd_front_bonus.c		\
		ft_lstdelone_bonus.c		\
		ft_lstiter_bonus.c			\
		ft_lstmap_bonus.c			\
		ft_lstnew_bonus.c			\
		ft_lstsize_bonus.c			\
		ft_lstclear_bonus.c			\
		ft_lstlast_bonus.c

BOBJ = $(BSRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c $(SRC)
	ar rc $(NAME) $(OBJ)

bonus:
	gcc -Wall -Wextra -Werror -c $(BSRC)
	ar rs $(NAME) $(BOBJ)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
