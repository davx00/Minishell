/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:39:41 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/25 12:55:43 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	src_len;
	size_t	cont;

	src_len = ft_strlen(s);
	cont = 0;
	if (src_len == 0 && c == '\0')
		return ((char *)s);
	else if (src_len == 0)
		return (NULL);
	s += src_len;
	while ((unsigned char)*s != (unsigned char)c && cont < src_len)
	{
		cont++;
		s--;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
