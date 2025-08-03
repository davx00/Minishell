/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:27:25 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 10:58:09 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	exec_built_export(t_console *terminal)
{
	int		idx;
	int		pos;
	char	**argv;

	if (!terminal || !terminal->command_nodes
		|| !terminal->command_nodes->command)
		return (1);
	argv = terminal->command_nodes->command->splitted_command;
	idx = 1;
	g_exit_code = 0;
	if (ft_array_len(argv) >= 2)
	{
		while (argv[idx])
		{
			pos = ft_strchr_index(argv[idx], '=');
			if (pos == -1)
				export_var_no_value(argv[idx], terminal);
			else
				export_var_with_value(argv[idx], pos, terminal);
			idx++;
		}
	}
	else
		print_envp(terminal->envp);
	return (0);
}
