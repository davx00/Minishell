/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_and_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:24:18 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:01:02 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words_and_quotes(const char *s,
	char *separators, int *position, int *word_count)
{
	int				in_quotes;
	char			quote_type;
	t_quote_state	state;

	quote_type = 0;
	in_quotes = 0;
	state.in_quotes = &in_quotes;
	state.quote_type = &quote_type;
	while (s[*position] != '\0')
	{
		while (ft_strchr(separators, s[*position]) && s[*position] != '\0')
			(*position)++;
		if (s[*position] == '\0')
			break ;
		(*word_count)++;
		while (s[*position] != '\0')
		{
			if (!process_char_in_word(s, position, &state, separators))
				break ;
		}
		if (in_quotes)
			return (-1);
	}
	return (*word_count);
}

int	ft_count_words_and_quotes_main(const char *s, char *separators)
{
	int				in_quotes;
	char			quote_type;
	int				position;
	int				word_count;
	t_quote_state	state;

	init_counters(&position, &word_count);
	init_quote_state(&state, &in_quotes, &quote_type);
	while (s && s[position] != '\0')
	{
		if (!process_word_main(s, &position, &state, separators))
			break ;
		word_count++;
		if (in_quotes)
			return (-1);
	}
	return (word_count);
}
