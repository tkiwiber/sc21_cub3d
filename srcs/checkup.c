/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:00:13 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/21 16:06:32 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_option(char *arg, char *mask)
{
	int	i;

	i = 0;
	while (arg[i] == mask[i])
	{
		if (arg[i] == '\0' && mask[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_extension(char *arg, char *mask)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == mask[2] && arg[i - 2] == mask[1])
		&& (arg[i - 3] == mask[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_check_map(t_all *g)
{
	int		i;
	int		j;

	i = -1;
	while (++i < g->map.y)
	{
		j = -1;
		while (++j < g->map.x)
		{
			if ((g->map.arr[i][j] != '1' && g->map.arr[i][j] != ' ' && i == 0)
			|| (g->map.arr[i][j] != '1' && g->map.arr[i][j] != ' ' && j == 0)
			|| (g->map.arr[i][j] != '1' && g->map.arr[i][j] != ' '
			&& j == g->map.x - 1) || (g->map.arr[i][j] != '1'
			&& g->map.arr[i][j] != ' ' && i == g->map.y - 1))
				return (-1);
			else if (g->map.arr[i][j] != '1' && g->map.arr[i][j] != ' ')
				if (g->map.arr[i - 1][j] == ' ' || g->map.arr[i + 1][j] == ' '
				|| g->map.arr[i][j - 1] == ' ' || g->map.arr[i][j + 1] == ' '
				|| g->map.arr[i - 1][j - 1] == ' ' || g->map.arr[i + 1][j + 1] \
				== ' ' || g->map.arr[i - 1][j + 1] == ' '
				|| g->map.arr[i + 1][j - 1] == ' ')
					return (-1);
		}
	}
	return (1);
}

int		ft_check_load(t_all *g)
{
	if (g->win.x <= 0 || g->win.y <= 0)
		return (ft_strerror(-14));
	else if (g->tex.no == NULL)
		return (ft_strerror(-151));
	else if (g->tex.so == NULL)
		return (ft_strerror(-152));
	else if (g->tex.ea == NULL)
		return (ft_strerror(-153));
	else if (g->tex.we == NULL)
		return (ft_strerror(-154));
	else if (g->tex.sp == NULL)
		return (ft_strerror(-155));
	else if (g->tex.ce == NONE)
		return (ft_strerror(-161));
	else if (g->tex.fl == NONE)
		return (ft_strerror(-162));
	else if (g->err.p == 0)
		return (ft_strerror(-17));
	else if (g->err.p > 1)
		return (ft_strerror(-18));
	return (1);
}

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
