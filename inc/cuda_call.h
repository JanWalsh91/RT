/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_call.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:35:59 by tgros             #+#    #+#             */
/*   Updated: 2017/05/28 16:37:34 by jwalsh           ###   ########.fr       */
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
void	render(struct s_raytracing_tools *r, struct s_tile tile);
#ifdef __cplusplus
extern "C"
#endif
void	lens_flare_wrapper(struct s_raytracing_tools *r);
#ifdef __cplusplus
extern "C"
#endif
int		cuda_free(struct s_raytracing_tools *r, int all);
#ifdef __cplusplus
extern "C"
#endif
void	update_photon_map(struct s_raytracing_tools *r);

#endif
