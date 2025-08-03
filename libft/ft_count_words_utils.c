/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 03:00:00 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:00:00 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_counters(int *position, int *word_count)
{
	*position = 0;
	*word_count = 0;
}

void	init_quote_state(t_quote_state *state, int *in_quotes,
	char *quote_type)
{
	*in_quotes = 0;
	*quote_type = 0;
	state->in_quotes = in_quotes;
	state->quote_type = quote_type;
}

int	process_char_in_word(const char *s, int *pos,
	t_quote_state *state, char *separators)
{
	if (!*(state->in_quotes) && (s[*pos] == '\"' || s[*pos] == '\''))
	{
		*(state->quote_type) = s[*pos];
		*(state->in_quotes) = 1;
	}
	else if (*(state->in_quotes) && s[*pos] == *(state->quote_type))
	{
		*(state->in_quotes) = 0;
		*(state->quote_type) = 0;
	}
	else if (!*(state->in_quotes) && ft_strchr(separators, s[*pos]))
		return (0);
	(*pos)++;
	return (1);
}

int	process_word_main(const char *s, int *position,
	t_quote_state *state, char *separators)
{
	while (ft_strchr(separators, s[*position]) && s[*position] != '\0')
		(*position)++;
	if (s[*position] == '\0')
		return (0);
	while (s[*position] != '\0')
	{
		if (!process_char_in_word(s, position, state, separators))
			break ;
	}
	return (1);
}
