/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 10:41:42 by tgros             #+#    #+#             */
/*   Updated: 2017/06/03 12:42:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.cuh"

/*
** Warpper function to call on the desired filter.
*/

__device__
t_color		filter(t_color orig, t_filter filter)
{
	t_color		new_col;

	if (filter == F_NONE)
		return (orig);
	if (filter == F_BW)
		new_col = b_w_filter(orig);
	else if (filter == F_SEPIA)
		new_col = sepia_filter(orig);
	else if (filter == F_DEUTAN)
		new_col = deutan_filter(orig);
	else if (filter == F_LEFT_RED)
		new_col = left_red_filter(orig);
	else if (filter == F_RIGHT_CYAN)
		new_col = right_cyan_filter(orig);
	return (new_col);
}
