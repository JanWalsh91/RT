/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/06/08 14:11:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.cuh"
#include "../inc/gui.h"
#include <time.h>

int	main(int ac, char **av)
{
	t_gtk_tools			g;
	t_parse_tools		t;
	t_raytracing_tools	r;

	srand(time(NULL));
	if (ac > 2)
		ft_error_exit(USAGE);
	g.ac = ac;
	g.av = av;
	g.win = NULL;
	g.drawing_area = NULL;
	g.cr = NULL;
	g.updating_gui = 0;
	g.t = &t;
	g.r = &r;
	g.pixbuf = NULL;
	g.r->settings.tile_size = DEFAULT_TILE_SIZE;
	g.r->settings.photon_search_radius = 5;
	g.filename = (ac >= 2) ? ft_strdup(av[1]) : NULL;
	main_gtk(&g);
	return (0);
}
