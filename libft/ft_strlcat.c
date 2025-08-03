/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:23:00 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/07 17:23:31 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	index_src;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen((char *)src);
	if (n <= len_dst)
		return (n + len_src);
	index_src = 0;
	while (src[index_src] != '\0' && n > (len_dst + 1))
	{
		dst[len_dst] = src[index_src];
		index_src++;
		len_dst++;
	}
	dst[len_dst] = '\0';
	return (len_dst + ft_strlen((char *)(&src[index_src])));
}
/*
#include <stdio.h>
int main(void)
{
	char src[20] = "defy456";
	char dest[20] = "abcx123";

	ft_strlcat(dest, src, 13);
	printf("%s\n", dest);
	size_t cont;
	
	cont = 0;
	while ( dest[cont] != '\0' ) 
	{
		printf("%c", dest[cont]);
		cont++;
	}
	
	return (0);
}
*/
