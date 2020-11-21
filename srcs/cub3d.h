/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:30:16 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/21 17:00:15 by tkiwiber         ###   ########.fr       */
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

# define BUFFER_SIZE 1024

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
	char			**tmp;
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
	unsigned int	*sp;
	unsigned int	ce;
	unsigned int	fl;
}				t_tex;

typedef struct	s_plp
{
	double			x;
	double			y;
	int				size;
}				t_plp;

typedef struct	s_pld
{
	double			x;
	double			y;
	double			a;
}				t_pld;

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
	int				step_left;
	int				step_right;
	int				step_forward;
	int				step_back;
	int				turn_left;
	int				turn_right;
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
	t_plp			plp;
	t_pld			pld;
	t_ray			ray;
	t_hit			hit;
	t_spr			*spr;
	t_stk			*stk;
	t_key			key;
}				t_all;

size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str, int *err);
char			*ft_strjoin(char *s1, char *s2, int *err);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strchr(const char *s, int c);

char			*fill_line(char *root, char **line, int *err);
int				ft_trunc_line(char **line, char **residue, char **p_n, \
				char **buf);
void			ft_strclr(char *g);
int				get_next_line(int fd, char **line);
int				free_str(char **s1, char **s2);

t_mlx			ft_init_mlx();
t_tex			ft_init_tex();
t_win			ft_init_win();
t_map			ft_init_map();
t_err			ft_init_err();
t_img			ft_init_img();
t_plp			ft_init_plp();
t_pld			ft_init_pld();
t_ray			ft_init_ray();
t_hit			ft_init_hit();
t_key			ft_init_key();
t_spr			*ft_init_spr();
t_stk			*ft_init_stk();
void			ft_init_all(t_all *g);

int				ft_read_file(t_all *g, char *file);
int				ft_parse_line(t_all *s, char *l);
int				ft_set_resolution(t_all *g, char *line, int *i);
int				ft_set_colors(unsigned int *color, char *line, int *i);
void			ft_set_position(t_all *g);

int				ft_map_fill(t_all *g, char *line, int *i);
void			ft_map_transform(t_all *g);
int				ft_map_lenght(t_all *g, char *line);
char			*ft_map_line(t_all *g, char *line, int *i);
int				ft_map_final(t_all *g);

int				ft_check_load(t_all *g);
int				ft_check_map(t_all *g);
int				ft_check_extension(char *arg, char *mask);
int				ft_check_option(char *arg, char *mask);

int				ft_atoi(char *line, int *i);
int				ft_skip_whitespaces(char *line, int *pos);
int				ft_strerror(int err);
int				ft_close(t_all *g, int win);

int				ft_bmp_save(t_all *g);
void			ft_bmp_header(t_all *g, int fd);
void			ft_bmp_info(t_all *g, int fd);
void			ft_bmp_data(t_all *g, int fd);

int				ft_key_up(int key, t_all *g);
int				ft_key_down(int key, t_all *g);
int				ft_update_movement(t_all *g);

int				ft_create_frame(t_all *g);
int				ft_update_frame(t_all *g);
void			ft_put_frame(t_all *g);

void			ft_step(t_all *g, double c);
void			ft_turn(t_all *g, double c);
void			ft_sideways(t_all *g, double c);
void			ft_init_movement(t_all *g);

void			ft_raycast(t_all *g);
void			ft_direction(t_all *g);
void			ft_vertical_wall(t_all *g);
void			ft_horizontal_wall(t_all *g);
void			ft_stock(t_all *g);

unsigned int	ft_take_pixel(t_all *g, double pos);
int				ft_modify_height(t_all *g);
void			ft_draw(t_all *g, int size);

int				ft_check_xpm_file(char *arg);
int				ft_load_xpm_file(t_all *g, unsigned int **adr, char *file);
int				ft_get_textures(t_all *g, unsigned int **adr, char *line,\
				int *i);

unsigned int	ft_sprite_take_pixel(t_all *gl, int index, unsigned int col);
void			ft_sprite_draw(t_all *g, int loc, double dist);
void			ft_sprite_loc(t_all *g, double dirx, double diry, double dist);
void			ft_sprite_order(t_all *g);
void			ft_sprite(t_all *g);
int				ft_sprite_list(t_all *g);

#endif
