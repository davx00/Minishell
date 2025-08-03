/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_vars_to_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:27 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:31:33 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	is_inside_quotes(char *str, int i, int *quotes)
{
	if (str[i] == '\'' && !quotes[1])
		quotes[0] = !quotes[0];
	else if (str[i] == '\"' && !quotes[0])
		quotes[1] = !quotes[1];
	return (quotes[0] || quotes[1]);
}

int	should_expand_variable(char *str, int i, int *quotes)
{
	if (quotes[0] || str[i] != '$' || !str[i + 1])
		return (0);
	if (!quotes[1] && ft_strchars_index(&str[i + 1], "/~%^{}:; "))
		return (1);
	if (quotes[1] && ft_strchars_index(&str[i + 1], "/~%^{}:;\""))
		return (1);
	return (0);
}
