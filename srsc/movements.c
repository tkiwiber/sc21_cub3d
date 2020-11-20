/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:53:10 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 13:14:33 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_turn(t_all *g, double c)
{
	double	dist;
	
	g->pld.x =  g->pld.x * cos(c * TURN) - g->pld.y * sin(c * TURN);
	g->pld.y =  g->pld.x * sin(c * TURN) + g->pld.y * cos(c * TURN);
	dist = hypot(g->pld.x, g->pld.y);
	g->pld.x /= dist;
	g->pld.y /= dist;	
	g->pld.a = acos(g->pld.x) * (g->pld.y < 0 ? 1 : -1);
}

void	ft_sideways(t_all *g, double c)
{
	g->plp.x -= c * g->pld.y * (STEP);
	if (g->map.arr[(int)floor(g->plp.y)][(int)floor(g->plp.x)] == '1')
		g->plp.x += c * g->pld.y * (STEP);
	g->plp.y += c * g->pld.x * (STEP);
	if (g->map.arr[(int)floor(g->plp.y)][(int)floor(g->plp.x)] == '1')
		g->plp.y -= c * g->pld.x * (STEP);
}

void	ft_step(t_all *g, double c)
{
	g->plp.x += c * g->pld.x * (STEP);
	if (g->map.arr[(int)floor(g->plp.y)][(int)floor(g->plp.x )] == '1')
		g->plp.x -= c * g->pld.x * (STEP);
	g->plp.y += c * g->pld.y * (STEP);
	if (g->map.arr[(int)floor(g->plp.y)][(int)floor(g->plp.x)] == '1')
		g->plp.y -= c * g->pld.y * (STEP);
}

void    ft_init_movement(t_all *g)
{
    ft_turn(g, 1);
	ft_step(g, 1);
	ft_turn(g, -1);
	ft_step(g, -1);
	ft_sprite_list(g);
}