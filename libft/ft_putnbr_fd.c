/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:47:44 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/07 19:20:56 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	int	aux;

	aux = n;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (aux < 0)
	{
		ft_putchar_fd('-', fd);
		aux = aux * -1;
	}
	if (aux / 10 > 0)
		ft_putnbr_fd((aux / 10), fd);
	ft_putchar_fd((aux % 10) + '0', fd);
}
/*
int main(void)
{
	int fd;
	
	fd = open("../fichero.txt", O_WRONLY);
	ft_putnbr_fd(-2147483648, fd);
	close(fd);
	return (0);
}
*/
