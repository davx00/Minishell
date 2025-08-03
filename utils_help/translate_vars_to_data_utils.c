/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_vars_to_data_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:02:00 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 11:02:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static int	calculate_position(char *str, int i)
{
	int	pos;

	pos = 0;
	while (str[i + pos] && (ft_isalnum(str[i + pos]) || str[i + pos] == '_'))
		pos++;
	if (pos == 0 && ft_strchr("$?", str[i]))
		pos = 1;
	return (pos);
}

static char	*get_variable_value(char *str, int i, t_console *prompt)
{
	char	*var;
	char	*var_name;
	int		len;

	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	var_name = ft_substr(str, i, len);
	var = mini_getenv(var_name, prompt, len);
	free(var_name);
	if (!var)
	{
		if (str[i] == '$')
			var = ft_itoa(prompt->pid);
		else if (str[i] == '?')
			var = ft_itoa(g_exit_code);
		else
		{
			var = ft_strdup("");
		}
	}
	return (var);
}

char	*get_substr_var(char *str, int i, t_console *prompt)
{
	char	*var;
	char	*result;
	int		pos;

	pos = calculate_position(str, i);
	var = get_variable_value(str, i, prompt);
	result = build_expanded_string(str, i, pos, var);
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (var)
	{
		free(var);
		var = NULL;
	}
	return (result);
}

static char	*expand_tilde(char *str, int i, char *var)
{
	char	*aux;
	char	*path;

	aux = ft_substr(str, 0, i);
	path = ft_strjoin(aux, var);
	free(aux);
	aux = NULL;
	aux = ft_substr(str, i + 1, ft_strlen(str));
	free(str);
	str = NULL;
	str = ft_strjoin(path, aux);
	free(aux);
	aux = NULL;
	free(path);
	path = NULL;
	return (str);
}

char	*expand_string(char *str, int i, int *quotes, t_console *prompt)
{
	char	*var;
	int		var_len;

	while (str && str[++i])
	{
		if (is_inside_quotes(str, i, quotes)
			&& str[i] == '~' && (i == 0 || str[i - 1] != '$'))
		{
			var = mini_getenv("HOME", prompt, 4);
			if (!var)
				var = malloc(sizeof(char));
			var_len = ft_strlen(var);
			str = expand_tilde(str, i, var);
			free(var);
			return (expand_string(str, i + var_len - 1, quotes, prompt));
		}
		if (should_expand_variable(str, i, quotes))
			return (expand_string(get_substr_var(str, ++i, prompt), -1,
					quotes, prompt));
	}
	return (str);
}
