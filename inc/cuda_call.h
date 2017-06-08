/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_call.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:35:59 by tgros             #+#    #+#             */
/*   Updated: 2017/06/08 13:46:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDA_CALL_H
#define CUDA_CALL_H

#include "rt.cuh"

#ifdef __cplusplus
extern "C"
#endif
bool	cuda_malloc(struct s_raytracing_tools *r);
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
void	radiance_estimation_pass(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void	photon_mapping_pass(struct s_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	get_flares(struct s_raytracing_tools *r);
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
extern "C"
#endif
void	get_cartoon_effect(struct s_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	perpare_memory(t_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	free_map_and_list(t_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	copy_1(t_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
void	copy_2(t_raytracing_tools *r);
#ifdef __cplusplus
#endif
#endif
