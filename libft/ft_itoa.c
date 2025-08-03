/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:29:07 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/03 12:30:22 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sizeint(int n);

int	ft_sizeint(int n)
{
	int	cont;

	cont = 1;
	while ((n / 10) != 0)
	{
		cont++;
		n = n / 10;
	}
	return (cont);
}

char	*ft_itoa(int n)
{
	char			*str_num;
	size_t			size_n;
	unsigned int	num;

	num = n;
	size_n = ft_sizeint(n);
	if (n < 0)
	{
		num *= -1;
		size_n++;
	}
	str_num = (char *)malloc((size_n + 1) * sizeof(char));
	if (!str_num)
		return (NULL);
	str_num[size_n] = '\0';
	while (size_n--)
	{
		str_num[size_n] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str_num[0] = '-';
	return (str_num);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%s", ft_itoa(-123));
	return (0);
}
*/
