/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_replace_index.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:04:05 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:05:30 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_replace_index(char ***big, char **small, int index)
{
	char	**result;
	int		big_idx;
	int		small_idx;
	int		dest_idx;

	big_idx = -1;
	dest_idx = 0;
	small_idx = -1;
	if (!big || !*big || index < 0 || index >= (int)ft_array_len(*big))
		return ;
	result = ft_calloc(ft_array_len(*big) + ft_array_len(small),
			sizeof(char *));
	while (big[0][++big_idx] && result)
	{
		if (big_idx != index)
			result[dest_idx++] = ft_strdup((*big)[big_idx]);
		else
			while (small && small[++small_idx])
				result[dest_idx++] = ft_strdup(small[small_idx]);
	}
	ft_free_matrix(big);
	big[0] = result;
}
