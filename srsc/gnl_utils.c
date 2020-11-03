/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiwiber <alex_orlov@goodiez.app>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:16:46 by tkiwiber          #+#    #+#             */
/*   Updated: 2020/10/27 20:50:12 by tkiwiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i] != 0)
			i++;
	return (i);
}

char		*ft_strdup(const char *str, int *err)
{
	char	*new;
	int		i;

	i = 0;
	new = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
	{
		*err = -1;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char		*ft_strjoin(char *s1, char *s2, int *err)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s1l;
	size_t	s2l;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (s1l + s2l + 1))))
	{
		*err = -1;
		return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < (s1l + s2l))
		if (i < s1l)
			str[i] = s1[i];
		else
			str[i] = s2[j++];
	str[i] = '\0';
	return (str);
}

char		*ft_strchr(const char *s, int c)
{
	char	*str_p;

	str_p = (char *)s;
	while (*str_p != '\0')
	{
		if (*str_p == (unsigned char)c)
			return (str_p);
		str_p++;
	}
	if (*str_p == (unsigned char)c)
		return (str_p);
	else
		return (NULL);
}

char		*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
