# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: talemari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 15:17:33 by talemari          #+#    #+#              #
#    Updated: 2017/05/10 16:15:03 by talemari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 			ft_freetab.c\
				objparser.c\
				set_obj.c\
				get_vector_f.c\
				get_vector_i.c\
				get_float.c\
				get_number.c\
				main.c
LIB =			../../Libft/libft.a
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
	@-./$(NAME) teapot.obj
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
