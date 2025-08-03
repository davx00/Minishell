/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:54:46 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/07 17:46:30 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*sr;

	dest = (char *)dst;
	sr = (const char *)src;
	if (dest > sr)
	{
		while (n--)
			dest[n] = sr[n];
	}
	else if (dest < sr)
		ft_memcpy(dest, src, n);
	return (dst);
}
/*
#include <stdio.h>
int main(void)
{
	char src[5] = "";
	char dest[10] = "";
	
	
	printf("%s", (char*)ft_memmove(dest, src, 5));
	
	return (0);
}
*/
