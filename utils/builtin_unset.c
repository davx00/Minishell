/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:04:59 by despanol          #+#    #+#             */
/*   Updated: 2025/07/27 00:52:30 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static int	var_in_envp_unset(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_index(argv, '=');
	if (pos == -1)
		return (0);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

static void	unset_var_no_equal(char *arg, t_console *terminal)
{
	char	*aux;
	int		idx;

	aux = ft_strjoin(arg, "=");
	idx = 0;
	while (terminal->envp[idx])
	{
		if (!ft_strncmp(terminal->envp[idx], aux, ft_strlen(aux)))
		{
			ft_matrix_replace_index(&terminal->envp, NULL, idx);
			break ;
		}
		idx++;
	}
	free(aux);
	aux = NULL;
}

static void	unset_var_with_equal(char *arg, t_console *terminal)
{
	int	ij[2];

	if (var_in_envp_unset(arg, terminal->envp, ij))
		ft_matrix_replace_index(&terminal->envp, NULL, ij[1]);
}

int	exec_built_unset(t_console *terminal)
{
	char	**argv;
	int		idx;

	if (!terminal || !terminal->command_nodes
		|| !terminal->command_nodes->command)
		return (1);
	argv = terminal->command_nodes->command->splitted_command;
	idx = 0;
	if (ft_array_len(argv) >= 2)
	{
		while (argv[++idx])
		{
			if (argv[idx][ft_strlen(argv[idx]) - 1] != '=')
				unset_var_no_equal(argv[idx], terminal);
			else
				unset_var_with_equal(argv[idx], terminal);
		}
	}
	g_exit_code = 0;
	return (0);
}
