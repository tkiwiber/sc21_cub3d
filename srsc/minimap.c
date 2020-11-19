/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:31:21 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 14:33:06 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_minimap(t_all *g)
{
	int osx;
	int osy;
	int i, j;

	osx = g->map.sizex;
	osy = g->map.sizey;
	j = 0;
	while (j < g->map.y)
	{
		i = 0;
		while (i < g->map.x)
		{
			if ((g->map.arr[j][i]) == '1')
				ft_plot_rect_r(g, osx + i * osx, osy + j * osy, \
				i * osx + 2 * osx, j * osy + 2 * osy, WHITE);
			i++;
		}
		j ++;
	}
	ft_plot_rect(g, osx, osx, (g->map.x - 1) * osx + \
	2 * osx, (g->map.y - 1) * osy + 2 * osy, RED);
	ft_plot_rect(g, g->pl.x * osx + osx, g->pl.y * osy + osy, g->pl.x * \
	osx + osx + g->pl.size, g->pl.y * osy + osy + g->pl.size, BLACK);
}
