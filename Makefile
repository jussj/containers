# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 17:19:58 by jusaint-          #+#    #+#              #
#    Updated: 2022/06/03 18:22:33 by jusaint-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	containers

FLAGS		=	-Wall -Wextra -Werror -std=c++98 -g3

CC			=	c++

RM			=	rm -f

SRCS		=	main.cpp

OBJS		=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $^ -o $(NAME)

%.o:		%.cpp
			$(CC) $(FLAGS) -c $< -o $@

clean:		
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean all

dl:			
			curl -O "https://projects.intra.42.fr/uploads/document/document/8394/main.cpp"
			curl -O "https://cdn.intra.42.fr/pdf/pdf/47623/en.subject.pdf"

.PHONY:		all clean fclean re
