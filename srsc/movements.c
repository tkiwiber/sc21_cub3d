/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:53:10 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 14:17:24 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_turn(t_all *g, double c)
{
	double	dist;
	
	g->dir.x =  g->dir.x * cos(c * TURN) - g->dir.y * sin(c * TURN);
	g->dir.y =  g->dir.x * sin(c * TURN) + g->dir.y * cos(c * TURN);
	dist = hypot(g->dir.x, g->dir.y);
	g->dir.x /= dist;
	g->dir.y /= dist;	
	g->dir.a = acos(g->dir.x) * (g->dir.y < 0 ? 1 : -1);
}

void	ft_sideways(t_all *g, double c)
{
	g->pl.x -= c * g->dir.y * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x)] == '1')
		g->pl.x += c * g->dir.y * (STEP);
	g->pl.y += c * g->dir.x * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x)] == '1')
		g->pl.y -= c * g->dir.x * (STEP);
}

void	ft_step(t_all *g, double c)
{
	g->pl.x += c * g->dir.x * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x )] == '1')
		g->pl.x -= c * g->dir.x * (STEP);
	g->pl.y += c * g->dir.y * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x)] == '1')
		g->pl.y -= c * g->dir.y * (STEP);
}

void    ft_init_movement(t_all *g)
{
    ft_turn(g, 1);
	ft_step(g, 1);
	ft_turn(g, -1);
	ft_step(g, -1);
}