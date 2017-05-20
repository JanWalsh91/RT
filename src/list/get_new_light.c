/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:40:04 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/20 15:42:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Creates a new light.
*/

static void	set_light_non_values(t_light *new_light);

t_light		*get_new_light(t_parse_tools *t)
{
	t_light		*new_light;
	static int	i = 1;

	if (!(new_light = (t_light *)ft_memalloc(sizeof(t_light))))
		ft_errno_exit();
	set_light_non_values(new_light);
	if (!t->input->value || !*t->input->value)
	{
		new_light->name = ft_strjoin(t->tokens[t->input->token], " ");
		new_light->name = ft_strjoinfree(new_light->name, ft_itoa(i), 'b');
	}
	else
		new_light->name = ft_strdup(t->input->value);
	++i;
	return (new_light);
}

static void	set_light_non_values(t_light *new_light)
{
	ft_bzero(new_light, sizeof(t_light));
	new_light->next = NULL;
	new_light->pos = v_new(NAN, NAN, NAN);
	new_light->dir = v_new(NAN, NAN, NAN);
	new_light->look_at = v_new(NAN, NAN, NAN);
	new_light->col = v_new(NAN, NAN, NAN);
	new_light->intensity = NAN;
	new_light->name = NULL;
}
