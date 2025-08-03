/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_clone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:07:08 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:52:17 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_clone(char **src) // duplica la matrix
{
	char	**copy;
	int		count;
	int		row;

	count = ft_array_len(src);
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	row = 0;
	while (src[row])
	{
		copy[row] = ft_strdup(src[row]);
		if (!copy[row])
		{
			while (row > 0)
				free(copy[--row]);
			free(copy);
			copy = NULL;
			return (NULL);
		}
		row++;
	}
	copy[row] = NULL;
	return (copy);
}
