/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:29:58 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/21 16:53:25 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_start(char *file, int save)
{
	t_all	g;

	ft_init_all(&g);
	if (!(g.mlx.ptr = mlx_init()))
	{
		perror("MLX failed");
		return (1);
	}
	if (ft_read_file(&g, file) == -1)
		return (ft_close(&g, -1));
	if (save)
		return (ft_bmp_save(&g));
	ft_init_movement(&g);
	if (!(g.win.ptr = mlx_new_window(g.mlx.ptr, g.win.x, g.win.y, \
	"CUB3D tkiwiber")))
	{
		perror("WIN failed");
		return (ft_close(&g, -1));
	}
	mlx_loop_hook(g.mlx.ptr, ft_update_frame, &g);
	mlx_hook(g.win.ptr, 2, 0, ft_key_down, &g);
	mlx_hook(g.win.ptr, 3, 0, ft_key_up, &g);
	mlx_hook(g.win.ptr, 17, 0, ft_close, &g);
	mlx_loop(g.mlx.ptr);
	return (1);
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
