# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: talemari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 15:17:33 by talemari          #+#    #+#              #
#    Updated: 2017/04/29 10:49:04 by talemari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 			srcs/ft_freetab.c\
				srcs/objparser.c\
				srcs/set_obj.c\
				srcs/get_number.c
LIB =			includes/libft/libft.a
OBJ = $(LIB)
NAME = ObjectParser
CFLAGS += -Wall -Wextra -Werror -g3
DLENGHT = 100
TTEXT = \nBEGIN TEST :\n
all : $(NAME)
$(NAME) : $(SRC) $(LIB)
	cc -o $(NAME) $(CFLAGS) $(SRC) $(LIB)
$(LIB) :
	cd includes/Libft/ && make
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)
supclean :
	rm -f $(NAME)
test : all
	@printf '\n%.0s' {1..3}
	@printf '#%.0s' {1..$(DLENGHT)}
	@printf '$(TTEXT)'
	@printf '\n%0.s' {1..3}
	@-./$(NAME) testmap
	@printf '\n%.0s' {1..3}
	@printf '#%.0s' {1..$(DLENGHT)}
	@printf '\n%0.s' {1..3}
	@-rm $(NAME)
backup :
	cp -rf ./* ../RTv1backup2/
re : fclean all
supre : supclean test
go : all clean
.PHONY : go re fclean clean all
