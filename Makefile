# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wiljimen <wiljimen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 07:07:38 by wiljimen          #+#    #+#              #
#    Updated: 2026/02/16 16:56:36 by wiljimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address -g3
INCLUDES = -I inc
RM = rm -f
MAKEFLAGS += --silent

SRC = src/main.c src/parse.c src/time.c src/rules.c src/init.c \
      src/meals.c src/philos.c src/thread.c
OBJ = $(SRC:.c=.o)

RED       := \033[91;1m
GREEN     := \033[92;1m
CLEAR     := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Philo compiled$(CLEAR)"

%.o: %.c inc/philo.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
