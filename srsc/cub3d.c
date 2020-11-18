/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:29:58 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/18 21:48:41 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_xpmfile(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == 'm' && arg[i - 2] == 'p')
		&& (arg[i - 3] == 'x' && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_load_xpm(t_all *g, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];
	int		size;
	
	size = 64;
	if (ft_check_xpmfile(file) == 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(g->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != size || tab[1] != size)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[3], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int		ft_skip_whitespaces(char *line, int *pos)
{
	while ((line[*pos] == ' ' || line[*pos] == '\t' || line[*pos] == '\n')
	|| (line[*pos] == '\r' || line[*pos] == '\v' || line[*pos] == '\f'))
		(*pos)++;
	return (1);
}

int		ft_get_textures(t_all *s, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	ft_skip_whitespaces(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = ft_load_xpm(s, adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}

int				ft_size(t_all *g)
{
	double	correc;
	double	fisheye;

	fisheye = fabs((double)g->ray.i / (g->win.x / 2) - 1);
	fisheye *= 28 * M_PI / 180;
	correc = (double)g->hit.d * cos(fisheye);
	return (round(g->win.y / correc));
}

void			ft_stock(t_all *g)
{
	g->stk[g->ray.i].x = g->ray.x;
	g->stk[g->ray.i].y = g->ray.y;
	g->stk[g->ray.i].d = g->hit.d;
}

unsigned int	ft_take_pixel(t_all *g, double pos)
{
	int	i;
	int size;

	size = 64;
	if (floor(g->hit.y) == g->hit.y)
	{
		i = size * floor(size * pos) + size * (g->hit.x - floor(g->hit.x));
		if (g->ray.w == 1)
			return (g->tex.so[i]);
		else if (g->ray.w == 0)
			return (g->tex.no[i]);
	}
	else if (floor(g->hit.x) == g->hit.x)
	{
		i = size * floor(size * pos) + size * (g->hit.y - floor(g->hit.y));
		if (g->ray.v == 1)
			return (g->tex.ea[i]);
		else if (g->ray.v == 0)
			return (g->tex.we[i]);
	}
	return (BLACK);
}

void			ft_column(t_all *g, int size)
{
	unsigned int	color;
	int				start;
	int				count;
	int				line_height;
	int				draw_start;
	int				draw_end;

	if (size != 0)
		line_height = (int)(g->win.y / size);
	else
		line_height = g->win.y;
	
	draw_start = (-size / 2 + g->win.y / 2) * 1;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (size / 2 + g->win.y / 2) * 1;
	if (draw_end >= g->win.y)
		draw_end = g->win.y - 1;
	
	//plot_line(g, g->ray.i, draw_start, g->ray.i, draw_end);
	//printf("****** ray.i=%d draw_s=%d draw_e=%d pos=%d max=%d\n", g->ray.i, draw_start, draw_end, (g->ray.i + g->win.x * draw_start), (g->win.x * g->win.y));
	//printf("%s %s\n", g->img.adr[g->ray.i * g->win.x], g->img.adr[1]);
	
	/*while (draw_start < draw_end && g->ray.i < g->win.x)
	{
		if (g->ray.v && g->ray.w)
			color = RED;
		else if (g->ray.v && !g->ray.w)
			color = GREEN;
		else if (!g->ray.v && !g->ray.w)
			color = YELLOW;
		else if (!g->ray.v && g->ray.w)
			color = BLUE;
		g->img.adr[g->win.x * draw_start + g->ray.i ] = mlx_get_color_value(g->mlx.ptr, color);
		draw_start++;
	}*/
	
	//printf("******** x=%d hit.d = %0.2f size = %d line_height = %d y0y1=[%d,%d]\n", g->ray.i , g->hit.d, size, line_height, draw_start, draw_end);

	start = g->win.x * (g->win.y - size) / 2;
	if (size > g->win.y)
		count = (size - g->win.y) / 2;
	else
		count = 0;
	color = SLATEGRAY;
	while (g->ray.i < g->win.x * g->win.y)
	{
		if (g->ray.i >= start && count < size)
		{			
			color = ft_take_pixel(g, (double)count / size);
			count++;
		}
		else if (count == size)
			color = SLATEGRAY;
		g->img.adr[g->ray.i] = mlx_get_color_value(g->mlx.ptr, color);
		g->ray.i += g->win.x;
	}
	g->ray.i -= g->win.x * g->win.y;
	
}

void	ft_mlx_pixel_put(t_all *g, int x, int y, int color)
{
	unsigned int	*data;

	data = g->img.adr + (x * (g->img.bpp / 8) + y * g->img.sl);
    *(int *)data = color;
}

void	ft_ver(t_all *g)
{
	double	x;
	double	y;

	x = floor(g->pl.x) + g->ray.v;
	y = g->pl.y + (x - g->pl.x) * (g->ray.y / g->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < g->map.y )
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
	g->hit.d = 99999999;
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
			//printf("******** hit hor = [%0.3f ; %0.3f] dist = %0.3f\n", g->hit.x, g->hit.y, g->hit.d);
			return ;
		}
		y += (2 * g->ray.w - 1);
		x += (2 * g->ray.w - 1) * g->ray.x / g->ray.y;
	}
}

void	ft_ray(t_all *g)
{
	double	ang;
	double	dis;

	ang = ((double)g->ray.i - (g->win.x / 2)) * 33 / (g->win.x / 2);
	ang = ang * M_PI / 180;
	g->ray.x = g->dir.x * cos(ang) - g->dir.y * sin(ang);
	g->ray.y = g->dir.y * cos(ang) + g->dir.x * sin(ang);
	dis = hypot(g->ray.x, g->ray.y);
	g->ray.x /= dis;
	g->ray.y /= dis;
	
	//printf("******** RAY = [%0.3f ; %0.3f]\n", g->ray.x, g->ray.y);

	/*t_ray	ray;
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
	
	printf("%d COLUMNS WERE DRAWN\n", n);*/
	
}

void	ft_dir(t_all *g)
{	
	if (g->ray.x >= 0)
		g->ray.v = 1;
	else
		g->ray.v = 0;
	if (g->ray.y >= 0)
		g->ray.w = 1;
	else
		g->ray.w = 0;
	
	/*while (g->map.arr[(int)(ray.y / g->map.sizey)][(int)(ray.x / g->map.sizex)] != '1')
	{
		ray.x += cos(g->dir.a);
		ray.y += sin(g->dir.a);
		ft_mlx_pixel_put(g, ray.x, ray.y, GREEN);
	}*/
	
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
}

void	ft_sideways(t_all *g, double c)
{
	g->pl.x -= c * g->dir.y * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x)] == '1')
		g->pl.x += c * g->dir.y * (STEP);
	g->pl.y += c * g->dir.x * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x)] == '1')
		g->pl.y -= c * g->dir.x * (STEP);
}

void	ft_forward(t_all *g, double c)
{
	g->pl.x += c * g->dir.x * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x )] == '1')
		g->pl.x -= c * g->dir.x * (STEP);
	g->pl.y += c * g->dir.y * (STEP);
	if (g->map.arr[(int)floor(g->pl.y)][(int)floor(g->pl.x)] == '1')
		g->pl.y -= c * g->dir.y * (STEP);
}

void	ft_player(t_all *g)
{
	raster_circle(g, g->pl.x, g->pl.y, g->pl.size);
	raster_circle(g, g->pl.x, g->pl.y, g->pl.size + 1);
	
}

void	ft_map(t_all *g)
{
	int osx = 1; //g->map.sizex;
	int osy = 1; //g->map.sizey;
	int i, j;

int bpp, end, sl, img_width, img_height;
t_img	text1;

	text1.ptr = mlx_xpm_file_to_image(g->mlx.ptr, "brick.xpm", &img_width, &img_height);
	text1.adr = (unsigned int *)mlx_get_data_addr(text1.ptr, &bpp, &sl, &end);

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
	g->img.adr = (unsigned int *)mlx_get_data_addr(g->img.ptr, &g->img.bpp, &g->img.sl, &g->img.end);
	g->stk = malloc(sizeof(t_stk) * g->win.x);

	while (g->ray.i < g->win.x)
	{
		ft_ray(g);
		ft_dir(g);
		ft_ver(g);
		ft_hor(g);
		ft_stock(g);
		ft_column(g, ft_size(g));

		//ft_map(g);
		//ft_player(g);
		//ft_dir(g);
		g->ray.i++;
	}
		
		
		//ft_ray(g);
		
		//ft_ver(g);
		//ft_hor(g);
		
		//ft_column(g, ft_size(g));
		//ft_map(g);
		
	
}

void	ft_draw(t_all *g)
{
	int		bpp;
	int		sl;
	int		end;
	t_ray	ray;
	t_hit	hit;
	int i;

	//mlx_do_sync(g->mlx.ptr);
	
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
	
	i = 0;
	ft_get_textures(g, &g->tex.so, "SO ./textures/bluestone.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.we, "WE ./textures/greystone.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.ea, "EA ./textures/mossy.xpm", &i);
	i = 0;
	ft_get_textures(g, &g->tex.no, "NO ./textures/purplestone.xpm", &i);

	//printf("BEFORE player_pos [%.3f;%.3f] dir [%.3f;%.3f]\n", g->pl.x, g->pl.y, g->dir.x, g->dir.y);

	ft_screen(g);
	mlx_do_sync(g->mlx.ptr);
	mlx_put_image_to_window(g->mlx.ptr, g->win.ptr, g->img.ptr, 0, 0);

	//printf("AFTER player_pos [%.3f;%.3f] dir [%.3f;%.3f]\n", g->pl.x, g->pl.y, g->dir.x, g->dir.y);

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

int		ft_init_keystates(t_key *key)
{
	key->step_left = 0;
	key->step_right = 0;
	key->step_forward = 0;
	key->step_back = 0;
	key->turn_left = 0;
	key->turn_right = 0;
	return (1);
}

int		ft_loop(t_all *g)
{
	ft_update_movement(g);
	ft_draw(g);
	return (1);
}

int		ft_update_movement(t_all *g)
{
	//printf("*** Forward button state: %d\n", g->key.step_forward);
	if (g->key.step_forward)
		ft_forward(g, 1);
	if (g->key.step_back)
		ft_forward(g, -1);
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

int		ft_key_down(int key, t_all *g)
{	
	static int n = 0;
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
	t_key	key;

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
	tex.no = NULL;
	tex.so = NULL;
	tex.ea = NULL;
	tex.we = NULL;
	tex.i = NULL;
	spr = NULL;
	stk = NULL;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	map.sizex = 32;
	map.sizey = 32;
	tex.ceiling = NONE;
	tex.floor = NONE;
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

	ft_init_keystates(&key);
	g.key = key;


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
					g.pl.x = i;
					g.pl.y = j;
					g.dir.a = acos(g.dir.x) * (g.dir.y < 0 ? 1 : -1);
				}
			i++;
		}
		j++;
	}

	// Drawing main window using mlx
	g.mlx.ptr = mlx_init();

	ft_turn(&g, 1);
	ft_forward(&g, 1);
	ft_turn(&g, -1);
	ft_forward(&g, -1);

	g.win.ptr = mlx_new_window(g.mlx.ptr, g.win.x, g.win.y, "CUB3D tkiwiber");
	ft_draw(&g);
	//mlx_string_put(g.mlx.ptr, g.win.ptr, 10, 10, WHITE, "Press anykey to start! (ESC for exit)");

/* texture 
	text1.ptr = mlx_xpm_file_to_image(g.mlx.ptr, "brick.xpm", &img_width, &img_height);
	text1.adr = mlx_get_data_addr(text1.ptr, &bpp, &sl, &end);

	mlx_put_image_to_window(g.mlx.ptr, g.win.ptr, text1.ptr, 0, 0);
*/
	mlx_loop_hook(g.mlx.ptr, ft_loop, &g);
	mlx_hook(g.win.ptr, 2, 0, ft_key_down, &g);
	mlx_hook(g.win.ptr, 3, 0, ft_key_up, &g);
	mlx_hook(g.win.ptr, 17, 0, ft_close, &g);
	
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
