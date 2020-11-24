/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:58:27 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/24 21:45:59 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_set_resolution(t_all *g, char *line, int *i)
{
	if (g->win.x != 0 || g->win.y != 0)
		return (-3);
	(*i)++;
	g->win.x = ft_atoi(line, i);
	g->win.y = ft_atoi(line, i);
	if (g->win.x > 1280)
		g->win.x = 1280;
	if (g->win.y > 800)
		g->win.y = 800;
	ft_skip_whitespaces(line, i);
	if (g->win.x <= 0 || g->win.y <= 0 || line[*i] != '\0')
		return (-4);
	return (0);
}

int				ft_set_colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = ft_atoi(line, i);
	(*i)++;
	g = ft_atoi(line, i);
	(*i)++;
	b = ft_atoi(line, i);
	ft_skip_whitespaces(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

void			ft_set_position(t_all *g)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < g->map.y)
	{
		while (++j < g->map.x)
		{
			c = g->map.arr[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				g->plp.y = (double)i + 0.5;
				g->plp.x = (double)j + 0.5;
				g->pld.x = (c == 'E' || c == 'W') ? 1 : 0;
				g->pld.x *= (c == 'W') ? -1 : 1;
				g->pld.y = (c == 'S' || c == 'N') ? 1 : 0;
				g->pld.y *= (c == 'N') ? -1 : 1;
				g->err.p++;
			}
		}
		j = -1;
	}
}

int				ft_parse_line(t_all *g, char *l)
{
	int		i;

	i = 0;
	ft_skip_whitespaces(l, &i);
	if ((l[i] == '1' || g->err.m == 1) && l[i] != '\0')
		g->err.n = ft_map_fill(g, l, &i);
	else if (l[i] == 'R' && l[i + 1] == ' ')
		g->err.n = ft_set_resolution(g, l, &i);
	else if (l[i] == 'N' && l[i + 1] == 'O' && l[i + 2] == ' ')
		g->err.n = ft_get_textures(g, &g->tex.no, l, &i);
	else if (l[i] == 'S' && l[i + 1] == 'O' && l[i + 2] == ' ')
		g->err.n = ft_get_textures(g, &g->tex.so, l, &i);
	else if (l[i] == 'W' && l[i + 1] == 'E' && l[i + 2] == ' ')
		g->err.n = ft_get_textures(g, &g->tex.we, l, &i);
	else if (l[i] == 'E' && l[i + 1] == 'A' && l[i + 2] == ' ')
		g->err.n = ft_get_textures(g, &g->tex.ea, l, &i);
	else if (l[i] == 'S' && l[i + 1] == ' ')
		g->err.n = ft_get_textures(g, &g->tex.sp, l, &i);
	else if (l[i] == 'F' && l[i + 1] == ' ')
		g->err.n = ft_set_colors(&g->tex.fl, l, &i);
	else if (l[i] == 'C' && l[i + 1] == ' ')
		g->err.n = ft_set_colors(&g->tex.ce, l, &i);
	if (ft_skip_whitespaces(l, &i) && g->err.n == 0 && l[i] != '\0')
		return (ft_strerror(-10));
	return (g->err.n < 0 ? ft_strerror(g->err.n) : 0);
}

int				ft_read_file(t_all *g, char *file)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_strerror(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_parse_line(g, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));
	ft_map_transform(g);
	if (!(ft_map_final(g)))
		return (-1);
	ft_set_position(g);
	g->spr = NULL;
	ft_sprite_list(g);
	return (ft_check_load(g));
}
