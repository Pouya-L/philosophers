# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plashkar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 14:11:07 by plashkar          #+#    #+#              #
#    Updated: 2024/05/16 11:53:25 by plashkar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

STANDARD_FLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

philo_LIB = philo.a

SRC = \
	src/main.c \
	src/utils.c \
	src/parser.c \
	src/init.c \
	src/test.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(STANDARD_FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling $@"
	@$(CC) $(STANDARD_FLAGS) $(OBJ) -o $(NAME) > /dev/null
	@echo "philo has been created."

$(philo_LIB): $(OBJ)
	@echo "Creating $@"
	@ar rcs $(philo_LIB) $(OBJ) > /dev/null
	@echo The library philo.a has been created.

clean:
	@rm -f src/*.o
	@echo Object files have been deleted.

fclean: clean
	@rm -f $(philo_LIB)
	@rm -f $(NAME)
	@echo All created files have been deleted.

re: fclean all

v: all clean



.PHONY: fclean clean all re
