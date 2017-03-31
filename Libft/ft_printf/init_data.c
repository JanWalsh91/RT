/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:13:38 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/16 13:13:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Sets default values in the t_data structure.
*/

void	init_data(t_data *d, char *format)
{
	d->f = format;
	d->s = NULL;
	d->byte_count = 0;
	d->null_char = 0;
}
