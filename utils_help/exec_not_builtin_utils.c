/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_builtin_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 02:17:24 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 02:50:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	handle_signal_data(t_signal_data *signal_data, char *command)
{
	if (signal_data && is_blocking_command(command))
		signal_data->is_blocking_command = 1;
}

int	handle_path_error(char *command, t_signal_data *signal_data)
{
	cmd_not_found(command);
	(void) command;
	if (signal_data)
		signal_data->is_blocking_command = 0;
	return (127);
}

static void	handle_child_process(char *executable_path,
	t_command_nodes *node, t_console *terminal)
{
	if (execve(executable_path, node->command->splitted_command,
			terminal->envp) == -1)
	{
		execve_error(node->command->splitted_command[0],
			executable_path, terminal);
	}
}

int	handle_fork_process(char *executable_path,
	t_command_nodes *node, t_console *terminal)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		handle_child_process(executable_path, node, terminal);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		wait_and_set_exit(status);
	}
	else
	{
		perror("fork");
		g_exit_code = 1;
	}
	return (g_exit_code);
}
