/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 12:11:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 12:28:53 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Contains functions for parsing each value based on token.
*/

static char	*init_perlin(t_parse_tools *t, char **res);
static char *init_checkerboard(t_parse_tools *t, char **res);
static char *init_noise(t_parse_tools *t, char **res);
static char	*init_bmp(t_parse_tools *t);

char		*read_texture_file(t_parse_tools *t)
{
	char			**res;
	int				i;
	char			*ret;

	printf("read_texture_file\n");
	if (!t->input->value)
		return ("Invalid texture name");
	res = ft_strsplit(t->input->value, ' ');
	if (!res)
		return ("Invalid texture name");
	ft_strtoupper(res[0]);
	if (ft_strcmp(res[0], "PERLIN") == 0 && !(ret = init_perlin(t, res)))
		return (ret);
	else if (ft_strcmp(res[0], "CHECKERBOARD") == 0 && !(ret =
		init_checkerboard(t, res)))
		return (ret);
	else if (ft_strcmp(res[0], "NOISE") == 0 && !(ret = init_noise(t, res)))
		return (ret);
	else if (!(ret = init_bmp(t)))
		return (ret);
	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
	return (NULL);
}

static char	*init_perlin(t_parse_tools *t, char **res)
{
	t_vec3	resolution;

	if (v_isnan(resolution = parse_vector(t->input->value + ft_strlen(res[0]))))
		return ("Position formatting error.");
	t->current_object->texture_name = ft_strdup("Perlin");
	resolution = v_clamp(resolution, 10, 2000);
	t->current_object->texture = generate_perlin_noise(&resolution);
	t->current_object->texture_dim = resolution;
	return (NULL);
}

static char	*init_checkerboard(t_parse_tools *t, char **res)
{
	t_vec3	resolution;

	if (v_isnan(resolution = parse_vector(t->input->value + ft_strlen(res[0]))))
		return ("Position formatting error.");
	t->current_object->texture_name = ft_strdup("Checkerboard");
	resolution = v_clamp(resolution, 10, 2000);
	while ((int)resolution.x % (int)resolution.z != 0)
		++resolution.x;
	if (((int)resolution.x / (int)resolution.z) % 2 == 1)
		resolution.x += resolution.z;
	while ((int)resolution.y % (int)resolution.z != 0)
		++resolution.y;
	if (((int)resolution.y / (int)resolution.z) % 2 == 1)
		resolution.y += resolution.z;
	t->current_object->texture = generate_checkerboard(&resolution);
	t->current_object->texture_dim = resolution;
	return (NULL);
}

static char	*init_noise(t_parse_tools *t, char **res)
{
	t_vec3	resolution;

	if (v_isnan(resolution = parse_vector(t->input->value + ft_strlen(res[0]))))
		return ("Position formatting error.");
	t->current_object->texture_name = ft_strdup("Noise");
	resolution.x = ft_clampf(resolution.x, 10, 2000);
	resolution.y = ft_clampf(resolution.y, 10, 2000);
	resolution.z = ft_clampf(resolution.z, 0, 100);
	t->current_object->texture = generate_noise(&resolution);
	t->current_object->texture_dim = resolution;
	return (NULL);
}

static char	*init_bmp(t_parse_tools *t)
{
	t_color		*texture;

	if (!check_file_ext(t->input->value, "BMP"))
		return ("Texture must be a bmp file.");
	printf("%s\n", t->input->value);
	if (!(texture = read_bmp(t->input->value, &t->current_object->texture_dim)))
		return (strerror(errno));
	t->current_object->texture_name = ft_strdup(t->input->value);
	t->current_object->texture = texture;
	return (NULL);
}
