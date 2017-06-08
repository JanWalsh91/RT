# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgros <tgros@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/27 15:51:12 by jwalsh            #+#    #+#              #
#    Updated: 2017/06/08 11:36:42 by tgros            ###   ########.fr        #
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
			parse_value_10 \
			parse_value_11 \
			parse_value_12 \
			parse_value_13 \
			parse_vector \
			parse_float \
			reset_attributes \
			set_attributes_1 \
			set_attributes_2 \
			set_attributes_3 \
			split_trim

DATA_PREP = check_scene \
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
			remove_light

RAY_TRACING = cast_primary_ray \
			render \
			get_normal \
			get_normal2 \
			init_camera_ray \
			solve_quadratic \
			intersects \
			get_plane_intersection \
			get_sphere_intersection \
			get_disk_intersection \
			get_cylinder_intersection \
			get_cone_intersection \
			get_paraboloid_intersection \
			get_object_intersection \
			get_triangle_intersection \
			get_view_pane_intersection \
			in_shadow \
			get_diffuse \
			get_specular \
			get_ambient \
			reflect \
			refract \
			filters \
			filter \
			get_reflected_and_refracted \
			get_fresnel_ratio \
			get_texture \
			get_flares \
			init_light_flares \
			update_ior \
			create_anaglyph \
			get_cartoon_effect

MISC = 		debug \
			free_parse_tools \
			free_scene \
			rt_error \
			check_file_ext \
			find_texture \
			tile \
			write_values \
			gpu_errchk

GUI =		window_signals \
			window_signals1 \
			get_widget \
			sig_open_scene \
			sig_update_scene \
			sig_update_scene1 \
			sig_update_scene2 \
			sig_update_scene3 \
			sig_update_objects \
			sig_update_objects1 \
			sig_update_objects2 \
			sig_update_objects3 \
			sig_update_objects4 \
			sig_update_objects5 \
			sig_update_objects6 \
			sig_update_objects7 \
			sig_update_objects8 \
			sig_update_objects9 \
			sig_update_objects10 \
			sig_update_objects11 \
			sig_update_objects12 \
			sig_update_objects13 \
			sig_update_lights \
			sig_update_lights1 \
			sig_update_lights2 \
			sig_update_lights3 \
			sig_update_lights4 \
			sig_update_cameras \
			sig_update_cameras1 \
			sig_update_cameras2 \
			sig_update_cameras3 \
			sig_update_cameras4 \
			sig_update_cameras5 \
			sig_update_settings \
			sig_update_settings1 \
			sig_new_object \
			sig_new_camera \
			sig_new_light \
			sig_new_scene \
			sig_delete_object \
			sig_delete_light \
			sig_delete_camera \
			sig_save \
			sig_save_object \
			sig_save_scene \
			sig_save_camera \
			sig_save_light \
			sig_open_settings \
			sig_export_scene_bmp \
			sig_print_scene \
			sig_render \
			sig_set_full_screen \
			sig_generate_texture \
			sig_errors \
			photon_mapping

CUDA_MEM =	cuda_check_kernel_errors \
			cuda_malloc \
			ft_lstnew_cuda \
			cuda_malloc_camera \
			cuda_malloc_lights \
			cuda_malloc_objects \
			cuda_free \
			test_cuda_malloc

OBJ_PARSER = 	ft_freetab \
				ft_isnumeric \
				get_number \
				get_float \
				objparser \
				get_vector_i \
				get_vector_f \
				get_vector_2f \
				print_triangles \
				objparser_error \
				set_obj

PHOTON_MAPPING = update_photon \
				photon_mapping_pass \
				radiance_estimation_pass \
				malloc_region_map \
				update_region_map \
				shoot_photon \
				get_iors \
				redirect_photon

TEXTURE =	export_bmp \
			read_bmp \
			get_file_name \
			generate_perlin_noise \
			generate_checkerboard \
			generate_noise \

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
SRC_OBJ_PARSER = $(addsuffix $(EXT_C), $(OBJ_PARSER))
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
OBJ_OBJ_PARSER = $(addprefix $(OBJ_DIR)/, $(SRC_OBJ_PARSER:.c=.o))
OBJ_PHOTON_MAPPING = $(addprefix $(OBJ_DIR)/, $(SRC_PHOTON_MAPPING:.cu=.o))
OBJ_TEXTURE = $(addprefix $(OBJ_DIR)/, $(SRC_TEXTURE:.c=.o))

CC	= nvcc
NVCC = nvcc
CUFLAGS = -gencode=arch=compute_30,code=sm_30 #-Xnvlink --disable-warnings #A remettre pour la correction
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

$(NAME): $(OBJ_SRC) $(OBJ_PARSING) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) $(OBJ_GUI) $(OBJ_CUDA_MEM) $(OBJ_OBJ_PARSER) $(OBJ_PHOTON_MAPPING) $(OBJ_TEXTURE)
	@make -C $(LIB_PATH)
	@make -C $(LIBMATH_PATH)
	@$(NVCC) $(CUFLAGS) $(GTK3_LIBS) $(LIB_PATH)$(LIBFT_NAME) $(LIBMATH_PATH)$(LIBMATHFT_NAME) $(OBJ_PARSING) $(OBJ_SRC) $(OBJ_LST) $(OBJ_DATA) $(OBJ_RT) $(OBJ_MISC) $(OBJ_GUI) $(OBJ_CUDA_MEM) $(OBJ_OBJ_PARSER) $(OBJ_PHOTON_MAPPING) $(OBJ_TEXTURE) -o $(NAME)
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

$(OBJ_DIR)/%.o : ./src/objparser/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) -I./inc -dc $< -o $@

$(OBJ_DIR)/%.o : ./src/photon_mapping/%.cu
	@/bin/mkdir -p $(OBJ_DIR)
	@$(NVCC) $(GTK3_INC) $(CUFLAGS) -I./inc -dc $< -o $@

$(OBJ_DIR)/%.o : ./src/texture/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) $(GTK3_INC) -dc -I./inc -o $@ $<

clean:
	@/bin/rm -Rf $(OBJ_DIR)
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
