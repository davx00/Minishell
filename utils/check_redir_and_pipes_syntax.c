/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_and_pipes_syntax.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:28:12 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 06:11:59 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	is_redirection_operator(char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (2);
		return (1);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (2);
		return (1);
	}
	return (0);
}

static int	check_redir_at_end_or_invalid(char *str, int i, int redir_len)
{
	int	j;

	j = i + redir_len;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	if (str[j] == '\0' || str[j] == '|' || is_redirection_operator(str, j))
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			57);
		return (1);
	}
	return (0);
}

static int	check_redirection_arguments(char *str)
{
	int		i;
	int		in_quotes;
	char	quote_char;
	int		redir_len;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		update_quote_state(str[i], &in_quotes, &quote_char);
		if (!in_quotes)
		{
			redir_len = is_redirection_operator(str, i);
			if (redir_len > 0)
			{
				if (check_redir_at_end_or_invalid(str, i, redir_len))
					return (1);
				i += redir_len - 1;
			}
		}
		i++;
	}
	return (0);
}

static int	check_pipe_at_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	return (0);
}

int	validate_syntax(char *command_line)
{
	if (!command_line || !*command_line)
		return (0);
	if (check_pipe_at_start(command_line))
	{
		g_exit_code = 2;
		return (1);
	}
	if (check_consecutive_operators(command_line))
	{
		g_exit_code = 2;
		return (1);
	}
	if (check_redirection_arguments(command_line))
	{
		g_exit_code = 2;
		return (1);
	}
	return (0);
}
