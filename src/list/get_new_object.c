/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/05 11:08:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Creates a new object.
*/

t_object	*get_new_object(t_parse_tools *t)
{
	t_object	*new_object;
	static int	i = 1;

	if (!(new_object = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_errno_exit();
	set_non_values(new_object);
	if (!t->input->value || !*t->input->value)
	{
		new_object->name = ft_strjoin(t->tokens[t->input->token], " ");
		new_object->name = ft_strjoinfree(new_object->name, ft_itoa(i), 'b');
	}
	else
		new_object->name = ft_strdup(t->input->value);
	new_object->type = t->input->token;
	++i;
	return (new_object);
}

void		set_non_values(t_object *new_object)
{
	ft_bzero(new_object, sizeof(t_object));
	new_object->name = NULL;
	new_object->next = NULL;
	new_object->obj = NULL;
	new_object->pos = v_new(NAN, NAN, NAN);
	new_object->dir = v_new(NAN, NAN, NAN);
	new_object->look_at = v_new(NAN, NAN, NAN);
	new_object->col = v_new(NAN, NAN, NAN);
	new_object->texture = NULL;
	new_object->texture_ratio.x = 1;
	new_object->texture_ratio.y = 1;
	new_object->texture_translate.x = 0;
	new_object->texture_translate.y = 0;
	new_object->rad = NAN;
	new_object->height = NAN;
	new_object->ior = NAN;
	new_object->reflection = NAN;
	new_object->specular_exp = NAN;
	new_object->ks = NAN;
	new_object->kd = NAN;
	new_object->transparency = NAN;
}
