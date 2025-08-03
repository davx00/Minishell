/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:35:23 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/25 12:38:25 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	src_len;
	size_t	cont;

	src_len = ft_strlen(s);
	cont = 0;
	if ((unsigned char)c == '\0')
		return ((char *)s + src_len);
	while ((unsigned char)*s != (unsigned char)c && cont < src_len)
	{
		cont++;
		s++;
	}
	if (cont == src_len)
		return (NULL);
	return ((char *)s);
}
