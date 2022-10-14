NAME				=	containers

CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98

DEBUGFLAGS			=	-g3	# -fsanitize=address

CXX				=	c++

RM				=	rm -rf

SRCS				=	main_map.cpp

SRCS_DIR			=	test

INC				=	-I inc/iterator -I inc/type_traits -I inc/utility

OBJS				=	$(SRCS:.cpp=.o)

OBJS_DIR			= 	.obj

DEPS				=	$(SRCS:.cpp=.d)

DEPS_DIR			=	.dep

vpath %.cpp 		$(SRCS_DIR)

vpath %.o			$(OBJS_DIR)

vpath %.d			$(DEPS_DIR)

all:				$(NAME)

$(NAME):			$(DEPS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(addprefix $(OBJS_DIR)/,$(OBJS)) -o $(NAME)

%.d:				%.cpp
	$(CXX) $(INC) -MM $< -MF $(DEPS_DIR)/$@ 

-include $(addprefix $(DEPS_DIR)/, $(DEPS))

%.o:				%.cpp
	$(CXX) $(INC) $(CXXFLAGS) $(DEBUGFLAGS) -c $< -o $(OBJS_DIR)/$@

$(DEPS):			| $(DEPS_DIR)

$(DEPS_DIR):
	mkdir -p $(DEPS_DIR)

$(OBJS):			| $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:		
	$(RM) $(OBJS_DIR) $(DEPS_DIR)

fclean:				clean
	$(RM) $(NAME)

re:				fclean all

dl:			
	curl -O "https://projects.intra.42.fr/uploads/document/document/8394/main.cpp"
	curl -O "https://cdn.intra.42.fr/pdf/pdf/47623/en.subject.pdf"

.PHONY:				all clean fclean re dl
