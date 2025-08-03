/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:14:05 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/20 15:47:27 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	cont;

	cont = 0;
	while (cont < n)
	{
		((char *)s)[cont] = c;
		cont++;
	}
	return (s);
}
/*
#include <stdio.h>

int main(void)
{
	char frase[] = "Saludos";
	void *pointer = &frase;

	ft_memset(pointer, 65, 8);
	printf("%s", frase);

	printf("%c", *(char*)pointer); TIENE QUE ESTAR COMENTADO, ES OTRA OPCIÓN
	return (0);
}
*/
