/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:38:47 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 03:01:21 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	ft_free_matrix(char ***matrix)
{
	char	**m;
	int		i;

	m = *matrix;
	i = 0;
	if (!m)
		return ;
	while (m[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free(m);
	*matrix = NULL;
}
