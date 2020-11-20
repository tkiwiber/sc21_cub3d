/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:25:06 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 10:28:57 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < s->map.y)
	{
		j = 0;
		while (j < s->map.x)
		{
			if (s->map.arr[i][j] != '1' && i == 0)
				return (-1);
			else if (s->map.arr[i][j] != '1' && i == s->map.y - 1)
				return (-1);
			else if (s->map.arr[i][j] != '1' && j == 0)
				return (-1);
			else if (s->map.arr[i][j] != '1' && j == s->map.x - 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.no == NULL || s->tex.so == NULL || s->tex.ea == NULL)
			|| (s->tex.we == NULL || s->tex.sp == NULL))
		return (ft_strerror(-15));
	else if (s->tex.ce == NONE || s->tex.fl == NONE)
		return (ft_strerror(-16));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(s) == -1)
		return (ft_strerror(-19));
	return (1);
}

int				ft_map_lenght(t_all *g, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W')
			count++;
		else if (line[i] == 'E')
			count++;
		i++;
	}
	if (g->map.x != 0 && g->map.x != count)
		return (-1);
	return (count);
}

char			*ft_slab(t_all *s, char *line, int *i)
{
	char	*slab;
	int		j;

	if (!(slab = malloc(sizeof(char) * (ft_map_lenght(s, line) + 1))))
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			slab[j++] = line[*i];
		else if (line[*i] == '2')
		{
			slab[j++] = line[*i];
			s->map.spr++;
		}
		else if (line[*i] != ' ')
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int				ft_fill_map(t_all *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	g->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (g->map.y + 2))))
		return (-11);
	j = -1;
	while (++j < g->map.y)
		tmp[j] = g->map.arr[j];
	if ((tmp[g->map.y] = ft_slab(g, line, i)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[g->map.y + 1] = NULL;
	if (g->map.y > 0)
		free(g->map.arr);
	g->map.arr = tmp;
	g->map.y++;
	if ((g->map.x = ft_map_lenght(g, line)) == -1)
		return (-13);
	return (0);
}