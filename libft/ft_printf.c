/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:18:38 by despanol          #+#    #+#             */
/*   Updated: 2025/05/12 19:55:22 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printpointer(void *ptr)
{
	unsigned long	addr;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	return (2 + ft_hexa(addr, "0123456789abcdef"));
}

int	ft_whattype(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (c == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		count = ft_printpointer(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		count = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count = ft_putunsign(va_arg(args, unsigned int));
	else if (c == 'x')
		count = ft_hexa(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		count = ft_hexa(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		count = ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += ft_whattype(format[i + 1], args);
			i++;
		}
		else
		{
			count += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
	int	valor;
	int	*puntero;

	valor = 45;
	puntero = &valor;
	ft_printf("%p", (void *)puntero);
	printf("\n\n%p", (void *)puntero);
	return (0);
}
*/
