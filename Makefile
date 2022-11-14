MAP					=	ft_map
VECTOR				=	ft_vector
STACK				=	ft_stack
SET					=	ft_set

CXXFLAGS			=	-Wall -Wextra -Werror -W -std=c++98

DEBUGFLAGS			=	-g3	#-DDEBUG #-fsanitize=address 

CXX					=	c++

RM					=	rm -rf

SRCS_MAP			=	main_map.cpp
SRCS_VEC			=	main_vector.cpp
SRCS_STA			=	main_stack.cpp
SRCS_SET			=	main_set.cpp

SRCS_DIR			=	test

INC					=	-I inc/iterator -I inc/type_traits -I inc/utility

OBJS_MAP			=	$(SRCS_MAP:.cpp=.o)
OBJS_VEC			=	$(SRCS_VEC:.cpp=.o)
OBJS_STA			=	$(SRCS_STA:.cpp=.o)
OBJS_SET			=	$(SRCS_SET:.cpp=.o)

OBJS_DIR			= 	.obj

DEPS_MAP			=	$(SRCS_MAP:.cpp=.d)
DEPS_VEC			=	$(SRCS_VEC:.cpp=.d)
DEPS_STA			=	$(SRCS_STA:.cpp=.d)
DEPS_SET			=	$(SRCS_SET:.cpp=.d)

DEPS_DIR			=	.dep

vpath %.cpp 		$(SRCS_DIR)

vpath %.o			$(OBJS_DIR)

vpath %.d			$(DEPS_DIR)

all:				$(MAP) $(VECTOR) $(STACK)

map:				$(MAP)
vector:				$(VECTOR)
stack:				$(STACK)
set:				$(SET)

$(MAP):				$(DEPS_MAP) $(OBJS_MAP)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(addprefix $(OBJS_DIR)/,$(OBJS_MAP)) -o $(MAP)

$(VECTOR):			$(DEPS_VEC) $(OBJS_VEC)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(addprefix $(OBJS_DIR)/,$(OBJS_VEC)) -o $(VECTOR)

$(STACK):			$(DEPS_STA) $(OBJS_STA)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(addprefix $(OBJS_DIR)/,$(OBJS_STA)) -o $(STACK)

$(SET):				$(DEPS_SET) $(OBJS_SET)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) $(addprefix $(OBJS_DIR)/,$(OBJS_SET)) -o $(SET)

%.d:				%.cpp
	$(CXX) $(INC) -MM $< -MF $(DEPS_DIR)/$@ 

-include $(addprefix $(DEPS_DIR)/, $(DEPS_MAP), $(DEPS_VEC), $(DEPS_STA))

%.o:				%.cpp
	$(CXX) $(INC) $(CXXFLAGS) $(DEBUGFLAGS) -c $< -o $(OBJS_DIR)/$@

$(DEPS_MAP):		| $(DEPS_DIR)
$(DEPS_VEC):		| $(DEPS_DIR)
$(DEPS_STA):		| $(DEPS_DIR)
$(DEPS_SET):		| $(DEPS_DIR)

$(DEPS_DIR):
	mkdir -p $(DEPS_DIR)

$(OBJS_MAP):		| $(OBJS_DIR)
$(OBJS_VEC):		| $(OBJS_DIR)
$(OBJS_STA):		| $(OBJS_DIR)
$(OBJS_SET):		| $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:		
	$(RM) $(OBJS_DIR) $(DEPS_DIR)

fclean:				clean
	$(RM) $(MAP) $(VECTOR) $(STACK) $(SET)

re:				fclean all

dl:			
	curl -O "https://projects.intra.42.fr/uploads/document/document/8394/main.cpp"
	curl -O "https://cdn.intra.42.fr/pdf/pdf/47623/en.subject.pdf"

.PHONY:				all clean fclean re dl
