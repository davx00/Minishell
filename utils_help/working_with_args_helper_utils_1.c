/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_helper_utils_1.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:39:46 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/02 19:44:49 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	process_quote_removal(char *str, char *result,
	int *vars, char *quote_char)
{
	while (str[vars[0]])
	{
		if (!vars[2] && (str[vars[0]] == '\'' || str[vars[0]] == '\"'))
		{
			*quote_char = str[vars[0]];
			vars[2] = 1;
		}
		else if (vars[2] && str[vars[0]] == *quote_char)
		{
			vars[2] = 0;
			*quote_char = 0;
		}
		else
			result[vars[1]++] = str[vars[0]];
		vars[0]++;
	}
}
