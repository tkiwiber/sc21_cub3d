/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:49:17 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 19:56:15 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	    	ft_init_mlx()
{
	t_mlx	mlx;

	mlx.ptr = NULL;
	return (mlx);
}

t_tex		    ft_init_tex()
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

t_win	    	ft_init_win()
{
	t_win	win;

	win.ptr = NULL;
	win.x = 0;
	win.y = 0;
	return (win);
}

t_map	    	ft_init_map()
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

t_err	    	ft_init_err()
{
	t_err	err;

	err.m = 0;
	err.n = 0;
	err.p = 0;
	return (err);
}

t_img	    	ft_init_img()
{
	t_img	img;
	t_spr	*spr;
	t_stk	*stk;

	img.ptr = NULL;
	img.adr = NULL;
	return (img);
}

t_pp			ft_init_pp()
{
	t_pp	pp;

	pp.x = 0;
	pp.y = 0;
	pp.size = 1;
	return (pp);
}

t_pd			ft_init_pd()
{
	t_pd	pd;

	pd.x = 1;
	pd.y = 0;
	pd.a = 0;
	return (pd);
}

t_ray			ft_init_ray()
{
	t_ray	ray;

	ray.x = 0;
	ray.y = -1;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	return (ray);
}

t_hit			ft_init_hit()
{
	t_hit	hit;

	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	return (hit);
}

t_key			ft_init_key()
{
	t_key 	key;

	key.step_left = 0;
	key.step_right = 0;
	key.step_forward = 0;
	key.step_back = 0;
	key.turn_left = 0;
	key.turn_right = 0;
	return (key);
}

t_spr			*ft_init_spr()
{
	t_spr 	*spr;

	spr = NULL;
	return (spr);
}

t_stk			*ft_init_stk()
{
	t_stk 	*stk;

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
	g->pl = ft_init_pp();
	g->dir = ft_init_pd();
	g->key = ft_init_key();
	g->spr = ft_init_spr();
	g->stk = ft_init_stk();
}
