/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgros <tgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:57:30 by talemari          #+#    #+#             */
/*   Updated: 2017/05/02 15:46:24 by tgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/inc/libft.h"
#include "objparser.h"

int		ft_isnumeric(char c)
{
	if (ft_isdigit(c) || c == '-')
		return (1);
	else
		return (0);
}
