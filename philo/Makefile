# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moulmoud <moulmoud@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 13:47:03 by moulmoud          #+#    #+#              #
#    Updated: 2023/05/04 13:52:23 by moulmoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

#CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
