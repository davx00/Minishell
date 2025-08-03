/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:00:15 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/07 14:02:42 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		sign;
	int		num;

	str = (char *)nptr;
	sign = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		str--;
	while ((*str >= '0' && *str <= '9'))
		num = (num * 10) + (*str++) - '0';
	return (num * sign);
}
/*
#include <stdio.h>

int main(void)
{

int num = ft_atoi("321-123");

printf("%i", num);

return (0);
}
*/
