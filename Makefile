ifndef OUTPUT
.SILENT:
endif

NAME	=	neupp
ARGS	=	
SRCS	=	main.cpp Being.cpp randoms.cpp helpers.cpp \
				Neuron.cpp DynamicNeuron.cpp menu.cpp parser.cpp \
				TypesNeuron.cpp MetaNeuron.cpp prints.cpp Axon.cpp \
				InteractiveNeuron.cpp
HEAD	=	Makefile header.hpp Being.hpp defines.hpp randoms.hpp \
				Neuron.hpp DynamicNeuron.hpp menu.hpp TypesNeuron.hpp \
				MetaNeuron.hpp prints.hpp parser.hpp Axon.hpp types.hpp \
				InteractiveNeuron.hpp
SHELL	=	/bin/sh
CC		=	clang++ -Wfatal-errors -std=c++20 -Wc++20-extensions -pthread
CCFLAGS	=	-Wall -Werror -Wextra -g -Wfatal-errors
CCLINKS	=	#-Llibft -lft
OBJS	=	$(SRCS:.cpp=.o)
VAL		=	valgrind
VALFLAG	=	--tool=memcheck \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--show-reachable=yes
all:		$(NAME)
	echo
$(NAME):	$(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(NAME) $(CCLINKS) -lncurses
$(OBJS):	%.o : %.cpp $(HEAD)
	$(CC) $(CCFLAGS) -o $@ -c $< $(CCLINKS)
	echo -n "."
clean:
	-rm -f $(OBJS)
fclean:		clean
	-rm -f $(NAME)
re:			fclean all
rt:			re t
vf:			all
	$(VAL) $(VALFLAG) ./$(NAME) $(ARGS)
t:			all
	./$(NAME) $(ARGS)
v:			all
	$(VAL) ./$(NAME) $(ARGS)
g:			all
	gdb ./$(NAME) $(ARGS)
