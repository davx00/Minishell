/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:38:05 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:27:58 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static int	contains_newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*previous_line(const char *c)
{
	char	*result;
	int		i;

	i = 0;
	if (!c)
		return (NULL);
	while (c[i] && c[i] != '\n')
		i++;
	result = ft_calloc(i + 2, sizeof(*result));
	if (!result)
		return (NULL);
	i = 0;
	while (c[i] && c[i] != '\n')
	{
		result[i] = c[i];
		i++;
	}
	if (c[i] == '\n')
		result[i] = '\n';
	return (result);
}

static void	ft_cleanup_read(char **bff, char **keep)
{
	if (bff && *bff)
	{
		free(*bff);
		*bff = NULL;
	}
	if (keep && *keep)
	{
		free(*keep);
		*keep = NULL;
	}
}

static void	*read_line(int fd, char *keep)
{
	int		bytes_read;
	char	*bff;
	char	*tmp;

	bff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bff)
		return (free(keep), NULL);
	bytes_read = read(fd, bff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		bff[bytes_read] = '\0';
		tmp = ft_strjoin(keep, bff);
		if (!tmp)
			return (ft_cleanup_read(&bff, &keep), NULL);
		free(keep);
		keep = tmp;
		if (contains_newline(bff))
			break ;
		bytes_read = read(fd, bff, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (ft_cleanup_read(&bff, &keep), NULL);
	return (free(bff), keep);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep = read_line(fd, keep);
	if (!keep)
		return (NULL);
	if (keep && *keep)
	{
		line = previous_line(keep);
		temp = keep;
		keep = ft_update_static(keep);
		free(temp);
	}
	else
		line = NULL;
	if (!line || *line == '\0')
		return (ft_cleanup_gnl(&keep, &line), NULL);
	return (line);
}
