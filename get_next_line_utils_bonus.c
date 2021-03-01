/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afulmini <afulmini@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:37:33 by afulmini          #+#    #+#             */
/*   Updated: 2021/03/01 11:08:30 by afulmini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*gnl_memmove(void *dst, const void *src, size_t len)
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

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;

	if (!s1 && !s2)
		return (0);
	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	if (!(str = malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (0);
	gnl_memmove(str, s1, len_s1);
	gnl_memmove(str + len_s1, s2, len_s2);
	str[len_s1 + len_s2] = '\0';
	free((char *)s1);
	return (str);
}
