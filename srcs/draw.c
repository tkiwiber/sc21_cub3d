/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:19:31 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/21 09:46:20 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_take_pixel(t_all *g, double pos)
{
	int	i;
	int size;

	size = 64;
	if (floor(g->hit.y) == g->hit.y)
	{
		i = size * floor(size * pos) + size * (g->hit.x - floor(g->hit.x));
		if (g->ray.w == 1)
			return (g->tex.so[i]);
		else if (g->ray.w == 0)
			return (g->tex.no[i]);
	}
	else if (floor(g->hit.x) == g->hit.x)
	{
		i = size * floor(size * pos) + size * (g->hit.y - floor(g->hit.y));
		if (g->ray.v == 1)
			return (g->tex.ea[i]);
		else if (g->ray.v == 0)
			return (g->tex.we[i]);
	}
	return (BLACK);
}

int				ft_modify_height(t_all *g)
{
	double	mod;
	double	k;

	k = fabs((double)g->ray.i / (g->win.x / 2) - 1);
	k *= 33 * M_PI / 180;
	mod = (double)g->hit.d * cos(k);
	return (round(g->win.y / mod));
}

void			ft_draw(t_all *g, int size)
{
	unsigned int	color;
	int				start;
	int				count;

	start = g->win.x * (g->win.y - size) / 2;
	if (size > g->win.y)
		count = (size - g->win.y) / 2;
	else
		count = 0;
	color = g->tex.fl;
	while (g->ray.i < g->win.x * g->win.y)
	{
		if (g->ray.i >= start && count < size)
		{
			color = ft_take_pixel(g, (double)count / size);
			count++;
		}
		else if (count == size)
			color = g->tex.ce;
		g->img.adr[g->ray.i] = mlx_get_color_value(g->mlx.ptr, color);
		g->ray.i += g->win.x;
	}
	g->ray.i -= g->win.x * g->win.y;
}
