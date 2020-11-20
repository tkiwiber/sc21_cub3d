/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:47:03 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 17:47:42 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_key			ft_init_key(void)
{
	t_key	key;

	key.step_left = 0;
	key.step_right = 0;
	key.step_forward = 0;
	key.step_back = 0;
	key.turn_left = 0;
	key.turn_right = 0;
	return (key);
}

t_spr			*ft_init_spr(void)
{
	t_spr	*spr;

	spr = NULL;
	return (spr);
}

t_stk			*ft_init_stk(void)
{
	t_stk	*stk;

	stk = NULL;
	return (stk);
}

void			ft_init_all(t_all *g)
{
	g->mlx = ft_init_mlx();
	g->img = ft_init_img();
	g->win = ft_init_win();
	g->err = ft_init_err();
	g->map = ft_init_map();
	g->tex = ft_init_tex();
	g->ray = ft_init_ray();
	g->hit = ft_init_hit();
	g->plp = ft_init_plp();
	g->pld = ft_init_pld();
	g->key = ft_init_key();
	g->spr = ft_init_spr();
	g->stk = ft_init_stk();
}
