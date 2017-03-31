/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:41:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/23 11:45:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Puts the error message on the error output and exits the program.
*/

#include "libft.h"

void	ft_error_exit(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit(0);
}
