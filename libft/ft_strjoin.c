/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:47:11 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 02:54:11 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_string;
	size_t	s1_len;
	size_t	s2_len;
	size_t	cont;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	cont = 0;
	new_string = (char *)(malloc((s1_len + s2_len + 1) * sizeof(char)));
	if (new_string == NULL)
		return (NULL);
	while (s1 && s1[cont] != '\0')
	{
		new_string[cont] = s1[cont];
		cont++;
	}
	cont = 0;
	while (s2 && s2[cont] != '\0')
	{
		new_string[cont + s1_len] = s2[cont];
		cont++;
	}
	new_string[s1_len + s2_len] = '\0';
	return (new_string);
}
