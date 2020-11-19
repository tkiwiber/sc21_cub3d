/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:23:52 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 15:22:34 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_create_frame(t_all *g)
{
	int i;
	
	g->img.ptr = mlx_new_image(g->mlx.ptr, g->win.x, g->win.y);
	g->img.adr = (unsigned int *)mlx_get_data_addr(g->img.ptr, \
	&g->img.bpp, &g->img.sl, &g->img.end);
	g->stk = malloc(sizeof(t_stk) * g->win.x);

	while (g->ray.i < g->win.x)
	{
		ft_raycast(g);
		ft_direction(g);
		ft_vertical_wall(g);
		ft_horizontal_wall(g);
		ft_stock(g);
		ft_draw(g, ft_modify_height(g));
		ft_minimap(g);
		g->ray.i++;
	}
	ft_sprite(g);
}

void	ft_put_frame(t_all *g)
{
	t_ray	ray;
	t_hit	hit;
	
	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	g->ray = ray;
	g->hit = hit;
	ft_create_frame(g);
	mlx_do_sync(g->mlx.ptr);
	mlx_put_image_to_window(g->mlx.ptr, g->win.ptr, g->img.ptr, 0, 0);
	free(g->img.ptr);
	free(g->img.adr);
}

int		ft_update_frame(t_all *g)
{
	ft_update_movement(g);
	ft_put_frame(g);
	return (1);
}