/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_add_row.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:41:16 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:53:20 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_add_row(char **in, char *newstr)
{
	char	**new_matrix;
	int		i;
	int		len;

	len = ft_array_len(in);
	new_matrix = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_matrix[i] = ft_strdup(in[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(newstr);
	new_matrix[i + 1] = NULL;
	ft_free_matrix(&in);
	return (new_matrix);
}
