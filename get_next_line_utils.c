/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:39:52 by afulmini          #+#    #+#             */
/*   Updated: 2021/03/03 18:07:24 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst1;
	unsigned char	*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dst1 > src1)
	{
		while (len > 0)
		{
			dst1[len - 1] = src1[len - 1];
			len--;
		}
	}
	else
	{
		while (len--)
			*dst1++ = *src1++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	ft_memmove(str, s1, len1);
	ft_memmove(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	free((char *)s1);
	return (str);
}
