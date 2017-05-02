/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talemari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 11:57:30 by talemari          #+#    #+#             */
/*   Updated: 2017/04/29 13:20:36 by talemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/inc/libft.h"
#include "../includes/objparser.h"

int		ft_isnumeric(char c)
{
	if (ft_isdigit(c) || c == '-')
		return (1);
	else
		return (0);
}
