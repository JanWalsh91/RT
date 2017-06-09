# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 15:51:12 by jwalsh            #+#    #+#              #
#    Updated: 2017/06/09 10:05:33 by jwalsh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = RT
LIBFT_NAME = libft.a
LIBMATHFT_NAME = libmathft.a

SRC_PATH = src/
INC_PATH = inc/
LIB_PATH = Libft/
LIBMATH_PATH = Libmathft/

SRC = 		main

PARSING = 	get_color \
			get_file \
			get_token \
			init_color_list \
			init_parse_tools \
			init_tokens \
			parse_color_name \
			parse_float \
			parse_input \
			parse_value_1 \
			parse_value_10 \
			parse_value_12 \
			parse_value_13 \
			parse_value_2 \
			parse_value_3 \
			parse_value_4 \
			parse_value_5 \
			parse_value_6 \
			parse_value_7 \
			parse_value_8 \
			parse_value_9 \
			parse_vector \
			reset_attributes \
			set_attributes_1 \
			set_attributes_2 \
			set_attributes_3 \
			split_trim

DATA_PREP = check_objects \
			check_scene \
			init_cameras \
			set_default_1 \
			set_default_2 \
			set_default_3 \
			set_default_4 \
			set_default_5

LIST = 		get_new_camera \
			get_new_input \
			get_new_light \
			get_new_object \
			get_new_scene \
			input_pushback \
			push_camera \
			push_light \
			push_object \
			remove_camera \
			remove_light \
			remove_object

RAY_TRACING = cast_primary_ray \
			create_anaglyph \
			filter \
			filters \
			get_ambient \
			get_cartoon_effect \
			get_cone_intersection \
			get_cylinder_intersection \
			get_diffuse \
			get_disk_intersection \
			get_flares \
			get_fresnel_ratio \
			get_normal \
			get_normal2 \
			get_paraboloid_intersection \
			get_plane_intersection \
			get_reflected_and_refracted \
			get_specular \
			get_sphere_intersection \
			get_texture \
			get_view_pane_intersection \
			in_shadow \
			init_camera_ray \
			init_light_flares \
			intersects \
			reflect \
			refract \
			render \
			solve_quadratic \
			update_ior

MISC = 		check_file_ext \
			find_texture \
			free_parse_tools \
			free_scene \
			gpu_errchk \
			rt_error \
			tile \
			write_values

GUI =		get_widget \
			main_gtk \
			photon_mapping \
			sig_delete_camera \
			sig_delete_light \
			sig_delete_object \
			sig_errors \
			sig_export_scene_bmp \
			sig_generate_texture \
			sig_new_camera \
			sig_new_light \
			sig_new_object \
			sig_new_scene \
			sig_open_scene \
			sig_open_settings \
			sig_render \
			sig_save \
			sig_save_camera \
			sig_save_light \
			sig_save_object \
			sig_save_scene \
			sig_set_full_screen \
			sig_update_cameras \
			sig_update_cameras1 \
			sig_update_cameras2 \
			sig_update_cameras3 \
			sig_update_cameras4 \
			sig_update_cameras5 \
			sig_update_lights \
			sig_update_lights1 \
			sig_update_lights2 \
			sig_update_lights3 \
			sig_update_lights4 \
			sig_update_objects \
			sig_update_objects1 \
			sig_update_objects10 \
			sig_update_objects11 \
			sig_update_objects12 \
			sig_update_objects13 \
			sig_update_objects2 \
			sig_update_objects3 \
			sig_update_objects4 \
			sig_update_objects5 \
			sig_update_objects6 \
			sig_update_objects7 \
			sig_update_objects8 \
			sig_update_objects9 \
			sig_update_scene \
			sig_update_scene1 \
			sig_update_scene2 \
			sig_update_scene3 \
			sig_update_settings \
			sig_update_settings1 \
			window_signals \
			window_signals1

CUDA_MEM =	cuda_check_kernel_errors \
			cuda_free \
			cuda_malloc \
			cuda_malloc_camera \
			cuda_malloc_lights \
			cuda_malloc_objects \
			test_cuda_malloc

PHOTON_MAPPING = get_iors \
				malloc_region_map \
				photon_mapping_assist \
				photon_mapping_pass \
				radiance_estimation_pass \
				redirect_photon \
				shoot_photon \
				update_photon \
				update_region_map

TEXTURE =	export_bmp \
			generate_checkerboard \
			generate_noise \
			generate_perlin_noise \
			get_file_name \
			read_bmp

OBJ_DIR = obj

EXT_C = .c
EXT_CU = .cu

SRC_SRC = $(addsuffix $(EXT_C), $(SRC))
SRC_PARSING = $(addsuffix $(EXT_C), $(PARSING))
SRC_DATA = $(addsuffix $(EXT_C), $(DATA_PREP))
SRC_RT = $(addsuffix $(EXT_CU), $(RAY_TRACING))
SRC_LST = $(addsuffix $(EXT_C), $(LIST))
SRC_MISC = $(addsuffix $(EXT_C), $(MISC))
SRC_GUI = $(addsuffix $(EXT_C), $(GUI))
SRC_CUDA_MEM = $(addsuffix $(EXT_CU), $(CUDA_MEM))
SRC_PHOTON_MAPPING = $(addsuffix $(EXT_CU), $(PHOTON_MAPPING))
SRC_TEXTURE = $(addsuffix $(EXT_C), $(TEXTURE))

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC_SRC:.c=.o))
OBJ_PARSING = $(addprefix $(OBJ_DIR)/, $(SRC_PARSING:.c=.o))
OBJ_DATA = $(addprefix $(OBJ_DIR)/, $(SRC_DATA:.c=.o))
OBJ_RT = $(addprefix $(OBJ_DIR)/, $(SRC_RT:.cu=.o))
OBJ_LST = $(addprefix $(OBJ_DIR)/, $(SRC_LST:.c=.o))
OBJ_MISC = $(addprefix $(OBJ_DIR)/, $(SRC_MISC:.c=.o))
OBJ_GUI = $(addprefix $(OBJ_DIR)/, $(SRC_GUI:.c=.o))
OBJ_CUDA_MEM = $(addprefix $(OBJ_DIR)/, $(SRC_CUDA_MEM:.cu=.o))
OBJ_PHOTON_MAPPING = $(addprefix $(OBJ_DIR)/, $(SRC_PHOTON_MAPPING:.cu=.o))
OBJ_TEXTURE = $(addprefix $(OBJ_DIR)/, $(SRC_TEXTURE:.c=.o))

CC	= nvcc
NVCC = nvcc
CUFLAGS = -gencode=arch=compute_30,code=sm_30 -Xnvlink --disable-warnings
FLG = $(CUFLAGS) -Xcompiler="-Werror -Wextra -Wall"
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

$(NAME): $(OBJ_SRC) $(OBJ_PARSING) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) $(OBJ_GUI) $(OBJ_CUDA_MEM) $(OBJ_PHOTON_MAPPING) $(OBJ_TEXTURE)
	@make -C $(LIB_PATH)
	@make -C $(LIBMATH_PATH)
	@$(NVCC) $(CUFLAGS) $(GTK3_LIBS) $(LIB_PATH)$(LIBFT_NAME) $(LIBMATH_PATH)$(LIBMATHFT_NAME) $(OBJ_PARSING) $(OBJ_SRC) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) $(OBJ_GUI) $(OBJ_CUDA_MEM) $(OBJ_PHOTON_MAPPING) $(OBJ_TEXTURE) -o $(NAME)
	@$(ECHO) "$(C_GREEN)$(NAME) compilation done.$(C_NONE)"

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./src/parsing/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./src/list/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./src/data_prep/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./src/ray_tracing/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(NVCC) $(CUFLAGS) $(FLG) -I./inc -dc $< -o $@

$(OBJ_DIR)/%.o : ./src/misc/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./src/gui/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

$(OBJ_DIR)/%.o : ./src/cuda_mem/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(NVCC) $(CUFLAGS) $(FLG) -I./inc -dc $< -o $@

$(OBJ_DIR)/%.o : ./src/photon_mapping/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(NVCC) $(GTK3_INC) $(CUFLAGS) -I./inc -dc $< -o $@

$(OBJ_DIR)/%.o : ./src/texture/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
	@make -C $(LIB_PATH) clean
	@make -C $(LIBMATH_PATH) clean
	@$(ECHO) "$(C_GREEN)$(NAME) clean done.$(C_NONE)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@make -C $(LIBMATH_PATH) fclean
	@$(ECHO) "$(C_GREEN)$(NAME) fclean done.$(C_NONE)"

re: fclean all

PHONY : re all clean fclean
	@$(ECHO) "$(C_GREEN)$(NAME) .PHONY done.$(C_NONE)"

.PHONY: all clean fclean re
