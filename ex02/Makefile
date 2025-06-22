C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98

INFILES = main.cpp
OBJFILES = $(INFILES:.cpp=.o)

NAME = PmergeMe

all: $(NAME)

$(NAME): $(OBJFILES)
	$(C++) $(C++_FLAGS) $(OBJFILES) -o $(NAME)

%.o: %.cpp
	$(C++) $(C++_FLAGS) -c $< -o $@

main.o: PMergeMe.hpp PMergeMe.tpp

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re