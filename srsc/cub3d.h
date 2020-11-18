/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:30:16 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/18 21:40:54 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlxopengl/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define LIGHTGRAY 0x00D3D3D3
# define CYAN 0x0000FFFF
# define GRAY 0x00808080
# define SLATEGRAY 0x00708090

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define STEP 0.1
# define TURN 0.05

#define BUFFER_SIZE 1024

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				fsh;
	int				bpp;
	int				sl;
	int				end;
}				t_img;

typedef struct	s_err
{
	int				n;
	int				m;
	int				p;
}				t_err;

typedef struct	s_map
{
	char			**arr;
	int				x;
	int				y;
	int				spr;
	int				sizex;
	int				sizey;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*no;
	unsigned int	*so;
	unsigned int	*ea;
	unsigned int	*we;
	unsigned int	*i;
	unsigned int	ceiling;
	unsigned int	floor;
}				t_tex;

typedef struct	s_pp
{
	double			x;
	double			y;
	int				size;
}				t_pp;

typedef struct	s_pd
{
	double			x;
	double			y;
	double			a;
}				t_pd;

typedef struct	s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
	double			a;
}				t_ray;

typedef struct	s_hit
{
	double			x;
	double			y;
	double			d;
}				t_hit;

typedef struct	s_spr
{
	double			x;
	double			y;
	double			d;
}				t_spr;

typedef struct	s_key
{
	int			step_left;
	int			step_right;
	int			step_forward;
	int			step_back;
	int			turn_left;
	int			turn_right;
}				t_key;

typedef struct	s_stk
{
	double			x;
	double			y;
	double			d;
}				t_stk;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_err			err;
	t_map			map;
	t_tex			tex;
	t_pp			pl;
	t_pd			dir;
	t_ray			ray;
	t_hit			hit;
	t_spr			*spr;
	t_stk			*stk;
	t_key			key;
}				t_all;


size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t destsize);

int				get_next_line(int fd, char **line);
int				free_str(char **s1, char **s2);
char			*ft_strdup(const char *str, int *err);
char			*ft_strjoin(char *s1, char *s2, int *err);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strchr(const char *s, int c);
char			*fill_line(char *root, char **line, int *err);
void			ft_strclr(char *g);
int				ft_trunc_line(char **line, char **residue, char **p_n, char **buf);
int				ft_skipwhitespaces(char *line, int *pos);

int				ft_check_extension(char *arg, char *save);
int				ft_check_option(char *arg, char *ext);

int				ft_fill_map(t_all *g, char *line);

//int				ft_key(int key, void *arg); stable version
int				ft_key_up(int key, t_all *g);
int				ft_key_down(int key, t_all *g);
int				ft_close(t_all *g, int win);
int				ft_loop(t_all *g);

void			ft_draw(t_all *g);
void			ft_screen(t_all *g);
void			ft_map(t_all *g);
void			ft_player(t_all *g);
void			ft_ray(t_all *g);

void			ft_sideways(t_all *g, double c);
void			ft_forward(t_all *g, double c);
void			ft_turn(t_all *s, double c);
void			ft_mlx_pixel_put(t_all *data, int x, int y, int color);

void			ft_ver(t_all *g);
void			ft_hor(t_all *g);
int				ft_size(t_all *g);
void			ft_column(t_all *g, int size);

int				ft_get_textures(t_all *s, unsigned int **adr, char *line, int *i);
unsigned int	ft_take_pixel(t_all *g, double pos);

int				ft_load_xpm(t_all *g, unsigned int **adr, char *file);
int				ft_check_xpmfile(char *arg);



void    circle(t_all *g, int cx, int cy, int radius);
void	plot_line(t_all *g, int x0, int y0, int x1, int y1);
void	plot8points(t_all *g, int cx, int cy, int x, int y);
void	plot4points(t_all *g, int cx, int cy, int x, int y);
void	plot_rect(t_all *g, int x0, int y0, int x1, int y1);
void	plot_rect_r(t_all *g, int x0, int y0, int x1, int y1);
void	raster_circle (t_all *g, int x0, int y0, int radius);



#endif
