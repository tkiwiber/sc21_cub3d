/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:25:06 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/21 16:55:13 by tkiwiber         ###   ########.fr       */
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
		if (line[i] == '0' || line[i] == '1' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == ' ')
			count++;
		i++;
	}
	if (g->map.x != 0 && count < 1)
		return (-1);
	return (count);
}

char			*ft_map_line(t_all *s, char *l, int *i)
{
	char	*m_line;
	int		j;

	if (!(m_line = malloc(sizeof(char) * (ft_map_lenght(s, l) + 1))))
		return (NULL);
	j = 0;
	while (l[*i] != '\0')
	{
		if ((l[*i] == '0' || l[*i] == ' ' || l[*i] == '1' || l[*i] == 'N')
		|| (l[*i] == 'E' || l[*i] == 'S' || l[*i] == 'W'))
			m_line[j++] = l[*i];
		else if (l[*i] == '2')
		{
			m_line[j++] = l[*i];
			s->map.spr++;
		}
		else if (l[*i] != ' ')
		{
			free(m_line);
			return (NULL);
		}
		(*i)++;
	}
	m_line[j] = '\0';
	return (m_line);
}

int				ft_map_final(t_all *g)
{
	int		i;
	int		j;

	if (ft_check_map(g) == -1)
	{	
		g->err.m = 1;
		perror("ERROR : BAD map (not closed)");
		return (0);
	}
	i = -1;
	while (++i < g->map.y)
	{
		j = -1;
		while (++j < g->map.x)
		{
			if (g->map.arr[i][j] == ' ')
				g->map.arr[i][j] = '1';
		}
	}
	return (1);
}

void			ft_map_transform(t_all *g)
{
	char	**tmp;
	char	*line;
	int		i;
	int		j;
	int		flag;

	if (!(tmp = malloc(sizeof(char *) * (g->map.y))))
		return ;
	g->map.arr = tmp;
	j = -1;
	free(line);
	while (++j < g->map.y)
	{
		if (!(line = malloc(sizeof(char) * (g->map.x + 1))))
			return ;
		i = -1;
		g->map.arr[j] = line;
		flag = 0;
		while (++i < g->map.x)
			if (!(flag += g->map.tmp[j][i] == '\0' ? 1 : 0))
				g->map.arr[j][i] = g->map.tmp[j][i];
			else
				g->map.arr[j][i] = ' ';
		g->map.arr[j][i] = '\0';
	}
}

int				ft_map_fill(t_all *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	if (line[0] != '\0')
		g->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (g->map.y + 2))))
		return (-11);
	*i = 0;
	j = -1;
	while (++j < g->map.y)
		tmp[j] = g->map.tmp[j];
	if ((tmp[g->map.y] = ft_map_line(g, line, i)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[g->map.y + 1] = NULL;
	if (g->map.y > 0)
		free(g->map.tmp);
	g->map.tmp = tmp;
	g->map.y++;
	if (g->map.x < ft_map_lenght(g, line))
		g->map.x = ft_map_lenght(g, line);
	return (0);
}
