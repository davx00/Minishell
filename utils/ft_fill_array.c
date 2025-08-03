/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:21:08 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 17:21:08 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

char	**ft_fill_array(char **result, const char *s, char *separators,
	int indices[3])
{
	int	start_pos;
	int	quotes[2];
	int	str_len;

	quotes[0] = 0;
	quotes[1] = 0;
	str_len = ft_strlen(s);
	while (s[indices[0]])
	{
		skip_separators(s, separators, &indices[0]);
		start_pos = indices[0];
		process_word(s, separators, quotes, &indices[0]);
		if (start_pos >= str_len)
			result[indices[2]++] = NULL;
		else
			result[indices[2]++] = create_clean_word(s, start_pos, indices[0]);
	}
	return (result);
}
