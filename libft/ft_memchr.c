/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:01:03 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/25 13:01:39 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		cont;

	str = (const char *)s;
	cont = 0;
	while (cont < n)
	{
		if ((unsigned char)str[cont] == (unsigned char)c)
			return ((void *)(s + cont));
		cont++;
	}
	return (NULL);
}

/*
#include <stdio.h>
int main(void)
{
	char s1[] = "/|\100\xff\200|\\";
	
	printf("%s", (char *)ft_memchr(s1, '\200', 6));
	
	return (0);
}*/
