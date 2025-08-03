/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:24 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 20:33:04 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	execute_single_command(t_console *terminal,
	t_command_nodes *current_node)
{
	char	*command;
	int		stdout_backup;
	int		stdin_backup;

	stdin_backup = -1;
	stdout_backup = -1;
	if (!validate_single_command(terminal, current_node))
		return ;
	command = current_node->command->splitted_command[0];
	if (!handle_output_files(current_node, terminal, &stdin_backup,
			&stdout_backup))
		return ;
	if (!handle_redirections(current_node, &stdin_backup, &stdout_backup))
		return ;
	execute_command_dispatch(command, terminal, current_node);
	restore_redirections(stdin_backup, stdout_backup);
}

void	execute_builtin_in_pipe(t_console *terminal, t_command_nodes *cmd_node,
	int input_fd, int output_fd)
{
	char	*command;
	int		backup_fds;

	if (!cmd_node || !cmd_node->command || !cmd_node->command->splitted_command)
		return ;
	command = cmd_node->command->splitted_command[0];
	backup_fds = setup_pipe_redirections(input_fd, output_fd);
	exec_execute_command(command, terminal);
	restore_pipe_redirections(backup_fds);
}

void	basic_builtin_exec(t_console *terminal)
{
	if (!terminal || !terminal->command_nodes)
		return ;
	execute_pipeline_pipex_style(terminal);
}
