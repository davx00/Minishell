/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:01 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 18:01:55 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

int	find_var_in_envp(char *var_name, char **envp)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var_name, var_len)
			&& (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**replace_env_var(char **envp, int i, char *new_value)
{
	char	*old;

	old = envp[i];
	envp[i] = new_value;
	free(old);
	return (envp);
}

char	*mini_getenv_terminal(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_index(envp[i], '='))
			n2 = ft_strchr_index(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**mini_setenv_terminal(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	aux[0] = NULL;
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_index(envp[i[0]], '='))
			i[1] = ft_strchr_index(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
			return (replace_env_var(envp, i[0], aux[1]));
	}
	envp = ft_extend_array(envp, aux[1]);
	free(aux[1]);
	aux[1] = NULL;
	return (envp);
}
