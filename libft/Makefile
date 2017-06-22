# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/04/09 03:56:46 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[48;5;9m
GREEN = \033[48;5;10m
LOL = \033[48;5;106m
LIL = \033[48;5;129m
END = \033[0m
X = 0
Y = 0

NAME = libft.a

SRC = ./ft_putendl_fd.c\
	  ./ft_putchar_fd.c\
	  ./ft_hexa_itoa.c\
	  ./ft_hexa_ltoa.c\
	  ./ft_ltoa_base.c\
	  ./ft_putstr_fd.c\
	  ./ft_memalloc.c\
	  ./ft_memset.c\
	  ./ft_strcat.c\
	  ./ft_strcmp.c\
	  ./ft_strdel.c\
	  ./ft_strlen.c\
	  ./ft_strdup.c\
	  ./ft_ultoa.c\
	  ./ft_itoa.c\
	  ./ft_ltoa.c\
	  ./ft_putchar.c\
	  ./ft_putstr.c\
	  ./ft_putnbr.c\
	  ./ft_putendl.c\
	  ./print_hexa.c\
	  ./ft_strsplit.c\
	  ./ft_strsub.c\
	  ./ft_strnew.c\

OBJS = $(SRC:.c=.o)

CC = clang

FLAG = -Wall -Wextra -Werror -g3
#FLAG = -Weverything -O3

HEAD = ./includes/

all: $(NAME)

$(NAME): $(OBJS) ./includes/libft.h
	@$(CC) $(FLAG) -c $(SRC) -I $(HEAD)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

%.o : %.c $(HEAD)
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	$(CC) -c $(FLAG) $< -o $@

mc: fclean all clean

clean:
	@rm -f $(OBJS) ./percent_c.o ./percent_d.o ./percent_s.o ./ft_dprintf.o \
	./percent_p.o ./percent_x.o ./tools.o ./percent_o.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
