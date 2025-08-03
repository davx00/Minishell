/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:30 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 11:00:14 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static char	*return_envp_value(char *var,
	int index_post_equal, int size_to_copy)
{
	return (ft_substr(var, index_post_equal, size_to_copy));
}

static int	var_is_found_in_envp(t_console *terminal,
	int *i, char *var, char **aux)
{
	char	*old_value;

	if (!ft_strncmp(terminal->envp[i[0]], var, i[1]))
	{
		old_value = terminal->envp[i[0]];
		terminal->envp[i[0]] = ft_strdup(aux[1]);
		free(old_value);
		return (1);
	}
	return (0);
}

static void	resize_n_to_envp(int index, int *index_array, t_console *terminal)
{
	index_array[1] = index;
	if (index_array[1]
		< ft_strchr_index(terminal->envp[index_array[0]], (unsigned char) '='))
		index_array[1] = ft_strchr_index(terminal->envp[index_array[0]],
				(unsigned char) '=');
}

void	mini_setenv(char *var_name, int n, t_console *terminal, char **value)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var_name);
	i[0] = -1;
	aux[0] = ft_strjoin(var_name, "=");
	aux[1] = ft_strjoin(aux[0], *value);
	free(aux[0]);
	aux[0] = NULL;
	while (!ft_strchr(var_name, '=')
		&& terminal->envp && terminal->envp[++i[0]])
	{
		resize_n_to_envp(n, i, terminal);
		if (var_is_found_in_envp(terminal, i, var_name, aux))
		{
			free(aux[1]);
			aux[1] = NULL;
			return ;
		}
	}
	terminal->envp = ft_extend_array(terminal->envp, aux[1]);
	free(aux[1]);
	aux[1] = NULL;
}

char	*mini_getenv(char *var_name, t_console *terminal, int n)
{
	int		i[2];
	char	*envp_value;

	envp_value = NULL;
	i[0] = 0;
	if (n < 0)
		n = ft_strlen(var_name);
	while (!ft_strchr(var_name, '=') && terminal->envp && terminal->envp[i[0]])
	{
		i[1] = n;
		resize_n_to_envp(n, i, terminal);
		if (!ft_strncmp(terminal->envp[i[0]], var_name, i[1]))
		{
			envp_value = return_envp_value(terminal->envp[i[0]],
					i[1] + 1, ft_strlen(terminal->envp[i[0]]));
			return (envp_value);
		}
		i[0]++;
	}
	return (envp_value);
}
