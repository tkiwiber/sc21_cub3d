/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:11:13 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 16:32:54 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_down(int key, t_all *g)
{	
	if (key == ESC)
		ft_close(g, 1);
	else if (key == A)
		g->key.step_left = 1;
	else if (key == D)
		g->key.step_right = 1;
	else if (key == W)
		g->key.step_forward = 1;
	else if (key == S)
		g->key.step_back = 1;
	else if (key == LEFT)
		g->key.turn_right = 1;
	else if (key == RIGHT)
		g->key.turn_left = 1;
	return (1);
}

int		ft_key_up(int key, t_all *g)
{	
	if (key == ESC)
		ft_close(g, 1);
	else if (key == A)
		g->key.step_left = 0;
	else if (key == D)
		g->key.step_right = 0;
	else if (key == W)
		g->key.step_forward = 0;
	else if (key == S)
		g->key.step_back = 0;
	else if (key == LEFT)
		g->key.turn_right = 0;
	else if (key == RIGHT)
		g->key.turn_left = 0;
	return (1);
}

int		ft_update_movement(t_all *g)
{
	if (g->key.step_forward)
		ft_step(g, 1);
	if (g->key.step_back)
		ft_step(g, -1);
	if (g->key.step_left)
		ft_sideways(g, -1);
	if (g->key.step_right)
		ft_sideways(g, 1);
	if (g->key.turn_right)
		ft_turn(g, -1);
	if (g->key.turn_left)
		ft_turn(g, 1);
	return (1);
}

