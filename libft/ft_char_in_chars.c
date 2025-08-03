/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_in_chars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:20:02 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:12 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchars_index(const char *s, char *set)
{
	int	i;
	int	j;

	i = 0;
	if (!s || !set)
		return (-1);
	while (s[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
