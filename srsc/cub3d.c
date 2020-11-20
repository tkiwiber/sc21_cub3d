/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:29:58 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 10:33:35 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	uploadtex(t_all *g)
{
	int		i;

	i = 0;
	ft_get_textures(g, &g->tex.so, "SO ./textures/bluestone.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.we, "WE ./textures/greystone.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.ea, "EA ./textures/mossy.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.no, "NO ./textures/purplestone.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.sp,  "SS ./textures/fox.xpm", &i);
}*/

int		ft_sprite_list(t_all *g)
{
	int		i;
	int		j;
	int		k;

	if (g->spr != NULL)
		free(g->spr);
	if (!(g->spr = malloc(sizeof(t_spr) * g->map.spr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < g->map.y)
	{
		k = 0;
		while (k < g->map.x)
		{
			if (g->map.arr[j][k] == '2')
			{
				g->spr[i].y = (double)j + 0.5;
				g->spr[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}

int		ft_start(char *file, int save)
{
	t_all	g;

	ft_init_all(&g);
	g.mlx.ptr = mlx_init();	
	if (ft_read_file(&g, file) == -1)
		return (ft_close(&g, 0));

	ft_init_movement(&g);
	ft_sprite_list(&g);
	
	g.win.ptr = mlx_new_window(g.mlx.ptr, g.win.x, g.win.y, "CUB3D tkiwiber");

	mlx_loop_hook(g.mlx.ptr, ft_update_frame, &g);
	mlx_hook(g.win.ptr, 2, 0, ft_key_down, &g);
	mlx_hook(g.win.ptr, 3, 0, ft_key_up, &g);
	mlx_hook(g.win.ptr, 17, 0, ft_close, &g);

	mlx_loop(g.mlx.ptr);

	return (save); // dont forget to correct
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_check_extension(av[1], "cub") && \
	ft_check_option(av[2], "--save"))
		ft_start(av[1], 1);
	else if (ac == 2 && ft_check_extension(av[1], "cub"))
		ft_start(av[1], 0);
	else
		write(2, "Error: check arguments\n", 23);
	return (0);
}
