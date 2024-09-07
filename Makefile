# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 13:56:23 by olyetisk          #+#    #+#              #
#    Updated: 2024/09/06 17:22:16 by olyetisk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRC		=	main.c utils.c philo.c check.c
OBJS 	= 	$(SRC:.c=.o)
CC 		= 	gcc
CFLAGS 	=	-Wall -Wextra -Werror -fsanitize=thread
RM	 	= 	rm -rf

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re