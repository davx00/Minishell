/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:33:53 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 09:57:39 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static int	var_in_envp(char *argv, char **envp, int *index_found)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strchr_index(argv, '=');
	if (name_len == -1)
		name_len = ft_strlen(argv);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], argv, name_len)
			&& (envp[i][name_len] == '=' || argv[name_len] == '='))
		{
			*index_found = i;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	is_valid_var_name(char *name, int name_len)
{
	int	i;

	if (name_len <= 0)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (i < name_len)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
	g_exit_code = 0;
}

void	export_var_no_value(char *arg, t_console *terminal)
{
	int		found_index;
	char	*new_pair;
	int		name_len;

	name_len = ft_strlen(arg);
	if (!is_valid_var_name(arg, name_len))
	{
		fprintf(stderr,
			"export: '%s': not a valid identifier\n",
			arg);
		g_exit_code = 1;
	}
	else
	{
		if (!var_in_envp(arg, terminal->envp, &found_index))
		{
			new_pair = ft_strjoin(arg, "=");
			terminal->envp = ft_extend_array(terminal->envp, new_pair);
			free(new_pair);
			new_pair = NULL;
		}
	}
}

void	export_var_with_value(char *arg, int pos, t_console *terminal)
{
	int	found_index;

	if (!is_valid_var_name(arg, pos))
	{
		fprintf(stderr, "export: '%s': not a valid identifier\n", arg);
		g_exit_code = 1;
	}
	else
	{
		if (var_in_envp(arg, terminal->envp, &found_index))
		{
			free(terminal->envp[found_index]);
			terminal->envp[found_index] = NULL;
			terminal->envp[found_index] = ft_strdup(arg);
		}
		else
			terminal->envp = ft_extend_array(terminal->envp, arg);
	}
}
