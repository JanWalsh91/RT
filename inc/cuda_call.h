/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_call.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:35:59 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 14:54:17 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDA_CALL_H
#define CUDA_CALL_H

#ifdef __cplusplus
extern "C"
#endif
int		cuda_malloc(struct s_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	malloc_region_map(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void	cuda_malloc_region_map_tile(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void	render(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void			radiance_estimation_pass(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void			photon_mapping_pass(struct s_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	get_flares(struct s_raytracing_tools *r, struct s_color *pixel_map);
#ifdef __cplusplus
extern "C"
#endif
int		cuda_free(struct s_raytracing_tools *r, int all);
#ifdef __cplusplus
extern "C"
#endif
void	update_photon_map(struct s_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	copy_region_map_tile(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void	refresh_region_map_tile(struct s_raytracing_tools *r, struct s_tile t);
#ifdef __cplusplus
extern "C"
#endif
void	get_region_map_tile(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void	increment_tile(struct s_pt2 *tile_id, int tile_row);
#ifdef __cplusplus
extern "C"
#endif
void	cuda_check_kernel_errors(void);
#ifdef __cplusplus
#endif
#endif
