#include "rt.h"

__device__
bool		get_torus_intersection(t_raytracing_tools *r, t_ray *ray,
				int index)
{
	t_quartic	qua;
	t_object	*obj = &r->scene->objects[index];
	t_vec4im	sol;
	float		res;

	qua.a = (powf(ray->dir.x, 4)) + (powf(ray->dir.y, 4) + (pow(ray->dir.z, 4))); 
	qua.b =	(4 * ((powf(ray->dir.x, 3) * ray->origin.x) + (powf(ray->dir.y, 3) * ray->origin.y) +
		(powf(ray->dir.y, 3) * ray->origin.y)));
	qua.c = (6 * ((powf(ray->dir.x, 2) * powf(ray->origin.x,2)) + (powf(ray->dir.y, 2) * powf(ray->origin.y, 2)) + (powf(ray->dir.y, 2) * powf(ray->origin.y, 2))) - 
		(5 (powf(ray->dir.x, 2) + powf(ray->dir.y, 2) + powf(ray->dir.z, 2)))); 
	qua.d = (4 * ((powf(ray->origin.x, 3) * ray->dir.x) + (powf(ray->origin.y, 3) * ray->dir.y) + (powf(ray->origin.y, 3) * ray->dir.y)) -
		(10 * (ray->dir.x * ray->origin.x) + (ray->dir.y * ray->origin.y) + (ray->dir.y * ray.origin.y)));
	qua.e = (powf(ray->origin.x, 4) + powf(ray->origin.y, 4) + powf(ray->origin.z, 4) - (5 (powf(ray->origin.x, 2) + powf(ray->origin.y, 2) + powf(ray->origin.z, 2))));
	

	if(!solve_quartic(&qua, &sol);
		return(false);
	if (isnan(sol.x.i) || isnan(sol.y.i))
		res = choose_between_four_roots(sol.w.r, sol.x.r, sol.y.r, sol.z.r);
	else
		res = choose_between_two_roots(sol.w.r, sol.z.r);
	if (res < 0)
		return (false);
	if (r->pix.y == 600 && r->pix.x == 600)
	{
	 r->t > res ? ray->t = res : 0;
	if (ray->type == R_PRIMARY && r->t > res)
	{
		ray->hit_obj = index;
		ray->hit_type = T_CUBETROUE;
	}
	return (true);
}