/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:02:03 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/25 13:38:09 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n);

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	cont;

	str1 = (char *)s1;
	str2 = (char *)s2;
	cont = 0;
	while (cont < n)
	{
		if ((unsigned char)str1[cont] != (unsigned char)str2[cont])
			return ((unsigned char)str1[cont] - (unsigned char)str2[cont]);
		else
			cont++;
	}
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
	char s1[] = "abcd";
	char s2[] = "abcd";
	
	printf("%i", ft_memcmp(s1, s2, 10));
	
	return (0);
}
*/
