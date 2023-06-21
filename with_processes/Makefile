# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 14:00:27 by jofoto            #+#    #+#              #
#    Updated: 2023/06/21 13:18:43 by jofoto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =		-Wall -Wextra -Werror -pthread #-fsanitize=address

SRC =		src/main_bonus.c src/init_helpers_bonus.c src/init_bonus.c src/philosophers_bonus.c \
			src/destroy_bonus.c src/process_helpers_bonus.c

OBJ =		$(SRC:%.c=%.o)

NAME =		philo_bonus

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