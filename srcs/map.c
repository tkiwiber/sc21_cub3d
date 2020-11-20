/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:25:06 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 17:10:45 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char			*ft_map_line(t_all *s, char *line, int *i)
{
	char	*m_line;
	int		j;

	if (!(m_line = malloc(sizeof(char) * (ft_map_lenght(s, line) + 1))))
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			m_line[j++] = line[*i];
		else if (line[*i] == '2')
		{
			m_line[j++] = line[*i];
			s->map.spr++;
		}
		else if (line[*i] != ' ')
		{
			free(m_line);
			return (NULL);
		}
		(*i)++;
	}
	m_line[j] = '\0';
	return (m_line);
}

int				ft_sprite_list(t_all *g)
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

int				ft_map_fill(t_all *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	g->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (g->map.y + 2))))
		return (-11);
	j = -1;
	while (++j < g->map.y)
		tmp[j] = g->map.arr[j];
	if ((tmp[g->map.y] = ft_map_line(g, line, i)) == NULL)
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
