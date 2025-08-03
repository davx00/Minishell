/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_and_pipes_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:17:26 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 18:35:47 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	update_quote_state(char current, int *in_quotes, char *quote_char)
{
	if ((current == '"' || current == '\'') && !*in_quotes)
	{
		*in_quotes = 1;
		*quote_char = current;
	}
	else if (current == *quote_char && *in_quotes)
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
}

int	check_double_pipe(char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `||'\n", 52);
		return (1);
	}
	return (0);
}

int	check_redir_followed_by_operator(char *str, int i, int redir_len)
{
	int	j;

	j = i + redir_len;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	if (is_redirection_operator(str, j) || str[j] == '|')
	{
		write(2, "minishell: syntax error near unexpected token\n", 46);
		return (1);
	}
	return (0);
}

int	check_pipe_followed_by_invalid(char *str, int i)
{
	int	j;

	if (str[i] != '|')
		return (0);
	j = i + 1;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	if (str[j] == '\0' || str[j] == '|' || is_redirection_operator(str, j))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	return (0);
}

int	check_consecutive_operators(char *str)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		update_quote_state(str[i], &in_quotes, &quote_char);
		if (!in_quotes)
		{
			if (process_char_outside_quotes(str, &i))
				return (1);
		}
		i++;
	}
	return (0);
}
