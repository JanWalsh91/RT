/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.cuh                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 12:07:23 by tgros             #+#    #+#             */
/*   Updated: 2017/05/02 11:07:08 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <cuda.h>
# include "../Libft/inc/libft.h"

# include "../Libmathft/inc/libmathft.cuh"

#ifndef CUDA_DEV
#ifdef __CUDACC__
#define CUDA_DEV __device__
#else
#define CUDA_DEV
#endif
#endif


/*
** General settings
*/

# define BLOCK_DIM 32
# define USAGE "usage: ./RT <file.rt>"
# define DEFAULT_RES_W 1000
# define DEFAULT_RES_H 1000
# define DEFAULT_RAY_DEPTH 5
# define DEFAULT_KA 0.1
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
# define DEFAULT_IOR 1.1
# define DEFAULT_REFLECTION 0
# define DEFAULT_TRANSPARENCY 0
# define CAM_IMG_PANE_DIST 1
# define BIAS 0.01
# define INIT_IOR 1.0003 // initial index of refraction (air)
# define COLORS_PATH "res/colors.txt"
# define CSS_PATH "res/gtk.css"

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
	T_RESOLUTION,
	T_RAY_DEPTH,
	T_BACKGROUND_COLOR,
	T_KA,
	T_AMBIENT_LIGHT_COLOR,
	T_POSITION,
	T_DIRECTION,
	T_ROTATION,
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
	T_READ_RT_FILE,
	T_READ_OBJ_FILE,
	T_READ_TEXTURE_FILE,
	T_READ_MATERIAL_FILE,
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
** rot - rotation (pending feature)
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
	t_pt2		res;
	int			ray_depth;
	t_vec3		ambient_light_color;
	float		ka;
	float		intensity;
	float		fov;
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		rot;
	t_vec3		look_at;
	t_vec3		col;
	t_filter	filter;
	float		rad;
	float		height;
	float		ks;
	float		specular_exp;
	float		kd;
	float		ior;
	float		reflection;
	float		transparency;
}				t_attributes;

/*
** Current type of rays thrown
*/

typedef enum	e_ray_type
{
	R_PRIMARY,
	R_SHADOW
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
	int				hit_obj; //index of hit obj
	t_token			hit_type;
	int				n_dir;
	t_vec3			nhit;
	t_color			col;
	float			ior; //current index of refraction
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
	t_vec3			rot;
	t_vec3			look_at;
	t_vec3			col;
	t_color			*texture;
	t_pt2			texture_dim;
	float			rad;
	float			height;
	float			angle;
	float			kd;
	float			ks;
	float			ior;
	float			reflection;
	float			specular_exp;
	float			transparency; // TODO
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
	t_vec3			rot;
	t_vec3			look_at;
	t_vec3			col;
	float			intensity;
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
	t_vec3			rot;
	t_vec3			look_at;
	t_color			*pixel_map;
	t_matrix		ctw;
	t_filter		filter;
	float			scale;
	float			fov;
	struct s_camera	*prev;
	struct s_camera	*next;
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
	bool			is_shadow;
	bool			is_diffuse;
	bool			is_specular;
	uint8_t			is_3d;
	t_camera		*cameras;
	t_light			*lights;
	t_object		*objects;
	struct s_scene	*prev;
	struct s_scene	*next;
}				t_scene;

/*
** Structure with tools for parsing input files.
** input - linked list with info about each line
** scenes - linked list with info about all scenes
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
	t_scene			*scenes;
	t_scene			*current_scene;
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

typedef struct	s_update
{
	uint8_t		resolution;
	uint8_t		ray_depth;
	uint8_t		objects;
	uint8_t		lights;
	uint8_t		cameras;
	uint8_t		scene;
	uint8_t		render;
}				t_update;


/*
** Structure with tools to help with raytracing
** scenes - contains info about all scenes
** pix - coordinates of current pixel
** t - distance to closest intersection
*/

typedef	struct	s_rt_settings
{
	int		tile_size;
}				t_rt_settings;

typedef struct	s_raytracing_tools
{
	t_scene			*scene;
	t_scene			*d_scene;
	t_scene			*h_d_scene;
	t_color			*d_pixel_map;
	t_color			*d_pixel_map_3d;
	t_pt2			pix;
	float			t;
	t_update		update;
	uint8_t			rendering;
	t_rt_settings	settings;
}				t_raytracing_tools;


typedef struct	s_th_export
{
	float	progress;
	char	*filename;
	struct s_gtk_tools *g;
}				t_th_export;

// int		cuda_malloc(struct s_raytracing_tools *r);
// int		cuda_free(struct s_raytracing_tools *r);

void	*main_gtk(struct s_gtk_tools *g);

/*
** File Parsing Functions
*/

void			init_parse_tools(t_parse_tools *t);
void			init_tokens(t_parse_tools *t);
char			*get_file(char *file_name, t_parse_tools *t);
int				get_token(t_parse_tools *t, char *key);
char			*parse_input(t_parse_tools *t);
char			**split_trim(char *s, char c);
void			set_non_values(t_object *new_object);
void			set_attributes(t_parse_tools *t, t_attributes *a);
void			set_attributes_camera(t_parse_tools *t, t_attributes *a);
void			set_attributes_light(t_parse_tools *t, t_attributes *a);
void			set_attributes_plane(t_parse_tools *t, t_attributes *a);
void			set_attributes_sphere(t_parse_tools *t, t_attributes *a);
void			set_attributes_cylinder(t_parse_tools *t, t_attributes *a);
void			set_attributes_cone(t_parse_tools *t, t_attributes *a);
int				reset_attributes(t_attributes *att);
char			*parse_open_bracket(t_parse_tools *t);
char			*parse_close_bracket(t_parse_tools *t);
char			*parse_empty_line(t_parse_tools *t);
char			*parse_scene(t_parse_tools *t);
char			*parse_camera(t_parse_tools *t);
char			*parse_light(t_parse_tools *t);
char			*parse_plane(t_parse_tools *t);
char			*parse_disk(t_parse_tools *t);
char			*parse_sphere(t_parse_tools *t);
char			*parse_cylinder(t_parse_tools *t);
char			*parse_cone(t_parse_tools *t);
char			*parse_resolution(t_parse_tools *t);
char			*parse_ray_depth(t_parse_tools *t);
char			*parse_background_color(t_parse_tools *t);
char			*parse_ambient_light_color(t_parse_tools *t);
char			*parse_ka(t_parse_tools *t);
char			*parse_position(t_parse_tools *t);
char			*parse_direction(t_parse_tools *t);
char			*parse_rotation(t_parse_tools *t);
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
char			*read_rt_file(t_parse_tools *t);
char			*read_obj_file(t_parse_tools *t);
char			*read_texture_file(t_parse_tools *t);
char			*read_material_file(t_parse_tools *t);
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
char				*can_add_new_object(t_parse_tools *t);
t_vec3			look_at_object(t_parse_tools *t, char *value);

/*
** List management Functions
*/

t_scene			*get_new_scene(t_parse_tools *t);
t_object		*get_new_object(t_parse_tools *t);
t_light			*get_new_light(t_parse_tools *t);
t_camera		*get_new_camera(t_parse_tools *t);
t_input			*get_new_input(char *line, char *file_name, int fd,
					t_parse_tools *t);
void			push_scene(t_scene **scenes, t_scene *new_scene);
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

char			*check_scenes(t_scene *scenes);
void			check_objects(t_scene *scene, t_object *objects);
void			init_camera(t_scene *scene, t_camera *cam);
void			update_camera_scale(t_camera *camera);
void			update_camera_ctw(t_camera *camera);

/*
** Set Default Functions
*/

void			set_default_resolution(t_scene *scene);
void			set_default_ray_depth(t_scene *scene);
void			set_default_ka(t_scene *scene);
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
void	set_default_ior(t_scene *scene, int type, void *obj, float *ior);					
void	set_default_reflection(t_scene *scene, int type, void *obj, float *reflection);
void	set_default_transparency(t_scene *scene, int type, void *obj, float *transparency);

/*
** Ray Tracing Functions
*/

CUDA_DEV
void			*rt(struct s_gtk_tools *r);
CUDA_DEV
t_ray			init_camera_ray(t_raytracing_tools *r);
CUDA_DEV
t_color			cast_primary_ray(t_raytracing_tools *r, t_ray *ray);
CUDA_DEV
void			get_normal(t_ray *ray, t_object *obj);
CUDA_DEV
int				in_shadow(t_raytracing_tools *r, t_ray *primary_ray,
					t_ray *shadow_ray, t_light *light, t_color *dim_light);
CUDA_DEV
t_color			get_diffuse(t_scene *scene, t_ray *primary_ray,
					t_ray *shadow_ray, t_light *light);
CUDA_DEV
t_color			get_specular(t_scene *scene, t_ray *primary_ray,
					t_ray *shadow_ray, t_light *light);
CUDA_DEV
t_color			get_reflected_and_refracted(t_raytracing_tools *r, t_scene *scene, t_ray *ray);	
CUDA_DEV
float			get_fresnel_ratio(t_vec3 ray_dir, t_vec3 normal, float ior);				
CUDA_DEV
t_color			get_ambient(t_scene *scene);
CUDA_DEV
t_vec3			reflect(t_vec3 ray_dir, t_vec3 nhit);
CUDA_DEV
t_vec3			refract(t_vec3 ray_dir, t_vec3 nhit, float ior);

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
t_color			*read_bmp(char *file_name, t_pt2 *dim);



/*
** Textures Functions
*/
CUDA_DEV
t_pt2			get_uv_sphere(t_object *obj, t_ray *ray);
CUDA_DEV
t_pt2			get_uv_plane(t_object *obj, t_ray *ray);
CUDA_DEV
t_pt2			get_uv_cylinder(t_object *obj, t_ray *ray);
CUDA_DEV
t_pt2			get_uv_cone(t_object *obj, t_ray *ray);
CUDA_DEV
t_color			get_texture_at_uv_coord(t_object *obj, t_pt2 coord);


/*
** Free Functions
*/

void			free_parse_tools(t_parse_tools *t);
void			free_scenes(t_scene *scenes);

/*
** Error Functions
*/

void			rt_file_error_exit(t_parse_tools *t, char *msg);
void			rt_file_warning(t_parse_tools *t, char *msg);
void			data_error_exit(t_scene *scene, int type, void *object,
					char *msg);
void			data_warning(t_scene *scene, int type, void *object, char *msg);

/*
** Debug functions
*/

# define C(...) printf("check%i\n", __VA_ARGS__);
# define P(x) ft_printf(x);

void			print_scenes(t_scene *scenes_head);
void			print_attributes(t_attributes att);
void			print_vec(t_vec3 vec);
void			print_matrix(t_matrix m);

#endif
