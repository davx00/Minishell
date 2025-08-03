/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:41:43 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/03 16:12:28 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	str_len;
	size_t	cont;
	char	*str;

	cont = 0;
	str_len = ft_strlen(s);
	str = (char *)malloc((str_len + 1) * sizeof(char));
	if (s == 0 || f == 0 || str == 0)
		return (NULL);
	while (cont < str_len)
	{
		str[cont] = (*f)(cont, s[cont]);
		cont++;
	}
	str[cont] = '\0';
	return (str);
}
/*
#include <stdio.h>

int main(void)
{
	char str[] = "11111";
	char *str2;
	
	str2 = ft_strmapi(str, *funcion);
	printf("%s", str2);
	return (0);
}
*/
