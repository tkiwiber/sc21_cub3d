/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:41:34 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 10:40:32 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycast(t_all *g)
{
	double	ang;
	double	dis;

	ang = ((double)g->ray.i - (g->win.x / 2)) * 33 / (g->win.x / 2);
	ang = ang * M_PI / 180;
	g->ray.x = g->pld.x * cos(ang) - g->pld.y * sin(ang);
	g->ray.y = g->pld.y * cos(ang) + g->pld.x * sin(ang);
	dis = hypot(g->ray.x, g->ray.y);
	g->ray.x /= dis;
	g->ray.y /= dis;
}

void	ft_direction(t_all *g)
{	
	if (g->ray.x >= 0)
		g->ray.v = 1;
	else
		g->ray.v = 0;
	if (g->ray.y >= 0)
		g->ray.w = 1;
	else
		g->ray.w = 0;
}

void	ft_vertical_wall(t_all *g)
{
	double	x;
	double	y;

	x = floor(g->plp.x) + g->ray.v;
	y = g->plp.y + (x - g->plp.x) * (g->ray.y / g->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < g->map.y )
	{
		if (g->map.arr[(int)floor(y)][(int)(x - 1 + g->ray.v)] == '1')
		{
			g->hit.x = x;
			g->hit.y = y;
			g->hit.d = hypot(x - g->plp.x, y - g->plp.y);
			return ;
		}
		x += (2 * g->ray.v - 1);
		y += (2 * g->ray.v - 1) * g->ray.y / g->ray.x;
	}
	g->hit.x = g->plp.x;
	g->hit.y = g->plp.y;
	g->hit.d = 99999999;
}

void	ft_horizontal_wall(t_all *g)
{
	double	y;
	double	x;

	y = floor(g->plp.y) + g->ray.w;
	x = g->plp.x + (y - g->plp.y) * (g->ray.x / g->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < g->map.x)
	{
		if (g->map.arr[(int)(y - 1 + g->ray.w)][(int)floor(x)] == '1')
		{
			if (g->hit.d > hypot(x - g->plp.x, y - g->plp.y))
			{
				g->hit.x = x;
				g->hit.y = y;
				g->hit.d = hypot(x - g->plp.x, y - g->plp.y);
			}
			return ;
		}
		y += (2 * g->ray.w - 1);
		x += (2 * g->ray.w - 1) * g->ray.x / g->ray.y;
	}
}

void			ft_stock(t_all *g)
{
	g->stk[g->ray.i].x = g->ray.x;
	g->stk[g->ray.i].y = g->ray.y;
	g->stk[g->ray.i].d = g->hit.d;
}