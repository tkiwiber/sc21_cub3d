/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:16:01 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/10/27 22:12:51 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_strclr(char *s)
{
	if (s)
		while (*s)
			*s++ = '\0';
}

int				free_str(char **s1, char **s2)
{
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (-1);
}

char			*fill_line(char *residue, char **line, int *err)
{
	char		*p_n;

	p_n = NULL;
	if (residue)
	{
		if ((p_n = ft_strchr(residue, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(residue, err);
			p_n++;
			ft_strcpy(residue, p_n);
		}
		else
		{
			*line = ft_strdup(residue, err);
			ft_strclr(residue);
		}
	}
	else
		*line = ft_strdup("", err);
	return (p_n);
}

int				trunc_line(char **line, char **residue, char **p_n, char **buf)
{
	char		*tmp;
	int			errh;

	errh = 1;
	if ((*p_n = ft_strchr(*buf, '\n')))
	{
		**p_n = '\0';
		(*p_n)++;
		free(*residue);
		if (!(*residue = ft_strdup(*p_n, &errh)))
			return (-1);
	}
	tmp = *line;
	if (!(*line = ft_strjoin(*line, *buf, &errh)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*residue;
	char		*p_n;
	int			bwr;
	int			err;

	err = 1;
	if (read(fd, NULL, 0) < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	bwr = 1;
	p_n = fill_line(residue, line, &err);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (free_str(&buf, line));
	while (!p_n && (bwr = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bwr] = '\0';
		err = trunc_line(line, &residue, &p_n, &buf);
	}
	free(buf);
	if (bwr < 0 || err == -1)
		return (free_str(&buf, &residue));
	if (bwr == 0 && residue != 0)
		free_str(&residue, &residue);
	return ((p_n || bwr) ? 1 : 0);
}
