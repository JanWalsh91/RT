/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_photon_global.cu                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 13:34:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/18 13:22:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"
#include "photon_mapping.h"

__device__
void			knn_search(t_vec3 *hit_pos, t_kd_tree *photon_map, t_selected_photon *photons, int dim, int k);
__device__
static float	get_dist_by_dim(t_vec3 *hit_pos, t_vec3 photon_pos, int dim);
__device__
static float	get_dist2(t_vec3 hit_pos, t_vec3 photon_pos);
__device__
static int		add_to_list(t_selected_photon *photons, t_kd_tree *photon, float dist2, int k);
__device__
static void		push_list(t_selected_photon *list, t_selected_photon tmp, int i, int k);
__device__
static int		more_points_can_be_found(float dist, t_selected_photon *list, int k);
__device__
static void		print_selected_photons(t_selected_photon *list, int k);

/*
** Gathers k photons from the photon map closest to the hitpoint and averages a color
** value based on incoming radiosity.
*/

__device__
t_color	get_photon_global(t_raytracing_tools *r, t_ray *ray)
{
	t_selected_photon *photons;
	int dim = 0;
	int k = 10;
	int i = -1;
	//malloc list of photons based on r->settings->k + 1

	// printf("get_photon_global\n");
	// printf("-----%p\n", r->scene->photon_map);
	// printf("in kernel selected_photons: [%p]\n", r->scene->selected_photons);
	// printf("in kernel selected_photons: [%p]\n", r->scene->selected_photons[1]);
	photons = r->scene->selected_photons[r->idx];
	// printf("-----%p\n", r->scene->se	lected_photons);
	// printf("-----%p, pix num: %d, idx: %d\n", r->scene->selected_photons[r->idx], r->scene->res.x * r->scene->res.y, r->idx);
	while (++i < k)
	{
		// printf("-----%p\n", photons);
		photons[i].photon = NULL;
	}
	// printf("hit pos: %p [%f, %f, %f]\n", &ray->hit, ray->hit.x, ray->hit.y, ray->hit.z);
	knn_search(&ray->hit, r->scene->photon_map, photons, dim, k);
	// printf("IM GONNA PRINT SOME PHOTONS\n");
	// print_selected_photons(photons, k);
	t_vec3 sum;
	i = -1;
	sum = v_new(0, 0, 0);
	while (++i < k && photons[i].photon)
	{
		sum.x += photons[i].photon->col.r;
		sum.y += photons[i].photon->col.g;
		sum.z += photons[i].photon->col.b;
	}
	sum = v_scale(sum, 1.0 / r->scene->photon_count);
	//Take sum of power of all photons corrected by Lambertian Shading, divide by number of photons shot
	//Convert to t_color and return.
	return (vec_to_col(sum));
}


/*
** knn = k Nearest Neighbor search
** Gathers k closest photons to the hit point.
*/

__device__
void		knn_search(t_vec3 *hit_pos, t_kd_tree *photon_map, t_selected_photon *photons, int dim, int k)
{
	int		dir;
	float	dist;

	// printf("knn_search\n");
	// print_selected_photons(photons, k);
	if (!photon_map)
	{
		// printf("no photon map\n");
		return ;
	}
	dim = dim == 3 ? 0 : dim;
	//compare current node.dim distance with pos.dim
	dist = get_dist_by_dim(hit_pos, photon_map->pos, dim);
	// printf("dist: %f\n", dist);
	dir = (dist < 0) ? 2 : 1;
	// printf("dir: %d\n", dir);
	//go either left or right (closest first)
	dir == 1 ? knn_search(hit_pos, photon_map->right, photons, dim + 1, k) :
				knn_search(hit_pos, photon_map->left, photons, dim + 1, k);
	// printf("hit pos: %p [%f, %f, %f]\n", hit_pos, hit_pos->x, hit_pos->y, hit_pos->z);
	// //check to see if you can add it to photon list
	add_to_list(photons, photon_map, get_dist2(*hit_pos, photon_map->pos), k);

	// //if k points have been found and the other branch cannot have points closer to any of the current bests
	// 	//do not go down other branch
	if (more_points_can_be_found(dist, photons, k))
		dir == 1 ? knn_search(hit_pos, photon_map->left, photons, dim + 1, k) :
			knn_search(hit_pos, photon_map->right, photons, dim + 1, k);
}

__device__
static float	get_dist_by_dim(t_vec3 *hit_pos, t_vec3 photon_pos, int dim)
{
	// printf("get_dist_by_dim\n");
	if (dim == 0)
		return (hit_pos->x - photon_pos.x);
	if (dim == 1)
		return (hit_pos->y - photon_pos.y);
	if (dim == 2)
		return (hit_pos->z - photon_pos.z);
	else
		return (INFINITY);
}

__device__
static float	get_dist2(t_vec3 hit_pos, t_vec3 photon_pos)
{
	// printf("get_dist2\n");
	float length;

	length = v_dot(hit_pos, photon_pos);
	length = length < 0 ? -length : length;
	return (length);
}

__device__
static int		add_to_list(t_selected_photon *photons, t_kd_tree *photon, float dist2, int k)
{
	// printf("add_to_list\n");
	int 				i;
	t_selected_photon	tmp;

	i = -1;
	while (++i <= k)
	{
		if (photons[i].photon == NULL || photons[i].dist2 > dist2)
		{
			tmp.photon = photon;
			tmp.dist2 = dist2;
			push_list((photons), tmp, i, k);
			return (1);
		}
	}
	return (0);
}

__device__
static void		push_list(t_selected_photon *list, t_selected_photon tmp, int i, int k)
{
	// printf("push_list\n");
	t_selected_photon tmp2;
	

	//if at end of list or at NULL photon, store photon at last position.
	if (i == k - 1 || list[i].photon == NULL)
	{
		list[i] = tmp;
		return ;
	}
	//else save that photon
	tmp2 = list[i];
	//push that photon 
	push_list((list), tmp2, i + 1, k);
	//then store the previous photon 
	list[i].photon = tmp.photon;
	list[i].dist2 = tmp.dist2;
}

__device__
static int	more_points_can_be_found(float dist, t_selected_photon *list, int k)
{
	// printf("more_points_can_be_found ");
	int i;

	if (!list[k - 1].photon) //last photon does not exist. is list[k] the last photon?!
	{
		// printf("1\n");
		return (1);
	}
	i = -1;
	//check dist of all photons against dist from plane
	while (++i < k)
	{
		//if a photon in the selected photon list is farther from the hit point that the plane, there are more solutions
		if (dist * dist < list[i].dist2)
		{
			// printf("1\n");
			return (1);
		}
	}
	// printf("0\n");
	return (0);
}

__device__
static void	print_selected_photons(t_selected_photon *list, int k)
{
	int i = -1;
	while (++i < k && list && list[i].photon)
		printf("k: %d, selected photon: %p, [%f, %f, %f]\n",
		k, &list[i], list[i].photon->pos.x, list[i].photon->pos.y, list[i].photon->pos.z);
}