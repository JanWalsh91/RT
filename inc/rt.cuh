/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.cuh                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:28:08 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 16:29:55 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include "../Libft/inc/libft.h"
# include "../Libmathft/inc/libmathft.cuh"

# ifndef CUDA_DEV
#  ifdef __CUDACC__
#   define CUDA_DEV __device__
#  else
#   define CUDA_DEV
#  endif
# endif

/*
** General settings
*/

# define BLOCK_DIM 32
# define USAGE "usage: ./RT <file.rt>"
# define DEFAULT_RES_W 1000
# define DEFAULT_RES_H 1000
# define DEFAULT_RAY_DEPTH 5
# define MAX_RAY_DEPTH 10
# define DEFAULT_KA 0.1
# define DEFAULT_PPM_LIGHT_INTENSITY 1500
# define DEFAULT_AMBIENT_LIGHT_COLOR_R 255
# define DEFAULT_AMBIENT_LIGHT_COLOR_G 255
# define DEFAULT_AMBIENT_LIGHT_COLOR_B 255
# define DEFAULT_POS_X 0
# define DEFAULT_POS_Y 0
# define DEFAULT_POS_Z 0
# define DEFAULT_DIR_X 0
# define DEFAULT_DIR_Y 1
# define DEFAULT_DIR_Z 0
# define DEFAULT_COL_R 0xFF
# define DEFAULT_COL_G 0xFF
# define DEFAULT_COL_B 0xFF
# define DEFAULT_CAM_DIR_X 0
# define DEFAULT_CAM_DIR_Y 0
# define DEFAULT_CAM_DIR_Z 1
# define DEFAULT_FOV 45
# define DEFAULT_INTENSITY 10
# define DEFAULT_RADIUS 1
# define DEFAULT_HEIGHT 1
# define DEFAULT_KS 0.1
# define DEFAULT_KD 1
# define DEFAULT_SPECULAR_EXP 200
# define DEFAULT_IOR 1.01
# define DEFAULT_REFLECTION 0
# define DEFAULT_TRANSPARENCY 0
# define DEFAULT_TILE_SIZE 288
# define CAM_IMG_PANE_DIST 1
# define BIAS 0.001
# define INIT_IOR 1.0003
# define COLORS_PATH "res/colors.txt"
# define CSS_PATH "res/gtk.css"
# define CUDA_TEST 5
# define PHOTON_BOUNCE_MAX 5
# define PHOTON_SEARCH_RADIUS 10
# define cuda_device_prop cudaDeviceProp
# define cuda_pointer_attributes cudaPointerAttributes

/*
** Tokens for the parser.
*/

typedef enum	e_token
{
	T_OPEN_BRACKET,
	T_CLOSE_BRACKET,
	T_EMPTY_LINE,
	T_SCENE,
	T_CAMERA,
	T_LIGHT,
	T_PLANE,
	T_DISK,
	T_SPHERE,
	T_CYLINDER,
	T_CONE,
	T_PARABOLOID,
	T_RESOLUTION,
	T_RAY_DEPTH,
	T_BACKGROUND_COLOR,
	T_KA,
	T_AMBIENT_LIGHT_COLOR,
	T_POSITION,
	T_DIRECTION,
	T_LOOK_AT,
	T_COLOR,
	T_RADIUS,
	T_HEIGHT,
	T_DIFFUSE_COEF,
	T_REFRACTION_INDEX,
	T_REFLECTION,
	T_SPECULAR_EXPONENT,
	T_SPECULAR_COEF,
	T_TRANSPARENCY,
	T_FOV,
	T_INTENSITY,
	T_FILTER,
	T_READ_NORMAL_MAP,
	T_READ_TEXTURE_FILE,
	T_READ_MATERIAL_FILE,
	T_PARENT_INDEX,
	T_BEER_LAMBERT,
	T_KFLARE,
	T_HASHTAG,
	T_INVALID_TOKEN,
	T_COUNT
}				t_token;

typedef enum	e_filter
{
	F_NONE,
	F_BW,
	F_SEPIA,
	F_DEUTAN,
	F_LEFT_RED,
	F_RIGHT_CYAN
}				t_filter;

/*
** Link for linked list with info about each line parsed.
*/

typedef	struct	s_input
{
	int				token;
	char			*value;
	char			*file_name;
	size_t			line_number;
	struct s_input	*next;
}				t_input;

/*
** Link for linked list with info about colors read from external color file
*/

typedef struct	s_color_list
{
	t_vec3				value;
	char				*name;
	struct s_color_list	*next;
}				t_color_list;

/*
** Structure containing info about most attributes that entities can have
** res - resolution
** ambient_light_color - color of ambient lighting
** ka - ambient lighting intensity (0 - 1)
** intensity - light intensity
** fov - field of view (camera)
** pos - position
** dir - direction
** look_at - defines direction by position and a target
** col - color
** rad - radius
** height - height
** ks - specular coefficient (0 - 1)
** specular_exp - specular exponent
** kd - diffuse coefficient (0 - 1)
** ior - index of refraction
** reflection - reflection coefficient (0 - 1) (pending feature)
** transparency - transparency coefficient (0 - 1) (pending feature)
*/

typedef struct	s_attributes
{
	t_pt2			res;
	int				ray_depth;
	t_vec3			ambient_light_color;
	float			ka;
	float			intensity;
	float			kflare;
	float			fov;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			look_at;
	t_vec3			col;
	t_filter		filter;
	float			rad;
	float			height;
	float			ks;
	float			specular_exp;
	float			kd;
	float			ior;
	float			beer_lambert;
	float			reflection;
	float			transparency;
	unsigned short	parent_index;
	struct s_obj	*obj;
}				t_attributes;

/*
** Current type of rays thrown
*/

typedef enum	e_ray_type
{
	R_PRIMARY,
	R_SHADOW,
	R_DIRECT_PHOTON,
	R_INDIRECT_PHOTON
}				t_ray_type;

/*
** Structure containing info about a ray
** type - ray type (see above)
** origin - ray origin
** dir - ray direction
** t - distance to closest intersection, if any
** hit - hit point in World View
** hit_obj - pointer to object hit at intersection point
** hit_type - type of hit_obj
** nhit - normal at intersection point
** n_dir - direction (-1 or 1) of nhit
** col - color
*/

typedef	struct	s_ray
{
	t_ray_type		type;
	t_vec3			origin;
	t_vec3			dir;
	float			t;
	t_vec3			hit;
	int				hit_obj;
	t_token			hit_type;
	int				n_dir;
	t_vec3			nhit;
	t_color			col;
	float			ior;
	int				depth;
}				t_ray;

/*
** Link in linked list containing info about an object
** type - object type (see t_token)
** name - object name
** angle - calculated angle for cone
** (see t_attributes for more information)
*/

typedef struct	s_object
{
	t_token			type;
	char			*name;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			look_at;
	t_vec3			col;
	float			rad;
	float			height;
	float			angle;
	float			kd;
	float			ks;
	float			specular_exp;
	float			reflection;
	float			transparency;
	float			ior;
	float			beer_lambert;
	t_color			*texture;
	char			*texture_name;
	t_vec3			texture_dim;
	t_pt2			texture_ratio;
	t_pt2			texture_translate;
	char			texture_color_style;
	t_color			*normal_map;
	t_vec3			normal_map_dim;
	char			*normal_map_name;
	unsigned short	parent_index;
	struct s_object	*parent;
	struct s_object	*next;
}				t_object;

/*
** Link in linked list containing info about a light
** name - light name
** (see t_attributes for more information)
*/

typedef struct	s_light
{
	char			*name;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			look_at;
	t_vec3			col;
	float			intensity;
	float			kflare;
	struct s_light	*next;
}				t_light;

/*
** Link in linked list containing info about a camera
** name - camera name
** pixel_map - table of colors for each pixel
** ctw - Camera to World matrix
** scale - internal calculation based on fov
** (see t_attributes for more information)
*/

typedef struct	s_camera
{
	char			*name;
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			look_at;
	t_matrix		ctw;
	t_filter		filter;
	float			scale;
	float			fov;
	struct s_camera	*prev;
	struct s_camera	*next;
	float			ior;
}				t_camera;

/*
** Link containing info about one scene.
** res - resolution
** name - scene name
** cameras - linked list of cameras
** lights - linked list of lights
** objects - linked list of objects
** (see t_attributes for more information)
*/

typedef struct	s_scene
{
	t_pt2			res;
	char			*name;
	int				ray_depth;
	t_vec3			background_color;
	t_vec3			ambient_light_color;
	float			ka;
	float			image_aspect_ratio;
	float			ppm_light_intensity;
	bool			is_raytracing;
	bool			is_shadow;
	bool			is_diffuse;
	bool			is_specular;
	bool			is_3d;
	bool			is_fresnel;
	bool			is_photon_mapping;
	bool			is_cartoon_effect;
	char			is_aa;
	int				photon_count;
	int				photon_count_per_pass;
	int				photon_iteration;
	struct s_photon	*photon_list;
	t_camera		*cameras;
	t_light			*lights;
	t_object		*objects;
}				t_scene;

/*
** Structure with tools for parsing input files.
** input - linked list with info about each line
** scene - contains info about the scene
** current_* - pointers to relevant objects
** fd - current fd
** file_name - current file name
** global_attributes - attributes given outside scene declarations
** scene_attributes - attribtues given within scene declarations
**				      but outside object declarations
** object_attributes - attributes given within object declarations
** colors - linked list with color names and rgb values
** parse - list of function pointers for each token
*/

typedef struct	s_parse_tools
{
	bool			in_scene;
	bool			in_object;
	t_input			*input;
	t_input			*input_head;
	t_scene			*scene;
	t_object		*current_object;
	t_camera		*current_camera;
	t_light			*current_light;
	t_token			current_type;
	int				fd;
	char			*file_name;
	t_attributes	*global_attributes;
	t_attributes	*scene_attributes;
	t_attributes	*object_attributes;
	t_color_list	*colors;
	char			**tokens;
	char			*(**parse)(struct s_parse_tools *);
}				t_parse_tools;

/*
** Structure with tools for determining ray-object intersections.
** q - quadratic equation components
** r1, r2 - quadratic equation solutions/roots
** t - distance to closest intersection
** v1, v2, v3, p - extra temporary vectors
** d1, d2, d3 - extra temporary floats
** n_dir - direction of normal at point
*/

typedef struct	s_intersection_tools
{
	t_vec3			q;
	float			r1;
	float			r2;
	float			t;
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			v3;
	t_vec3			p;
	float			d1;
	float			d2;
	int				n_dir;
}				t_intersection_tools;

typedef	struct	s_light_flare_tools
{
	bool		is_valid;
	float		max_rad;
	float		dist;
	t_pt2		pos;
	t_light		*light;
	float		t;
}				t_light_flare_tools;

typedef struct	s_update
{
	uint8_t		resolution;
	uint8_t		ray_depth;
	uint8_t		objects;
	uint8_t		lights;
	uint8_t		cameras;
	uint8_t		scene;
	uint8_t		render;
	uint8_t		photon_map;
	uint8_t		anaglyph;
}				t_update;

/*
** Structure with tools to help with raytracing
** scene - contains info about the scene
** pix - coordinates of current pixel
** t - distance to closest intersection
*/

typedef	struct	s_rt_settings
{
	int		tile_size;
	int		photon_count_per_pass;
	float	photon_search_radius;
}				t_rt_settings;

typedef struct	s_raytracing_tools
{
	t_scene						*scene;
	t_scene						*d_scene;
	t_scene						*h_d_scene;
	t_color						*d_pixel_map;
	t_color						*rt_pixel_map;
	t_color						*d_pixel_map_3d;
	t_pt2						pix;
	float						t;
	t_update					update;
	uint8_t						rendering;
	t_rt_settings				settings;
	float						ior_list[MAX_RAY_DEPTH + 1];
	int							idx;
	struct curandStateXORWOW	*devStates;
	struct s_region				**h_region_map;
	struct s_region				*d_region_map;
	float						*rand_list;
}				t_raytracing_tools;

typedef struct	s_tile
{
	t_pt2	id;
	int		size;
	int		max;
	int		row;
	int		col;
}				t_tile;

typedef struct	s_th_export
{
	float				progress;
	char				*filename;
	struct s_gtk_tools	*g;
}				t_th_export;

/*
** Photon Mapping
*/

typedef struct	s_region
{
	t_vec3	hit_pt;
	t_vec3	ray_dir;
	t_vec3	normal;
	float	kd;
	float	radius;
	int		n;
	t_vec3	power;
}				t_region;

typedef struct	s_photon
{
	t_vec3		pos;
	t_vec3		dir;
	t_color		col;
	t_vec3		n;
	int			type;
}				t_photon;

/*
** File Parsing Functions
*/

void			init_parse_tools(t_parse_tools *t);
void			init_tokens(t_parse_tools *t);
char			*get_file(char *file_name, t_parse_tools *t);
int				get_token(t_parse_tools *t, char *key);
char			*parse_input(t_parse_tools *t);
t_input			*get_new_input(char *line, char *file_name, t_parse_tools *t);
char			**split_trim(char *s, char c);
void			set_non_values(t_object *new_object);
void			set_attributes(t_parse_tools *t, t_attributes *a);
void			set_attributes_camera(t_parse_tools *t, t_attributes *a);
void			set_attributes_light(t_parse_tools *t, t_attributes *a);
void			set_attributes_plane(t_parse_tools *t, t_attributes *a);
void			set_attributes_sphere(t_parse_tools *t, t_attributes *a);
void			set_attributes_cylinder(t_parse_tools *t, t_attributes *a);
void			set_attributes_cone(t_parse_tools *t, t_attributes *a);
void			set_attributes_paraboloid(t_parse_tools *t, t_attributes *a);
int				reset_attributes(t_attributes *att);
char			*parse_open_bracket(t_parse_tools *t);
char			*parse_close_bracket(t_parse_tools *t);
char			*parse_empty_line(t_parse_tools *t);
char			*parse_scene(t_parse_tools *t);
char			*parse_camera(t_parse_tools *t);
char			*parse_light(t_parse_tools *t);
char			*parse_kflare(t_parse_tools *t);
char			*parse_plane(t_parse_tools *t);
char			*parse_disk(t_parse_tools *t);
char			*parse_sphere(t_parse_tools *t);
char			*parse_cylinder(t_parse_tools *t);
char			*parse_cone(t_parse_tools *t);
char			*parse_paraboloid(t_parse_tools *t);
char			*parse_resolution(t_parse_tools *t);
char			*parse_ray_depth(t_parse_tools *t);
char			*parse_background_color(t_parse_tools *t);
char			*parse_ambient_light_color(t_parse_tools *t);
char			*parse_ka(t_parse_tools *t);
char			*parse_beer_lambert(t_parse_tools *t);
char			*parse_position(t_parse_tools *t);
char			*parse_direction(t_parse_tools *t);
char			*parse_look_at(t_parse_tools *t);
char			*parse_color(t_parse_tools *t);
char			*parse_radius(t_parse_tools *t);
char			*parse_height(t_parse_tools *t);
char			*parse_ior(t_parse_tools *t);
char			*parse_reflection(t_parse_tools *t);
char			*parse_diffuse_coef(t_parse_tools *t);
char			*parse_specular_coef(t_parse_tools *t);
char			*parse_specular_exponent(t_parse_tools *t);
char			*parse_transparency(t_parse_tools *t);
char			*parse_fov(t_parse_tools *t);
char			*parse_intensity(t_parse_tools *t);
char			*parse_filter(t_parse_tools *t);
char			*read_normal_map(t_parse_tools *t);
char			*read_texture_file(t_parse_tools *t);
char			*read_material_file(t_parse_tools *t);
char			*parse_parent_index(t_parse_tools *t);
char			*hashtag(t_parse_tools *t);
char			*invalid_token(t_parse_tools *t);
t_vec3			get_color(t_parse_tools *t, char *value);
t_vec3			parse_rgb(char *value);
t_vec3			parse_hexadecimal(char *value);
bool			valid_hex_format(char *value, int *i);
t_vec3			parse_color_name(t_parse_tools *t, char *value);
t_vec3			parse_vector(char *value);
float			parse_float(char *value);
char			*can_add_new_scene(t_parse_tools *t);
char			*can_add_new_object(t_parse_tools *t);
t_vec3			look_at_object(t_parse_tools *t, char *value);
char			*parse_obj(t_parse_tools *t);
char			*get_file_name(char *absolute_path);
int				check_file_ext(char *file_name, char *ext);


/*
** List management Functions
*/

t_scene			*get_new_scene(t_parse_tools *t);
t_object		*get_new_object(t_parse_tools *t);
t_light			*get_new_light(t_parse_tools *t);
t_camera		*get_new_camera(t_parse_tools *t);
void			push_object(t_object **objects, t_object *new_object);
void			push_light(t_light **lights_head, t_light *new_light);
void			push_camera(t_camera **cameras_head, t_camera *new_camera);
void			remove_object(t_object **objects, t_object *to_delete);
void			remove_light(t_light **lights, t_light *to_delete);
void			remove_camera(t_camera *to_delete, struct s_gtk_tools *g);
void			input_pushback(t_input **input, t_input *n);
int				init_color_list(t_color_list **colors);
bool			find_color_value(t_color_list *colors, char *value,
					t_vec3 *new_col);
int				get_hex_value(char c);

/*
** Data Checking Functions
*/

char			*check_scene(t_scene *scene);
void			check_objects(t_scene *scene, t_object *objects);
void			init_camera(t_camera *cam);
void			update_camera_scale(t_camera *camera);
void			update_camera_ctw(t_camera *camera);

/*
** Set Default Functions
*/

void			set_default_resolution(t_scene *scene);
void			set_default_ray_depth(t_scene *scene);
void			set_default_ka(t_scene *scene);
void			set_default_ppm_light_intensity(t_scene *scene);
void			set_default_ambient_light_color(t_scene *scene);
void			set_default_pos(t_scene *scene, int type, void *obj,
					t_vec3 *pos);
void			set_default_col(t_scene *scene, int type, void *obj,
					t_vec3 *col);
void			set_default_intensity(t_scene *scene, int type, void *obj,
					float *intensity);
void			set_default_radius(t_scene *scene, int type, void *obj,
					float *radius);
void			set_default_height(t_scene *scene, int type, void *obj,
					float *height);
void			set_default_cam_dir(t_scene *scene, int type, void *cam,
					t_vec3 *dir);
void			set_default_obj_dir(t_scene *scene, int type, void *obj,
					t_vec3 *dir);
void			set_default_light_dir(t_scene *scene, int type, void *obj,
					t_vec3 *dir);
void			set_default_fov(t_scene *scene, int type, void *obj,
					float *fov);
void			set_default_ks(t_scene *scene, int type, void *obj, float *ks);
void			set_default_kd(t_scene *scene, int type, void *obj, float *kd);
void			set_default_specular_exp(t_scene *scene, int type, void *obj,
					float *specular_exp);
void			set_default_ior(t_scene *scene, int type, void *obj,
														float *ior);
void			set_default_reflection(t_scene *scene, int type, void *obj,
													float *reflection);
void			set_default_transparency(t_scene *scene, int type, void *obj,
												float *transparency);

/*
** Cuda Malloc Functions
*/

bool			cuda_malloc_objects(t_raytracing_tools *r, t_scene
												*h_scene_to_array);
bool			cuda_malloc_lights(t_raytracing_tools *r, t_scene
												*h_scene_to_array);
bool			cuda_malloc_camera(t_raytracing_tools *r);
t_list			*ft_lstnew_cuda(void const *content, size_t content_size);
bool			test_cuda_malloc(void **to_malloc, size_t size);

/*
** Ray Tracing Functions
*/

CUDA_DEV
void			*rt(struct s_gtk_tools *r);
CUDA_DEV
t_ray			init_camera_ray(t_raytracing_tools *r, t_dpt2 current_pos_pix);
CUDA_DEV
t_color			cast_primary_ray(t_raytracing_tools *r, t_ray *ray);
CUDA_DEV
void			get_normal(t_ray *ray, t_object *obj);
CUDA_DEV
void			get_sphere_normal(t_ray *ray, t_object *obj);
CUDA_DEV
void			get_plane_normal(t_ray *ray, t_object *obj);
CUDA_DEV
void			get_cylinder_normal(t_ray *ray, t_object *obj);
CUDA_DEV
void			get_cone_normal(t_ray *ray, t_object *obj);
CUDA_DEV
void			get_paraboloid_normal(t_ray *ray, t_object *obj);
CUDA_DEV
t_vec3			get_normal_at_normal_map(t_object *obj, t_ray *ray);
CUDA_DEV
int				in_shadow(t_raytracing_tools *r, t_ray *shadow_ray,
					t_light *light, t_vec3 *dim_light);
CUDA_DEV
t_color			get_diffuse(t_scene *scene, t_ray *primary_ray,
					t_ray *shadow_ray, t_light *light);
CUDA_DEV
t_color			get_specular(t_scene *scene, t_ray *primary_ray,
					t_ray *shadow_ray, t_light *light);
CUDA_DEV
t_color			get_reflected_and_refracted(t_raytracing_tools *r,
									t_scene *scene, t_ray *ray);
CUDA_DEV
void			update_ior(float *n1, float *n2, t_raytracing_tools *r,
													t_ray *ray);
CUDA_DEV
float			get_fresnel_ratio(t_vec3 ray_dir, t_vec3 normal,
											float n1, float n2);
CUDA_DEV
t_color			get_ambient(t_scene *scene, t_ray *ray);
CUDA_DEV
t_vec3			reflect(t_vec3 ray_dir, t_vec3 nhit);
CUDA_DEV
t_vec3			refract(t_vec3 ray_dir, t_vec3 nhit, float ray_ior,
													float new_ior);
CUDA_DEV
t_color			update_photon(t_raytracing_tools *r, t_ray *ray);
CUDA_DEV
t_color			get_photon_global(t_raytracing_tools *r, t_ray *ray);

/*
** Photon Mapping
*/

CUDA_DEV
void			update_region_map(t_raytracing_tools *r, t_ray *cam_ray);
CUDA_DEV
void			get_iors(float *n1, float *n2, t_raytracing_tools *r, t_ray *ray);
void			render_ppm(struct s_gtk_tools *g, t_tile tile);
void			shoot_photon_wrapper(t_raytracing_tools *r, size_t photon_count,
													t_photon *init_photon_list);
CUDA_DEV
int				fresnel_reflect(t_raytracing_tools *r, t_ray *ray);
CUDA_DEV
void			redirect_photon_diffuse(t_raytracing_tools *r, t_ray *ray,
																float p);
CUDA_DEV
void			redirect_photon_specular(t_raytracing_tools *r, t_ray *ray,
																float p);
CUDA_DEV
void			redirect_photon_transmit(t_raytracing_tools *r, t_ray *ray,
																float p);

/*
** Intersection functions.
*/

CUDA_DEV
bool			intersects(t_raytracing_tools *r, t_ray *ray, int index);
CUDA_DEV
bool			get_plane_intersection(t_raytracing_tools *r, t_ray *ray,
					int index);
CUDA_DEV
bool			get_sphere_intersection(t_raytracing_tools *r, t_ray *ray,
					int index);
CUDA_DEV
bool			get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
					int index);
CUDA_DEV
bool			get_cone_intersection(t_raytracing_tools *r, t_ray *ray,
					int index);
CUDA_DEV
bool			get_disk_intersection(t_raytracing_tools *r, t_ray *ray,
					int index);
CUDA_DEV
bool			get_paraboloid_intersection(t_raytracing_tools *r, t_ray *ray,
					int index);
CUDA_DEV
bool			get_view_pane_intersection(t_ray *ray, t_camera *cam);
CUDA_DEV
bool			solve_quadratic(t_vec3 q, float *r1, float *r2);

/*
** Filters functions
*/

CUDA_DEV
t_color			filter(t_color orig, t_filter filter);
CUDA_DEV
t_color			b_w_filter(t_color c);
CUDA_DEV
t_color			b_w_filter_average(t_color c);
CUDA_DEV
t_color			sepia_filter(t_color c);
CUDA_DEV
t_color			deutan_filter(t_color c);
CUDA_DEV
t_color			right_cyan_filter(t_color c);
CUDA_DEV
t_color			left_red_filter(t_color c);

void			*export_image(void *th_export);
t_color			*read_bmp(char *file_name, t_vec3 *dim);
t_object		*find_texture(t_object *head, t_object *to_cmp, char
											*texture_name, t_vec3 dim);



/*
** Textures Functions
*/

t_color			*generate_perlin_noise(t_vec3 *res);
t_color			*generate_checkerboard(t_vec3 *res);
t_color			*generate_noise(t_vec3 *res);
CUDA_DEV
t_pt2			get_uv_coord(t_object *obj, t_ray *ray, t_vec3 *dim);
CUDA_DEV
t_pt2			get_uv_sphere(t_object *obj, t_ray *ray, t_vec3 *dim);
CUDA_DEV
t_pt2			get_uv_plane(t_object *obj, t_ray *ray, t_vec3 *dim);
CUDA_DEV
t_pt2			get_uv_cylinder(t_object *obj, t_ray *ray, t_vec3 *dim);
CUDA_DEV
t_pt2			get_uv_cone(t_object *obj, t_ray *ray, t_vec3 *dim);
CUDA_DEV
t_vec3			get_texture_at_uv_coord(t_object *obj, t_pt2 coord);
CUDA_DEV
t_vec3			get_object_color(t_object *obj, t_ray *ray);

/*
** Flare
*/

void			init_light_flares_wrapper(int light_count, t_raytracing_tools *r,
												t_light_flare_tools *tools);

/*
** Free Functions
*/

void			free_parse_tools(t_parse_tools *t);
void			free_scene(t_scene *scene);

/*
** Error Functions
*/

void			rt_file_error_exit(t_parse_tools *t, char *msg);
void			rt_file_warning(t_parse_tools *t, char *msg);
void			data_error_exit(t_scene *scene, int type, void *object,
					char *msg);
void			data_warning(t_scene *scene, int type, void *object,
														char *msg);
void 			gpu_errchk(int code);

/*
** Debug functions
*/

void			print_scene(t_scene *scene);
void			print_attributes(t_attributes att);
void			print_vec(t_vec3 vec);
void			print_matrix(t_matrix m);

#endif
