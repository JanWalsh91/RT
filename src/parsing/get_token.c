/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:37:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/04/05 12:08:04 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rt.cuh"

/*
** Parses the key in the key-value combination.
** Returns the corresponding enum value.
*/

int	get_token(t_parse_tools *t, char *key)
{
	int		i;

	i = 0;
	if (!key || !*key)
		return (T_EMPTY_LINE);
	if (ft_strchr(key, '#') && (key[0] == '#'))
		return (T_HASHTAG);
	while (i < (T_COUNT - 1))
	{
		if (t->tokens[i] == NULL)
			ft_errno_exit();
		if (!ft_strcmp(t->tokens[i], key))
			break ;
		++i;
	}
	if (i < T_COUNT)
		return (i);
	else
		return (T_INVALID_TOKEN);
}
