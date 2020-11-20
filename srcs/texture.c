/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:23:53 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/20 17:11:10 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_xpm_file(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == 'm' && arg[i - 2] == 'p')
		&& (arg[i - 3] == 'x' && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_load_xpm_file(t_all *g, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];
	int		size;

	size = 64;
	if (ft_check_xpm_file(file) == 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(g->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != size || tab[1] != size)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[3], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int		ft_get_textures(t_all *g, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	ft_skip_whitespaces(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = ft_load_xpm_file(g, adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}
