/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:45:55 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 17:47:29 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img			ft_init_img(void)
{
	t_img	img;

	img.ptr = NULL;
	img.adr = NULL;
	return (img);
}

t_plp			ft_init_plp(void)
{
	t_plp	plp;

	plp.x = 0;
	plp.y = 0;
	plp.size = 1;
	return (plp);
}

t_pld			ft_init_pld(void)
{
	t_pld	pld;

	pld.x = 1;
	pld.y = 0;
	pld.a = 0;
	return (pld);
}

t_ray			ft_init_ray(void)
{
	t_ray	ray;

	ray.x = 0;
	ray.y = -1;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	return (ray);
}

t_hit			ft_init_hit(void)
{
	t_hit	hit;

	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	return (hit);
}
