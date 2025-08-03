/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_redir_pipes_utils_2.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:30:31 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 18:37:32 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

int	process_char_outside_quotes(char *str, int *i)
{
	int	redir_len;

	if (check_double_pipe(str, *i))
		return (1);
	redir_len = is_redirection_operator(str, *i);
	if (redir_len > 0)
	{
		if (check_redir_followed_by_operator(str, *i, redir_len))
			return (1);
		*i += redir_len - 1;
	}
	if (check_pipe_followed_by_invalid(str, *i))
		return (1);
	return (0);
}
