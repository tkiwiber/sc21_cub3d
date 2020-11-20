/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:48:10 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 17:09:29 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_atoi(char *line, int *i)
{
	int		num;

	num = 0;
	ft_skip_whitespaces(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

int				ft_skip_whitespaces(char *line, int *pos)
{
	while ((line[*pos] == ' ' || line[*pos] == '\t' || line[*pos] == '\n')
	|| (line[*pos] == '\r' || line[*pos] == '\v' || line[*pos] == '\f'))
		(*pos)++;
	return (1);
}

int				ft_strerror2(int err)
{
	(err == -13) ? write(2, "ERROR : BAD map (must be rectangle)\n", 30) : 0;
	(err == -14) ? write(2, "ERROR : NO resolution\n", 32) : 0;
	(err == -151) ? write(2, "ERROR : BAD NO texture\n", 23) : 0;
	(err == -152) ? write(2, "ERROR : BAD SO texture\n", 23) : 0;
	(err == -153) ? write(2, "ERROR : BAD EA texture\n", 23) : 0;
	(err == -154) ? write(2, "ERROR : BAD WE texture\n", 23) : 0;
	(err == -155) ? write(2, "ERROR : BAD S texture\n", 22) : 0;
	(err == -161) ? write(2, "ERROR : NONE floor color\n", 26) : 0;
	(err == -162) ? write(2, "ERROR : NONE ceiling color\n", 26) : 0;
	(err == -17) ? write(2, "ERROR : NONE init position\n", 29) : 0;
	(err == -18) ? write(2, "ERROR : NOT single init positions\n", 36) : 0;
	(err == -19) ? write(2, "ERROR : WRONG map (not closed)\n", 38) : 0;
	return (err);
}

int				ft_strerror(int err)
{
	(err == -1) ? write(2, "ERROR : CANNOT open file (FD)\n", 30) : 0;
	(err == -2) ? write(2, "ERROR : CANNOT parse file (GNL)\n", 32) : 0;
	(err == -3) ? write(2, "ERROR : DOUBLE resolution define\n", 33) : 0;
	(err == -4) ? write(2, "ERROR : BAD resolution\n", 22) : 0;
	(err == -5) ? write(2, "ERROR : DOUBLE floor/ceiling define\n", 36) : 0;
	(err == -6) ? write(2, "ERROR : WRONG floor or ceiling line\n", 36) : 0;
	(err == -7) ? write(2, "ERROR : DOUBLE texture load\n", 28) : 0;
	(err == -8) ? write(2, "ERROR : FAIL open texture\n", 26) : 0;
	(err == -9) ? write(2, "ERROR : CANNOT load texture\n", 28) : 0;
	(err == -10) ? write(2, "ERROR : WRONG line in file\n", 27) : 0;
	(err == -11) ? write(2, "ERROR : FAIL malloc (map table)\n", 32) : 0;
	(err == -12) ? write(2, "ERROR : WRONG map\n", 18) : 0;
	err = ft_strerror2(err);
	return (-1);
}

int				ft_close(t_all *g, int win)
{
	int		i;

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