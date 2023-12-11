NAME = irc

CC = c++

FLAGS = -g3 -Wall -Wextra -Werror -std=c++98

SRCS =	srcs/commands.cpp \
		srcs/Channel.cpp	\
		srcs/Client.cpp	\
		srcs/ft_server.cpp		\
		srcs/main.cpp

INCLUDES = -Isrcs/includes

OBJS = $(SRCS:.cpp=.o)

DEP = $(SRCS:.cpp=.d)

RM = rm -rf

all: $(NAME)
-include $(DEP)
.cpp.o:
	$(CC) -MMD -MP $(INCLUDES) $(FLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(INCLUDES) $(FLAGS) $(SRCS) -o $(NAME)

clean :
	$(RM) $(OBJS) $(DEP)

fclean : clean
	$(RM) $(NAME)

re : clean all

.PHONY : all clean fclean re