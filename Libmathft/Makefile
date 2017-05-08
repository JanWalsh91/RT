# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgros <tgros@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 13:07:31 by jwalsh            #+#    #+#              #
#    Updated: 2017/05/04 16:25:53 by tgros            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmathft.a

VECTORS_AND_MATRICES = c_add \
		c_min \
		c_mult \
		c_new \
		c_scale \
		m_new \
		m_new_identity \
		m_new_scale \
		m_new_rotate \
		m_new_rodriguez \
		m_translate \
		m_v_mult \
		m_p_mult \
		m_mult \
		m_add \
		m_scale \
		v_new \
		v_to_rot_matrix \
		v_dot \
		v_length \
		v_dist \
		v_norm \
		v_cross \
		v_add \
		v_sub \
		v_mult \
		v_scale \
		v_clamp \
		v_isnan \
		vec_to_col \
		col_to_vec

MISC = 	ft_abs \
		ft_power \
		ft_round \
		ft_rgb_mix \
		ft_to_radian \
		ft_swap \
		ft_swapf \
		ft_clampf

OBJ_DIR = obj

EXT = .cu

SRC_VECTORS_AND_MATRICES = $(addsuffix $(EXT), $(VECTORS_AND_MATRICES))
SRC_MISC = $(addsuffix $(EXT), $(MISC))
OBJ_VECTORS_AND_MATRICES = $(addprefix $(OBJ_DIR)/, $(SRC_VECTORS_AND_MATRICES:.cu=.o))
OBJ_MISC = $(addprefix $(OBJ_DIR)/, $(SRC_MISC:.cu=.o))

HEAD = libmathft.cuh

CC = nvcc

CFLAGS = -arch=sm_30#-Wall -Werror -Wextra

C_NONE = \033[0m
C_BOLD = \033[1m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_BROWN = \033[33m
C_BLUE = \033[34m
C_MAGENTA = \033[35m
C_CYAN = \033[36m
C_GRAY = \033[37m

all: $(NAME)

$(NAME):  $(OBJ_VECTORS_AND_MATRICES) $(OBJ_MISC) 
	@$(CC) $(CFLAGS) -lib $^ -o $(NAME)
	@echo "$(C_CYAN)Libmathft compilation done.$(C_NONE)"

$(OBJ_DIR)/%.o : ./vectors_and_matrices/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./misc/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -dc -I./inc -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
	@echo "$(C_CYAN)Libmathft clean done.$(C_NONE)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(C_CYAN)Libmathft fclean done.$(C_NONE)"

re: fclean
	@$(MAKE) all

.PHONY: clean fclean
	@echo "$(C_CYAN)Libmathft .PHONY done.$(C_NONE)"
