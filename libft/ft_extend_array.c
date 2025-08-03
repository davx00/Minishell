/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:54:46 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 10:56:41 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static void	free_old_array(char **old_array)
{
	int	i;

	if (!old_array)
		return ;
	i = 0;
	while (old_array[i])
	{
		free(old_array[i]);
		i++;
	}
	free(old_array);
}

char	**ft_extend_array(char **old_array, char *new_element)
{
	int		i;
	int		len;
	char	**new_array;

	len = 0;
	if (old_array)
		while (old_array[len])
			len++;
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (old_array && i < len)
	{
		new_array[i] = ft_strdup(old_array[i]);
		i++;
	}
	new_array[i] = ft_strdup(new_element);
	new_array[i + 1] = NULL;
	free_old_array(old_array);
	return (new_array);
}
