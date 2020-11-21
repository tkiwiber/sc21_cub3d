/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:07:21 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 19:55:56 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bmp_data(t_all *g, int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];

	i = g->win.x * (g->win.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < g->win.x)
		{
			buffer[0] = (unsigned char)(g->img.adr[i] % 256);
			buffer[1] = (unsigned char)(g->img.adr[i] / 256 % 256);
			buffer[2] = (unsigned char)(g->img.adr[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * g->win.x;
	}
}

void	ft_bmp_info(t_all *g, int fd)
{
	int				n;
	unsigned char	bmp_header[40];

	n = 0;
	while (n < 40)
		bmp_header[n++] = (unsigned char)(0);
	bmp_header[0] = (unsigned char)(40);
	n = g->win.x;
	bmp_header[4] = (unsigned char)(n % 256);
	bmp_header[5] = (unsigned char)(n / 256 % 256);
	bmp_header[6] = (unsigned char)(n / 256 / 256 % 256);
	bmp_header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = g->win.y;
	bmp_header[8] = (unsigned char)(n % 256);
	bmp_header[9] = (unsigned char)(n / 256 % 256);
	bmp_header[10] = (unsigned char)(n / 256 / 256 % 256);
	bmp_header[11] = (unsigned char)(n / 256 / 256 / 256);
	bmp_header[12] = (unsigned char)(1);
	bmp_header[14] = (unsigned char)(32);
	write(fd, bmp_header, 40);
}

void	ft_bmp_header(t_all *g, int fd)
{
	int				pos;
	unsigned char	bmp_header[14];

	pos = 0;
	while (pos < 14)
		bmp_header[pos++] = (unsigned char)(0);
	bmp_header[0] = (unsigned char)(66);
	bmp_header[1] = (unsigned char)(77);
	pos = g->win.x * g->win.y * 4 + 54;
	bmp_header[2] = (unsigned char)(pos % 256);
	bmp_header[3] = (unsigned char)(pos / 256 % 256);
	bmp_header[4] = (unsigned char)(pos / 256 / 256 % 256);
	bmp_header[5] = (unsigned char)(pos / 256 / 256 / 256);
	bmp_header[10] = (unsigned char)(54);
	write(fd, bmp_header, 14);
}

int		ft_bmp_save(t_all *g)
{
	int		fd;

	ft_create_frame(g);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (ft_strerror(-1));
	ft_bmp_header(g, fd);
	ft_bmp_info(g, fd);
	ft_bmp_data(g, fd);
	close(fd);
	free(g->img.ptr);
	free(g->img.adr);
	ft_close(g, 0);
	return (1);
}
