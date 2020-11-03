/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:22:47 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/02 12:19:40 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    circle(t_all *g, int cx, int cy, int radius)
{
	int error = -radius;
	int x = radius;
	int y = 0;
// The following while loop may altered to 'while (x > y)' for a
// performance benefit, as long as a call to 'plot4points' follows
// the body of the loop. This allows for the elimination of the
// '(x != y') test in 'plot8points', providing a further benefit.
//
// For the sake of clarity, this is not shown here.
	while (x >= y)
	{
		plot8points(g, cx, cy, x, y);
		error += y;
		++y;
		error += y;
// The following test may be implemented in assembly language in
// most machines by testing the carry flag after adding 'y' to
// the value of 'error' in the previous step, since 'error'
// nominally has a negative value.
		if (error >= 0)
			{
			--x;
			error -= x;
			error -= x;
			}
	}
}

void	plot8points(t_all *g, int cx, int cy, int x, int y)
{
plot4points(g, cx, cy, x, y);
if (x != y) plot4points (g, cx, cy, y, x);
}
// The '(x != 0 && y != 0)' test in the last line of this function
// may be omitted for a performance benefit if the radius of the
// circle is known to be non-zero.

void	plot4points(t_all *g, int cx, int cy, int x, int y)
{
ft_mlx_pixel_put(g, cx + x, cy + y, WHITE);
if (x != 0) ft_mlx_pixel_put(g, cx - x, cy + y, WHITE);
if (y != 0) ft_mlx_pixel_put(g, cx + x, cy - y, WHITE);
if (x != 0 && y != 0) ft_mlx_pixel_put(g, cx - x, cy - y, WHITE);
}


void	plot_line(t_all *g, int x0, int y0, int x1, int y1)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */
	for (;;){  /* loop */
		ft_mlx_pixel_put(g, x0, y0, WHITE);
		if (x0 == x1 && y0 == y1) break;
			e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void	plot_rect(t_all *g, int x0, int y0, int x1, int y1)
{
	plot_line(g, x0, y0, x1, y0);
	plot_line(g, x1, y0, x1, y1);
	plot_line(g, x1, y1, x0, y1);
	plot_line(g, x0, y1, x0, y0);
}

void	plot_rect_r(t_all *g, int x0, int y0, int x1, int y1)
{
	int y = y1 - y0;
	
	//(y >= 0) ? (y *= 1) : (y *= -1); 
	while (y > 0)
	{
		int x = x1 - x0;
		while (x > 0)
		{
			ft_mlx_pixel_put(g, x0 + x, y0 + y, WHITE);
			x -= 1;
		}
		y -= 1;
	}
}

void	raster_circle (t_all *g, int x0, int y0, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	ft_mlx_pixel_put(g, x0, y0 + radius, RED);
	ft_mlx_pixel_put(g, x0, y0 - radius, RED);
	ft_mlx_pixel_put(g, x0 + radius, y0, RED);
	ft_mlx_pixel_put(g, x0 - radius, y0, RED);

	while (x < y)
	{
	// ddF_x == 2 * x + 1;
	// ddF_y == -2 * y;
	// f == x*x + y*y - radius*radius + 2*x - y + 1;
	if (f >= 0) 
		{
		y--;
		ddF_y += 2;
		f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;    
	
	ft_mlx_pixel_put(g, x0 + x, y0 + y, RED);
	ft_mlx_pixel_put(g, x0 - x, y0 + y, RED);
	ft_mlx_pixel_put(g, x0 + x, y0 - y, RED);
	ft_mlx_pixel_put(g, x0 - x, y0 - y, RED);
	
	ft_mlx_pixel_put(g, x0 + y, y0 + x, RED);
	ft_mlx_pixel_put(g, x0 - y, y0 + x, RED);
	ft_mlx_pixel_put(g, x0 + y, y0 - x, RED);
	ft_mlx_pixel_put(g, x0 - y, y0 - x, RED);

  }
}