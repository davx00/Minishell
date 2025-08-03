/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:22:43 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:26:15 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	ft_cleanup_gnl(char **keep, char **line)
{
	if (keep && *keep)
	{
		free(*keep);
		*keep = NULL;
	}
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
}

char	*ft_update_static(const char *keep)
{
	int		count;
	char	*x;
	int		i;
	int		count2;

	if (!keep)
		return (NULL);
	count2 = 0;
	count = 0;
	while (keep[count] && keep[count] != '\n')
		count++;
	if (!keep[count])
		return (NULL);
	count++;
	count2 = ft_strlen(keep + count);
	x = ft_calloc(count2 + 1, sizeof(*x));
	if (!x)
		return (NULL);
	i = 0;
	while (i < count2)
	{
		x[i] = keep[count + i];
		i++;
	}
	return (x);
}
