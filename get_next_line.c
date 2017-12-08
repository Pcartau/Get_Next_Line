/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcartau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 09:35:26 by pcartau           #+#    #+#             */
/*   Updated: 2017/12/08 09:18:22 by pcartau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cutstring(char *dst, int i)
{
	int x;

	x = 0;
	if (dst[i] == '\n')
		i++;
	while (dst[i])
	{
		dst[x] = dst[i];
		x++;
		i++;
	}
	dst[x] = '\0';
	return (dst);
}

char	*strj(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 && s2)
	{
		i = (ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		j = 0;
		while (s2[j])
			str[i++] = s2[j++];
		str[i] = '\0';
		free(s1);
		return (str);
	}
	return (NULL);
}

char	*filltab(char *line, char *dst)
{
	int i;

	i = 0;
	while (dst[i] != '\n' && dst[i])
		i++;
	if (!(line = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (dst[i] != '\n' && dst[i])
	{
		line[i] = dst[i];
		i++;
	}
	line[i] = '\0';
	dst = cutstring(dst, i);
	return (line);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*dst;
	char		str[BUFF_SIZE + 1];

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	if (!dst)
		if (!(dst = malloc(sizeof(char))))
			return (-1);
	while ((ret = read(fd, str, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		str[ret] = '\0';
		dst = strj(dst, str);
	}
	if (dst[0] == '\0')
		return (0);
	*line = filltab(*line, dst);
	return (1);
}
