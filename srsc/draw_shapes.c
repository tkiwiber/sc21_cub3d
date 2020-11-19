/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:22:47 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 13:57:56 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_plot_line(t_all *g, double x0, double y0, double x1, double y1, \
int color)
{
	double dx =  fabs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	double dy = -fabs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err;
	int e2;
	
	dx =  fabs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	dy = -fabs (y1 - y0), sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (!(x0 == x1 && y0 == y1))
	{
		ft_mlx_pixel_put(g, (int)x0, (int)y0, color);
		e2 = 2 * err;
		if (e2 >= dy) 
		{
			err += dy; 
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	ft_plot_rect(t_all *g, int x0, int y0, int x1, int y1, int color)
{
	ft_plot_line(g, x0, y0, x1, y0, color);
	ft_plot_line(g, x1, y0, x1, y1, color);
	ft_plot_line(g, x1, y1, x0, y1, color);
	ft_plot_line(g, x0, y1, x0, y0, color);
}

void	ft_plot_rect_r(t_all *g, int x0, int y0, int x1, int y1, int color)
{
	int y = y1 - y0;
	
	while (y > 0)
	{
		int x = x1 - x0;
		while (x > 0)
		{
			ft_mlx_pixel_put(g, x0 + x, y0 + y, color);
			x -= 1;
		}
		y -= 1;
	}
}

void	ft_mlx_pixel_put(t_all *g, int x, int y, int color)
{
	unsigned int	*data;

	data = g->img.adr + (x * (g->img.bpp / 8) + y * g->img.sl);
    *(int *)data = color;
}
