/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:49:17 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 17:46:48 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx			ft_init_mlx(void)
{
	t_mlx	mlx;

	mlx.ptr = NULL;
	return (mlx);
}

t_tex			ft_init_tex(void)
{
	t_tex	tex;

	tex.no = NULL;
	tex.so = NULL;
	tex.ea = NULL;
	tex.we = NULL;
	tex.sp = NULL;
	tex.ce = NONE;
	tex.fl = NONE;
	return (tex);
}

t_win			ft_init_win(void)
{
	t_win	win;

	win.ptr = NULL;
	win.x = 0;
	win.y = 0;
	return (win);
}

t_map			ft_init_map(void)
{
	t_map	map;

	map.arr = NULL;
	map.x = 0;
	map.y = 0;
	map.sizex = 2;
	map.sizey = 2;
	map.spr = 0;
	return (map);
}

t_err			ft_init_err(void)
{
	t_err	err;

	err.m = 0;
	err.n = 0;
	err.p = 0;
	return (err);
}
