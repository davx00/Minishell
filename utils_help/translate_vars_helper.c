/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_vars_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:00:00 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 11:01:27 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

char	*build_expanded_string(char *str, int i, int pos, char *var)
{
	char	*aux;
	char	*path;
	char	*result;

	aux = ft_substr(str, 0, i - 1);
	if (var && *var)
		path = ft_strjoin(aux, var);
	else
		path = ft_strdup(aux);
	free(aux);
	if ((size_t)(i + pos) < ft_strlen(str))
		result = ft_strjoin(path, &str[i + pos]);
	else
		result = ft_strjoin(path, "");
	free(path);
	return (result);
}
