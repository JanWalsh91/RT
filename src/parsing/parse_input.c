/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/05/27 15:09:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Loops over token-value pairs and prepares the scene.
*/

char		*parse_input(t_parse_tools *t)
{
	char	*ret;

	t->input_head = t->input;
	while (t->input)
	{
		if ((ret = t->parse[t->input->token](t)))
			return (ret);
			// printf("token: %d, value: %s\n", t->input->token, t->input->value);
		t->input = t->input->next;
	}
	if (t->in_scene || t->in_object)
		return ("Brackets error");
	return (NULL);
}
