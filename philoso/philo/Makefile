# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 14:21:13 by rmander           #+#    #+#              #
#    Updated: 2021/10/09 19:57:10 by rmander          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
INCLUDE = ./include
CFLAGS = -Wall -Wextra -Werror -MMD -I $(INCLUDE) -pthread
NAME = ./philo
SRCS =	./src/main.c \
		./src/mon.c \
		./src/philo.c \
		./src/error.c \
		./src/clean.c \
		./src/utils/ft_isdigit.c \
		./src/utils/ft_isspace.c \
		./src/utils/ft_strlen.c \
		./src/utils/ft_putstr_fd.c \
		./src/utils/ft_usleep.c \
		./src/utils/to_msec.c \
		./src/utils/to_usec.c \
		./src/utils/alloca_to.c \
		./src/utils/ft_atoss.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
