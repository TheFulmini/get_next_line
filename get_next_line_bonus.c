/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:54:36 by afulmini          #+#    #+#             */
/*   Updated: 2021/02/13 12:17:52 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static int			nl_line(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char			*recup_line(char *str)
{
	int				i;
	char			*dest;

	i = 0;
	if (!str)
	{
		if (!(dest = (char *)malloc(1)))
			free(dest);
		dest[0] = '\0';
		return (dest);
	}
	while (str[i] && str[i] != '\n')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char			*save_static(char *str)
{
	int				i;
	int				j;
	char			*dest;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	j = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	i += 1;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(str);
	return (dest);
}

int					get_next_line(const int fd, char **line)
{
	static char		*str_static[MAX_FD];
	char			*buffer;
	int				result;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 ||
		!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	result = 1;
	while (!nl_line(str_static[fd]) && result != 0)
	{
		result = read(fd, buffer, BUFFER_SIZE);
		if (result == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[result] = '\0';
		str_static[fd] = ft_strjoin(str_static[fd], buffer);
	}
	free(buffer);
	*line = recup_line(str_static[fd]);
	str_static[fd] = save_static(str_static[fd]);
	result = (result == 0 && ft_strlen(str_static[fd]) == 0) ? 0 : 1;
	return (result);
}
