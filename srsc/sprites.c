/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:31:13 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 16:30:03 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_sprite_take_pixel(t_all *gl, int i, unsigned int col)
{
	int	t;
	int	r;
	int	g;
	int	b;
	int size;

	size = 256;
	if (col >= NONE)
		return (gl->img.adr[i]);
	else if (col < pow(size, 3))
		return (col);
	t = col / (int)(pow(size, 3));
	r = (col / (int)(pow(size, 2)) % size) * (1 - (double)t / size);
	g = (col / size % size) * (1 - (double)t / size);
	b = (col % size) * (1 - (double)t / size);
	r += (gl->img.adr[i] / (int)(pow(size, 2)) % size) * ((double)t / size);
	g += (gl->img.adr[i] / size % size) * ((double)t / size);
	b += (gl->img.adr[i] % size) * ((double)t / size);
	return (r * pow(size, 2) + g * size + b);
}

void			ft_sprite_draw(t_all *g, int loc, double dist)
{
	unsigned int	col;
	double			size;
	int				index;
	int				i;
	int				j;

	i = 0;
	j = 0;
	size = g->win.y / dist / 2;
	loc = loc - size / 2;
	while (i < size)
	{
		while ((loc + i >= 0 && loc + i < g->win.x) &&
				(j < size && g->stk[loc + i].d > dist))
		{
			col = 64 * floor(64 * (double)j / size) + (double)i / size * 64;
			col = g->tex.sp[col];
			index = loc + i + (g->win.y / 2 + j) * g->win.x;
			if (index < g->win.x * g->win.y)
				g->img.adr[index] = ft_sprite_take_pixel(g, index, col);
			j++;
		}
		i++;
		j = 0;
	}
}

void			ft_sprite_loc(t_all *g, double dirx, double diry, double dist)
{
	double	angle;

	dirx = (dirx - g->pl.x) / dist;
	diry = (diry - g->pl.y) / dist;
	if (diry <= 0)
		angle = acos(dirx) * 180 / M_PI;
	else
		angle = 360 - acos(dirx) * 180 / M_PI;
	angle = g->dir.a - angle + 33;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	ft_sprite_draw(g, angle * g->win.x / 66, dist);
}

void			ft_sprite_order(t_all *g)
{
	t_spr	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < g->map.spr - 1)
	{
		j = i + 1;
		while (j < g->map.spr)
		{
			if (g->spr[i].d < g->spr[j].d)
			{
				tmp = g->spr[i];
				g->spr[i] = g->spr[j];
				g->spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void			ft_sprite(t_all *g)
{
	int		i;
	double	dist;

	dist = hypot(g->dir.x, g->dir.y);
	if (g->dir.y <= 0)
		g->dir.a = acos(g->dir.x / dist) * 180 / M_PI;
	else
		g->dir.a = 360 - acos(g->dir.x / dist) * 180 / M_PI;
	i = 0;
	while (i < g->map.spr)
	{
		g->spr[i].d = hypot(g->spr[i].x - g->pl.x, g->spr[i].y - g->pl.y);
		i++;
	}
	ft_sprite_order(g);
	i = 0;
	while (i < g->map.spr)
	{
		ft_sprite_loc(g, g->spr[i].x, g->spr[i].y, g->spr[i].d);
		i++;
	}
	free(g->stk);
}
