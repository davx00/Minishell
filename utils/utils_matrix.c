/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:32 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 19:47:07 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

char	**matrix_dup(char **matrix)
{
	int		cont;
	size_t	rows;
	char	**out;

	cont = -1;
	rows = ft_array_len(matrix) + 1;
	out = malloc(sizeof(char *) * (rows));
	if (!out)
		return (NULL);
	while (matrix[++cont])
	{
		out[cont] = ft_strdup(matrix[cont]);
		if (!out[cont])
			return (ft_free_matrix(&out), NULL);
	}
	out[cont] = NULL;
	return (out);
}
