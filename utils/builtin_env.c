/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:04:43 by despanol          #+#    #+#             */
/*   Updated: 2025/07/24 00:20:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	exec_built_env(t_console *terminal)
{
	int	i;

	if (!terminal || !terminal->envp)
	{
		g_exit_code = 1;
		return (1);
	}
	if (terminal->command_nodes && terminal->command_nodes->command
		&& terminal->command_nodes->command->splitted_command
		&& terminal->command_nodes->command->splitted_command[1])
	{
		write(2, "env: too many arguments\n", 24);
		g_exit_code = 1;
		return (1);
	}
	i = 0;
	while (terminal->envp[i])
	{
		printf("%s\n", terminal->envp[i]);
		i++;
	}
	g_exit_code = 0;
	return (0);
}
