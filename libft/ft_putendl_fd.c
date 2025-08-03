/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:46:12 by akamal-b          #+#    #+#             */
/*   Updated: 2024/10/07 19:20:55 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
#include <fcntl.h>

int main(void)
{
	int fd;
	
	fd = open("../fichero.txt", O_WRONLY);
	ft_putendl_fd("Capricos", fd);
	close(fd);
	return (0);
}
*/
