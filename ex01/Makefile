# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 21:23:14 by andrefranci       #+#    #+#              #
#    Updated: 2024/07/12 23:54:57 by andrefranci      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler settings
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -Wshadow -std=c++98 -g #-fstandalone-debug #-fsanitize=address

# Directories
SRCDIR = src
OBJDIR = objs

# Source Files

SRCS =  $(SRCDIR)/main.cpp \
		$(SRCDIR)/Graph.cpp \
		$(SRCDIR)/Vector2.cpp
		
OBJS = 	$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Targets
NAME = I_dont_know_what_im_doing


all: 	$(NAME)


clean:
		rm -rf $(OBJDIR)

fclean:	clean
		rm -f $(NAME)

run:	fclean all
		./$(NAME)

re:		fclean all


valgrind: fclean all
		valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
		

$(NAME): 	$(OBJS)
			$(CXX) $(OBJS) $(CXXFLAGS) -o  $(NAME) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean fclean re run test