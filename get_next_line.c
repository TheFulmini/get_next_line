/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:22:17 by afulmini          #+#    #+#             */
/*   Updated: 2020/12/19 23:57:25 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		nl_line(char *str)
{
	int		i;

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

static char		*recuperate_line(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
	{
		dest = (char *)malloc(1);
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

static char		*save_static_line(char *str)
{
	int		i;
	int		j;
	char	*dest;

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
		return (NULL);
	i += 1;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(str);
	return (dest);
}

static int		check_input(char *buffer, const int fd, char **line)
{
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !buffer
			|| read(fd, NULL, 0) < 0)
	{
		if (buffer)
			free(buffer);
		line = NULL;
		return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*str_static;
	char		*buffer;
	int			result;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!check_input(buffer, fd, line))
		return (-1);
	result = 1;
	while (!nl_line(str_static) && result != 0)
	{
		result = read(fd, buffer, BUFFER_SIZE);
		if (result == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[result] = '\0';
		str_static = ft_strjoin(str_static, buffer);
	}
	free(buffer);
	*line = recuperate_line(str_static);
	str_static = save_static_line(str_static);
	result = (result == 0 && ft_strlen(str_static) == 0) ? 0 : 1;
	return (result);
}
