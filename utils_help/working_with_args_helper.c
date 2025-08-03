/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:16:20 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:31:35 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	init_quote_vars(int *vars, char *quote_char)
{
	vars[0] = 0;
	vars[1] = 0;
	vars[2] = 0;
	*quote_char = 0;
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		vars[3];
	int		len;
	char	quote_char;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	init_quote_vars(vars, &quote_char);
	process_quote_removal(str, result, vars, &quote_char);
	result[vars[1]] = '\0';
	return (result);
}

void	skip_separators(const char *s, char *separators, int *index)
{
	while (ft_strchr(separators, s[*index]) && s[*index] != '\0')
		(*index)++;
}

void	process_word(const char *s, char *separators, int *quotes, int *index)
{
	while (s[*index] && (!ft_strchr(separators, s[*index])
			|| quotes[0] || quotes[1]))
		is_inside_quotes((char *)s, (*index)++, quotes);
}

char	*create_clean_word(const char *s, int start_pos, int end_pos)
{
	char	*temp_word;
	char	*clean_word;

	temp_word = ft_substr(s, start_pos, end_pos - start_pos);
	clean_word = remove_quotes(temp_word);
	free(temp_word);
	return (clean_word);
}
