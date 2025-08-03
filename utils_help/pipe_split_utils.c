/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:32:00 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:28:49 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static void	update_quote_state_pipe(char current_char,
	int *in_quotes, char *quote_char)
{
	if ((current_char == '"' || current_char == '\'') && !(*in_quotes))
	{
		*in_quotes = 1;
		*quote_char = current_char;
	}
	else if (current_char == *quote_char && *in_quotes)
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
}

static int	count_pipes_outside_quotes(char const *s)
{
	int		pipe_count;
	int		i;
	int		in_quotes;
	char	quote_char;

	pipe_count = 0;
	i = 0;
	in_quotes = 0;
	quote_char = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		update_quote_state_pipe(s[i], &in_quotes, &quote_char);
		if (s[i] == '|' && !in_quotes)
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

static void	extract_command_segment(char const *s, char **result, int *vars)
{
	int		i;
	int		start;
	int		cmd_idx;
	int		in_quotes;
	char	quote_char;

	i = vars[0];
	start = vars[1];
	cmd_idx = vars[2];
	in_quotes = vars[3];
	quote_char = vars[4];
	while (s[i])
	{
		update_quote_state_pipe(s[i], &in_quotes, &quote_char);
		if (s[i] == '|' && !in_quotes)
		{
			result[cmd_idx] = ft_substr(s, start, i - start);
			cmd_idx++;
			start = i + 1;
		}
		i++;
	}
	result[cmd_idx] = ft_substr(s, start, i - start);
	result[cmd_idx + 1] = NULL;
}

char	**split_by_pipes_preserve_quotes(char const *s)
{
	char	**result;
	int		pipe_count;
	int		vars[5];

	if (!s)
		return (NULL);
	pipe_count = count_pipes_outside_quotes(s);
	result = malloc((pipe_count + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	vars[0] = 0;
	vars[1] = 0;
	vars[2] = 0;
	vars[3] = 0;
	vars[4] = 0;
	extract_command_segment(s, result, vars);
	return (result);
}
