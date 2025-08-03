/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_builtin_help.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:09:53 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:12 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

int	handle_execve_and_wait(char *executable_path,
		t_command_nodes *node, t_console *terminal)
{
	int	pid;
	int	status;

	if (!executable_path)
	{
		cmd_not_found(node->command->splitted_command[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		free(executable_path);
		executable_path = NULL;
		return (1);
	}
	if (pid == 0)
		execve_child(executable_path, node, terminal);
	else
	{
		waitpid(pid, &status, 0);
		wait_and_set_exit(status);
	}
	return (0);
}
