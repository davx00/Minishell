/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:40:51 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/25 11:18:28 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	cont;

	cont = 0;
	if (!dest && !src)
		return (0);
	while (cont < n)
	{
		((char *)dest)[cont] = ((char *)src)[cont];
		cont++;
	}
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
	char frase1[] = "Hola";
	char frase2[] = "como estas";

	printf("%s", (char*)ft_memcpy(frase1, frase2, 3));
	return (0);
}
*/
