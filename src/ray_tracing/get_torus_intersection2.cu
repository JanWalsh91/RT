/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_torus_intersection2.cu                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 16:38:40 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/04 14:15:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOT A LA NORME

__device__
bool		get_torus_intersection(t_raytracing_tools *r, t_ray *ray,
				int index)
{
t_quartic	qua;
{
  double tmpA = dir2[0] * dir2[0] + dir2[1] * dir2[1] + dir2[2] * dir2[2];
  double tmpB =
    2.0 * (dir2[0] * pos2[0] + dir2[1] * pos2[1] + dir2[2] * pos2[2]);
  double tmpC =
    pos2[0] * pos2[0] + pos2[1] * pos2[1] + pos2[2] * pos2[2] +
    majorR * majorR - minusR * minusR;

  double tmp = 4.0 * majorR * majorR;
  double tmpD = tmp * (dir2[0] * dir2[0] + dir2[2] * dir2[2]);
  double tmpE = tmp * 2 * (dir2[0] * pos2[0] + dir2[2] * pos2[2]);
  double tmpF = tmp * (pos2[0] * pos2[0] + pos2[2] * pos2[2]);

  a = tmpA * tmpA;
  b = 2.0 * tmpA * tmpB;
  c = 2.0 * tmpA * tmpC + tmpB * tmpB - tmpD;
  d = 2.0 * tmpB * tmpC - tmpE;
  e = tmpC * tmpC - tmpF;

}