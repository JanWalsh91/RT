# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgros <tgros@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 15:51:12 by jwalsh            #+#    #+#              #
#    Updated: 2017/04/22 13:47:43 by tgros            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
LIBFT_NAME = libft.a
LIBMATHFT_NAME = libmathft.a

SRC_PATH = src/
INC_PATH = inc/
LIB_PATH = Libft/
LIBMATH_PATH = Libmathft/

SRC = 		main \
			rt

SDL = 		handle_sdl_events \
			init_sdl

PARSING = 	get_color \
			get_file \
			get_token \
			init_parse_tools \
			init_tokens \
			init_color_list \
			parse_color_name \
			parse_input \
			parse_value_1 \
			parse_value_2 \
			parse_value_3 \
			parse_value_4 \
			parse_value_5 \
			parse_value_6 \
			parse_value_7 \
			parse_value_8 \
			parse_value_9 \
			parse_vector \
			parse_double \
			reset_attributes \
			set_attributes_1 \
			set_attributes_2 \
			split_trim

DATA_PREP = check_scenes \
			check_objects \
			init_cameras \
			set_default_1 \
			set_default_2 \
			set_default_3 \
			set_default_4 \
			set_default_5

LIST = 		get_new_camera \
			get_new_light \
			get_new_object \
			get_new_scene \
			get_new_input \
			input_pushback \
			push_camera \
			push_light \
			push_object \
			remove_object \
			remove_camera \
			remove_light \
			push_scene 

RAY_TRACING = cast_primary_ray \
			render \
			get_normal \
			init_camera_ray \
			solve_quadratic \
			intersects \
			get_plane_intersection \
			get_sphere_intersection \
			get_disk_intersection \
			get_cylinder_intersection \
			get_cone_intersection \
			in_shadow \
			get_diffuse \
			get_specular \
			get_ambient \
			reflect \
			refract \
			filters \
			get_reflected_and_refracted \
			get_fresnel_ratio


MISC = 		debug \
			free_parse_tools \
			free_scenes \
			rt_error \
			export_bmp

GUI =		sig_open_scene \
			sig_update_scene \
			sig_update_objects \
			sig_update_lights \
			sig_update_cameras \
			sig_new_object \
			sig_new_camera \
			sig_new_light \
			sig_delete_object \
			sig_delete_light \
			sig_delete_camera \
			sig_save \
			sig_open_settings \
			sig_export_scene_bmp \

OBJ_DIR = obj

EXT_C = .c
EXT_CU = .cu

SRC_SRC = $(addsuffix $(EXT_C), $(SRC))
SRC_SDL = $(addsuffix $(EXT_C), $(SDL))
SRC_PARSING = $(addsuffix $(EXT_C), $(PARSING))
SRC_DATA = $(addsuffix $(EXT_C), $(DATA_PREP))
SRC_RT = $(addsuffix $(EXT_CU), $(RAY_TRACING))
SRC_LST = $(addsuffix $(EXT_C), $(LIST))
SRC_MISC = $(addsuffix $(EXT_C), $(MISC))
SRC_GUI = $(addsuffix $(EXT_C), $(GUI))

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC_SRC:.c=.o))
OBJ_SDL = $(addprefix $(OBJ_DIR)/, $(SRC_SDL:.c=.o))
OBJ_PARSING = $(addprefix $(OBJ_DIR)/, $(SRC_PARSING:.c=.o))
OBJ_DATA = $(addprefix $(OBJ_DIR)/, $(SRC_DATA:.c=.o))
OBJ_RT = $(addprefix $(OBJ_DIR)/, $(SRC_RT:.cu=.o))
OBJ_LST = $(addprefix $(OBJ_DIR)/, $(SRC_LST:.c=.o))
OBJ_MISC = $(addprefix $(OBJ_DIR)/, $(SRC_MISC:.c=.o))
OBJ_GUI = $(addprefix $(OBJ_DIR)/, $(SRC_GUI:.c=.o))

CC	= nvcc
NVCC = nvcc
CUFLAGS = -arch=sm_30
FLG = $(CUFLAGS) #-Werror -Wextra -Wall
SDL_PATH = sdl2/
SDL2 = `$(SDL_PATH)/sdl2-config --cflags --libs`
GTK3_LIBS = `pkg-config --libs gtk+-3.0`
GTK3_INC = `pkg-config --cflags gtk+-3.0`

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

ECHO = echo

all: $(NAME)

$(NAME): $(OBJ_SRC) $(OBJ_SDL) $(OBJ_PARSING) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) $(OBJ_GUI)
	@if [ ! -d "$(SDL_PATH)lib" ]; then \
		/bin/mkdir $(SDL_PATH)lib; \
		cd $(SDL_PATH) ; ./configure --prefix=`pwd`/lib; \
	fi
	@make -C $(SDL_PATH)
	@make -C $(SDL_PATH) install >/dev/null
	@$(ECHO) "$(C_CYAN)SDL2 compilation done.$(C_NONE)"
	@make -C $(LIB_PATH)
	@make -C $(LIBMATH_PATH)
	@$(NVCC) $(CUFLAGS) $(SDL2) $(GTK3_LIBS) $(LIB_PATH)$(LIBFT_NAME) $(LIBMATH_PATH)$(LIBMATHFT_NAME) $(OBJ_PARSING) $(OBJ_SRC) $(OBJ_SDL) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) $(OBJ_GUI) -o $(NAME)
	@$(ECHO) "$(C_GREEN)$(NAME) compilation done.$(C_NONE)"

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

$(OBJ_DIR)/%.o : ./src/sdl/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

$(OBJ_DIR)/%.o : ./src/parsing/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

$(OBJ_DIR)/%.o : ./src/list/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

$(OBJ_DIR)/%.o : ./src/data_prep/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

$(OBJ_DIR)/%.o : ./src/ray_tracing/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(NVCC) $(CUFLAGS) -I./inc -I./$(SDL_PATH)/include -dc $< -o $@

$(OBJ_DIR)/%.o : ./src/misc/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

$(OBJ_DIR)/%.o : ./src/gui/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC)  -dc -I./inc -I./$(SDL_PATH)/include -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
	# @/bin/rm -Rf $(SDL_PATH)lib
	# @/bin/rm -Rf $(SDL_PATH)build
	@$(ECHO) "$(C_CYAN)SDL2 clean done.$(C_NONE)"
	# @make -C $(LIB_PATH) clean
	# @make -C $(LIBMATH_PATH) clean
	@$(ECHO) "$(C_GREEN)$(NAME) clean done.$(C_NONE)"

fclean: clean
	@/bin/rm -f $(NAME)
	# @make./ -C $(LIB_PATH) fclean
	# @make -C $(LIBMATH_PATH) fclean
	@$(ECHO) "$(C_GREEN)$(NAME) fclean done.$(C_NONE)"

re: fclean all

PHONY : re all clean fclean
	@$(ECHO) "$(C_GREEN)$(NAME) .PHONY done.$(C_NONE)"

.PHONY: all clean fclean re
