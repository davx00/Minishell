/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:18:56 by despanol          #+#    #+#             */
/*   Updated: 2025/05/12 19:58:51 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putchar('-');
		count += ft_putchar('2');
		count += ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		count += ft_putchar('-');
		count += ft_putnbr(-n);
	}
	else if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	else
		count += ft_putchar(n + '0');
	return (count);
}

int	ft_putunsign(unsigned int ns)
{
	int				i;
	char			str[10];
	int				count;
	unsigned long	n;

	i = 0;
	if (ns == 0)
	{
		ft_putchar('0');
		return (1);
	}
	n = (unsigned int)ns;
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	count = i;
	while (i--)
		ft_putchar(str[i]);
	return (count);
}

int	ft_hexa(unsigned long n, const char *base)
{
	const char	*hexa_digits = base;
	char		str[65];
	int			i;
	int			count;

	i = 0;
	count = 0;
	if (n == 0)
	{
		return (ft_putchar('0'));
	}
	while (n > 0)
	{
		str[i++] = hexa_digits[n % 16];
		n = n / 16;
	}
	while (i--)
	{
		count += ft_putchar(str[i]);
	}
	return (count);
}
