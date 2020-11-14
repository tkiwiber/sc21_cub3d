/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:29:58 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/14 18:35:00 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_size(t_all *g)
{
	double	correc;
	double	fisheye;

	fisheye = fabs((double)g->ray.i / (g->win.x / 2) - 1);
	fisheye *= 28 * M_PI / 180;
	correc = (double)g->hit.d * cos(fisheye);
	return (round(g->win.y / correc));
}

void			ft_column(t_all *g, int size)
{
	unsigned int	color;
	int				start;
	int				count;

	start = g->win.x * (g->win.y - size) / 2;
	if (size > g->win.y)
		count = (size - g->win.y) / 2;
	else
		count = 0;
	color = RED;
	while (g->ray.i < g->win.x * g->win.y)
	{
		if (g->ray.i >= start && count < size)
		{
			color = RED;
			count++;
		}
		else if (count == size)
			color = GREEN;
		
		g->img.adr[g->ray.i] = color;
		g->ray.i += g->win.x;
	}
	g->ray.i -= g->win.x * g->win.y;
}

int	ft_resize(t_all *g, int win)
{

	//printf("RE-seized\n");
	return(1);
}

void	ft_mlx_pixel_put(t_all *g, int x, int y, int color)
{
	char	*data;

	data = g->img.adr + (x * (g->img.bpp / 8) + y * g->img.sl);
    *(int *)data = color;
}

void	ft_ver(t_all *g)
{
	double	x;
	double	y;

	x = floor(g->pl.x) + g->ray.v;
	y = g->pl.y + (x - g->pl.x) * (g->ray.y / g->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < g->map.y)
	{
		if (g->map.arr[(int)floor(y)][(int)(x - 1 + g->ray.v)] == '1')
		{
			g->hit.x = x;
			g->hit.y = y;
			g->hit.d = hypot(x - g->pl.x, y - g->pl.y);
			return ;
		}
		x += (2 * g->ray.v - 1);
		y += (2 * g->ray.v - 1) * g->ray.y / g->ray.x;
	}
	g->hit.x = g->pl.x;
	g->hit.y = g->pl.y;
	g->hit.d = 1000000000;
}

void	ft_hor(t_all *g)
{
	double	y;
	double	x;

	y = floor(g->pl.y) + g->ray.w;
	x = g->pl.x + (y - g->pl.y) * (g->ray.x / g->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < g->map.x)
	{
		if (g->map.arr[(int)(y - 1 + g->ray.w)][(int)floor(x)] == '1')
		{
			if (g->hit.d > hypot(x - g->pl.x, y - g->pl.y))
			{
				g->hit.x = x;
				g->hit.y = y;
				g->hit.d = hypot(x - g->pl.x, y - g->pl.y);
			}
			return ;
		}
		y += (2 * g->ray.w - 1);
		x += (2 * g->ray.w - 1) * g->ray.x / g->ray.y;
	}
}

void	ft_ray(t_all *g)
{
	t_ray	ray;
	double	ray_start, ray_end;
	double	fov = M_PI / 3.;
	t_pd	dir;
	int     lx, i, x, y, n;
	double	ang_size, height;

	n = 0;
	ang_size = tan(fov);
	x = 1;
	y = g->win.y / 2;
	ray_start = g->dir.a - fov / 2.;
	ray_end = g->dir.a + fov / 2;
	
	while (ray_start <= ray_end)
	{
		i = 0;
		ray.x = g->pl.x;
		ray.y = g->pl.y;

		dir.x = cos(ray_start);
		dir.y = sin(ray_start);

		while (g->map.arr[(int)(ray.y / g->map.sizey)][(int)(ray.x / g->map.sizex)] != '1')
		{
				
			ray.x += dir.x;
			ray.y += dir.y;
			i ++;
			
			ft_mlx_pixel_put(g, ray.x, ray.y, BLUE);
		}

		//height =  fabs(i / (2 * cos (g->dir.a) * ang_size));
		if (i * (cos(ray_start)) > 0)
			height = (g->win.y * g->map.sizey) / (i * (cos(ray_start)));

		printf("HEIGHT=%0.3f", height);

		plot_line(g, x, y, x, (int)(y - height / 3));
		plot_line(g, x, y, x, (int)(y + height / 3));
		printf("angle:%0.3f steps: %d height: %.3f LINE [%d ; %d]\n", ray_start * 180 / M_PI, i, height, (int)(y - height / 2), (int)(y + height / 2));
		x++;

		n++;
		ray_start += fov / g->win.x;
	}
	
	printf("%d COLUMNS WERE DRAWN\n", n);
	
}

void	ft_dir(t_all *g)
{
	t_ray	ray;
	int c = 1;
	t_ray dir;

	ray.x = g->pl.x;
	ray.y = g->pl.y;
	//g->dir.a = acos(g->dir.x) * (g->dir.y < 0 ? 1 : -1);
	
	if (g->ray.x >= 0)
		g->ray.v = 1;
	else
		g->ray.v = 0;
	if (g->ray.y >= 0)
		g->ray.w = 1;
	else
		g->ray.w = 0;
	
	while (g->map.arr[(int)(ray.y / g->map.sizey)][(int)(ray.x / g->map.sizex)] != '1')
	{
		ray.x += cos(g->dir.a);
		ray.y += sin(g->dir.a);
		ft_mlx_pixel_put(g, ray.x, ray.y, GREEN);
	}
	
}

void	ft_turn(t_all *g, double c)
{
	double	dist;
	
	g->dir.x =  g->dir.x * cos(c * TURN) - g->dir.y * sin(c * TURN);
	g->dir.y =  g->dir.x * sin(c * TURN) + g->dir.y * cos(c * TURN);
	dist = hypot(g->dir.x, g->dir.y);
	g->dir.x /= dist;
	g->dir.y /= dist;
	
	g->dir.a = acos(g->dir.x) * (g->dir.y < 0 ? 1 : -1);
	printf("Player.a = %.3f\n", g->dir.a * 180 / M_PI);
}

void	ft_sideways(t_all *g, double c)
{
	g->pl.x += c * STEP * g->dir.y;
	if (g->map.arr[(int)floor(g->pl.y / g->map.sizey)][(int)floor(g->pl.x / g->map.sizex)] == '1')
		g->pl.x -= c * STEP * g->dir.y;

	g->pl.y += c * STEP * g->dir.x;
	if (g->map.arr[(int)floor(g->pl.y / g->map.sizey)][(int)floor(g->pl.x / g->map.sizex)] == '1')
		g->pl.y -= c * STEP * g->dir.x;
	
}

void	ft_forward(t_all *g, double c)
{
	g->pl.x += c * (STEP) * g->dir.x;
	if (g->map.arr[(int)floor(g->pl.y / g->map.sizey)][(int)floor(g->pl.x / g->map.sizex)] == '1')
		g->pl.x -= c * (STEP) * g->dir.x;

	g->pl.y -= c * (STEP) * g->dir.y;
	if (g->map.arr[(int)floor(g->pl.y / g->map.sizey)][(int)floor(g->pl.x / g->map.sizex)] == '1')
		g->pl.y += c * (STEP) * g->dir.y;
}

void	ft_player(t_all *g)
{
	raster_circle(g, g->pl.x, g->pl.y, g->pl.size);
	raster_circle(g, g->pl.x, g->pl.y, g->pl.size + 1);
	
}

void	ft_map(t_all *g)
{
	int osx = g->map.sizex;
	int osy = g->map.sizey;
	int i, j;

int bpp, end, sl, img_width, img_height;
t_img	text1;

	text1.ptr = mlx_xpm_file_to_image(g->mlx.ptr, "brick.xpm", &img_width, &img_height);
	text1.adr = mlx_get_data_addr(text1.ptr, &bpp, &sl, &end);

	j = 0;
	while (j < g->map.y)
	{
		i = 0;
		while (i < g->map.x)
		{
			if ((g->map.arr[j][i]) == '1')
				//mlx_put_image_to_window(g->mlx.ptr, g->win.ptr, text1.ptr, i * osx, j * osy);
			plot_rect(g, i * osx, j * osy, i * osx + osx, j * osy + osy);
			i++;
		}
		j ++;
	}

	//mlx_put_image_to_window(g->mlx.ptr, g->win.ptr, text1.ptr, 0, 0);

}

void	ft_screen(t_all *g)
{
	int i;
	
	g->img.ptr = mlx_new_image(g->mlx.ptr, g->win.x, g->win.y);
	g->img.adr = mlx_get_data_addr(g->img.ptr, &g->img.bpp, &g->img.sl, &g->img.end);

	
		ft_map(g);
		ft_player(g);
		ft_dir(g);
		ft_ray(g);
		
		//ft_ver(g);
		//ft_hor(g);
		
		//ft_column(g, ft_size(g));
	

	
}

void	ft_draw(t_all *g)
{
	int		bpp;
	int		sl;
	int		end;
	t_ray	ray;
	
	//mlx_do_sync(g->mlx.ptr);
	
	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	
	printf("BEFORE player_pos [%.3f;%.3f] dir [%.3f;%.3f]\n", g->pl.x, g->pl.y, g->dir.x, g->dir.y);

	ft_screen(g);
	mlx_do_sync(g->mlx.ptr);
	mlx_put_image_to_window(g->mlx.ptr, g->win.ptr, g->img.ptr, 0, 0);

	printf("AFTER player_pos [%.3f;%.3f] dir [%.3f;%.3f]\n", g->pl.x, g->pl.y, g->dir.x, g->dir.y);

	free(g->img.ptr);
	free(g->img.adr);
}

int		ft_close(t_all *g, int win)
{
	int	i;
	// add free to others structs later
	i = 0;
	while (i < g->map.y)
		free(g->map.arr[i++]);
	free(g->map.arr);
	if (win == 1)
		mlx_destroy_window(g->mlx.ptr, g->win.ptr);
	free(g->mlx.ptr);
	exit(0);
	return (1);
}

int		ft_key(int key, void *arg)
{
	if (key == ESC)
		ft_close(arg, 1);
	else if (key == A)
		ft_sideways(arg, -1);
	else if (key == D)
		ft_sideways(arg, 1);
	else if (key == W)
		ft_forward(arg, 1);
	else if (key == S)
		ft_forward(arg, -1);
	else if (key == LEFT)
		ft_turn(arg, 1);
	else if (key == RIGHT)
		ft_turn(arg, -1);
	ft_draw(arg);
	return (1);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	if (destsize <= 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

int		ft_fill_map(t_all *g, char *line)
{
	int		i, j;
	char	**tmp;

	j = -1;
	i = -1;

	if (!(tmp = malloc(sizeof(char *) * (g->map.y + 2))))
		return (-1); // don't forget to handle with g.err

	while (++i < g->map.y)
		tmp[i] = g->map.arr[i];
	/*{
		if (!(tmp[i] = malloc(sizeof(char) * (g->map.x) + 1)))
			return (-1); // don't forget to handle with g.err
		ft_strlcpy(tmp[i], g->map.arr[i], g->map.x + 1);
	}*/
	if (!(tmp[g->map.y] = malloc(sizeof(char) * (g->map.x) + 1)))
		return (-1); // don't forget to handle with g.err
	else
		ft_strlcpy(tmp[i], line, g->map.x + 1);

	tmp[g->map.y + 1] = NULL;
	
	if (g->map.y > 0)
		free (g->map.arr);

	g->map.arr = tmp;

	g->map.y += 1;
	return (0);
}

int		ft_start(char *f_name, int c)
{
	/* declare all the structures of objects: main (agregate all of others), ninilibx, /
	 windiws, images, errors, maps, textures, stockes, sprites, plaeyer position and player direction */

	// structers
	t_all	g;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;
	t_map	map;
	t_tex	tex;
	t_spr	*spr;
	t_stk	*stk;
	t_pp	pp;
	t_pd	pd;
	t_ray	ray;
	t_hit	hit;

int bpp, end, sl, img_width, img_height;
t_img	text1;
	// arrays with coordinates to read form files
	char	*line;
	int		fd;
	int		ret;
	int		n;

	// read from file and store in game's [g] structure 
	char	**tmp;
	int		i, j;

	// all veriables initialization 
	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	win.x = 1200;
	win.y = 800;
	img.fsh = 0;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	g.mlx = mlx;
	g.win = win;
	g.img = img;
	g.err = err;

	map.arr = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	spr = NULL;
	stk = NULL;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	map.sizex = 32;
	map.sizey = 32;
	tex.c = NONE;
	tex.f = NONE;
	g.map = map;
	g.tex = tex;
	g.spr = spr;
	g.stk = stk;
	pp.x = 0;
	pp.y = 0;
	pp.size = 2;
	pd.x = 1;
	pd.y = 0;
	pd.a = 0;
	g.pl = pp;
	g.dir = pd;
	ray.x = 0;
	ray.y = -1;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	g.ray = ray;
	g.dir = pd;
	// reading from file to form map

	n = 0;
	ret = 1;
	
	fd = open(f_name, O_RDONLY);
	
	if (fd == -1)
		return (-1); // don't forget to handle with g.err
	
	j = -1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		g.map.x = ft_strlen(line);
		ft_fill_map(&g, line);
		free (line);
	}

	close (fd);

	/*
	j = -1;
	while (++j < g.map.y)
	{
		i = -1;
		while (++i < g.map.x)
			printf("%c", *(g.map.arr[j]+i));
		printf("\n");
	}*/
	
	
	
	
	j = 0;
	while (j < g.map.y)
	{
		i = 0;
		while (i < g.map.x)
		{
			if (*(g.map.arr[j] + i) == 'W')
				{
					g.pl.x = i * g.map.sizex + g.map.sizex / 2;
					g.pl.y = j * g.map.sizey + g.map.sizey / 2;
					g.dir.a = acos(g.dir.x) * (g.dir.y < 0 ? 1 : -1);
					
				}
			i++;
		}
		j++;
	}

	// Drawing main window using mlx
	g.mlx.ptr = mlx_init();
	g.win.ptr = mlx_new_window(g.mlx.ptr, g.win.x, g.win.y, "CUB3D tkiwiber");

	mlx_string_put(g.mlx.ptr, g.win.ptr, 10, 10, WHITE, "Press anykey to start! (ESC for exit)");

/* texture 
	text1.ptr = mlx_xpm_file_to_image(g.mlx.ptr, "brick.xpm", &img_width, &img_height);
	text1.adr = mlx_get_data_addr(text1.ptr, &bpp, &sl, &end);

	mlx_put_image_to_window(g.mlx.ptr, g.win.ptr, text1.ptr, 0, 0);
*/
	//ft_draw(&g);
	mlx_hook(g.win.ptr, 2, 1L<<8, ft_key, &g);
	mlx_hook(g.win.ptr, 17, 0, ft_close, &g);
	mlx_hook(g.win.ptr, 10, 0, ft_resize, &g);

	mlx_loop(g.mlx.ptr);
	
	return (c); // dont forget to correct


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
