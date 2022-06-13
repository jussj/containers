# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jusaint- <jusaint-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 17:19:58 by jusaint-          #+#    #+#              #
#    Updated: 2022/06/13 18:50:04 by jusaint-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	containers

CPP_FLAGS			=	-Wall -Wextra -Werror -std=c++98

DEBUG_FLAGS			=	-g3

DEPS_FLAGS			=	-MMD -MP -include $(DEPS)

CC					=	c++

RM					=	rm -f

SRCS				=	_test/test_iterator.cpp

OBJS				=	$(addprefix $(OBJS_DIR),$(SRCS:.cpp=.o))

OBJS_DIR			= 	.obj/

DEPS				=	$(addprefix $(DEPS_DIR),$(SRCS:.cpp=.d))

DEPS_DIR			=	.dep/

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CPP_FLAGS) $^ -o $(NAME)

$(OBJS_DIR)/%.o:	%.cpp
					mkdir -p $(OBJS_DIR) $(DEPS_DIR)
					$(CC) $(CPP_FLAGS) $(DEPS_FLAGS) -c $< -o $@

clean:		
					$(RM) $(OBJS_DIR) $(DEPS_DIR)

fclean: 			clean
					$(RM) $(NAME)

re:					fclean all

dl:			
					curl -O "https://projects.intra.42.fr/uploads/document/document/8394/main.cpp"
					curl -O "https://cdn.intra.42.fr/pdf/pdf/47623/en.subject.pdf"

.PHONY:				all clean fclean re
