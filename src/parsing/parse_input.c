/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 12:25:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/20 13:45:46 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

char		*parse_input(t_parse_tools *t)
{
	char	*ret;

	t->input_head = t->input;
	while (t->input)
	{
		if ((ret = t->parse[t->input->token](t)))
			return (ret);
		t->input = t->input->next;
	}
	if (t->in_scene || t->in_object)
		// rt_file_error_exit(NULL, "Brackets error.");
		return ("Brackets error");
	return (NULL);
}
