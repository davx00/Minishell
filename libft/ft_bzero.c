/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:45:30 by akamal-b          #+#    #+#             */
/*   Updated: 2024/09/20 15:46:15 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n);

void	ft_bzero(void *s, size_t n)
{
	size_t	cont;

	cont = 0;
	while (cont < n)
	{
		((char *)s)[cont] = '\0';
		cont++;
	}
}
/*
#include <stdio.h>

int main(void)
{
	char frase[] = "Saludos";
	void *pointer = &frase;

	ft_bzero(pointer, 3);

	for(int i=0; i<7; i++)
	{
		printf("%c", frase[i]);
	}

	return (0);
}
*/
