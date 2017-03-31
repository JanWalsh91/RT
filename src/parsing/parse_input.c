/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/31 16:50:45 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.cuh"

void		parse_input(t_parse_tools *t)
{
	t->input_head = t->input;
	while (t->input)
	{
		t->parse[t->input->token](t);
		t->input = t->input->next;
	}
	if (t->in_scene || t->in_object)
		rt_file_error_exit(NULL, "Brackets error.");
}
