/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:16:01 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/11/19 22:03:07 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*error(char *stock)
{
	free(stock);
	return (NULL);
}

int		newline_check(char *stock, int read_size)
{
	int	i;

	i = 0;
	if (stock == NULL)
		return (0);
	if (read_size == 0)
		return (1);
	while (stock[i] != '\0')
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*buf_join(char *stock, char *buf)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (stock != NULL && stock[i] != '\0')
		i++;
	while (buf[j] != '\0')
		j++;
	if (!(new = malloc(sizeof(char) * (i + j + 1))))
		return (error(stock));
	i = 0;
	j = 0;
	while (stock != NULL && stock[i] != '\0')
		new[i++] = stock[j++];
	j = 0;
	while (buf[j] != '\0')
		new[i++] = buf[j++];
	new[i] = '\0';
	if (stock != NULL)
		free(stock);
	return (new);
}

char	*stock_trim(char *stock)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	while (stock[i++] != '\0')
		j++;
	if (!(trimmed = malloc(sizeof(char) * j + 1)))
		return (error(stock));
	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\0')
		i--;
	i++;
	while (stock[i] != '\0')
		trimmed[j++] = stock[i++];
	trimmed[j] = '\0';
	free(stock);
	return (trimmed);
}

char	*get_line(char *stock)
{
	int		i;
	char	*line;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (!(line = malloc(sizeof(char) * i + 1)))
		return (error(stock));
	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int		get_next_line(int fd, char **line)
{
	int			read_size;
	char		buf[4096];
	static char	*stock = NULL;

	if (line == NULL || fd < 0)
		return (-3);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(stock, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-3);
		buf[read_size] = '\0';
		if ((stock = buf_join(stock, buf)) == NULL)
			return (-3);
	}
	if ((*line = get_line(stock)) == NULL)
		return (-3);
	if (read_size == 0)
		free(stock);
	if (read_size == 0)
		return (0);
	if ((stock = stock_trim(stock)) == NULL)
		return (-3);
	return (1);
}
