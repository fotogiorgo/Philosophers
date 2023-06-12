# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 14:00:27 by jofoto            #+#    #+#              #
#    Updated: 2023/06/12 19:21:17 by jofoto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =		-Wall -Wextra -Werror -pthread

SRC =		src/main.c src/helpers.c src/init.c src/process.c

OBJ =		$(SRC:%.c=%.o)

NAME =		philo

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ) $(FLAGS)

$(OBJ): %.o: %.c
	cc -c $? -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all