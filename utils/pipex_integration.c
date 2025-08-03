/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_integration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:14:57 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	exec_child(t_command_nodes *cmd_node,
						t_console *terminal,
						t_pipeline_vars vars)
{
	if (!cmd_node || !cmd_node->command || !cmd_node->command->splitted_command)
	{
		free(vars.pids);
		vars.pids = NULL;
		free(vars.heredoc_fds);
		vars.heredoc_fds = NULL;
		exit(127);
	}
	vars.command = cmd_node->command->splitted_command[0];
	vars.is_last_command = (vars.output_fd == STDOUT_FILENO);
	handle_input_redirection(cmd_node, terminal, &vars);
	handle_output_redirection(cmd_node, terminal, &vars);
	execute_command_child(cmd_node, terminal, &vars);
}

int	execute_pipeline_pipex_style(t_console *terminal)
{
	t_pipeline_vars	vars;

	if (!terminal || !terminal->command_nodes)
		return (0);
	vars.cmd_count = count_commands_in_pipeline(terminal->command_nodes);
	if (vars.cmd_count == 1)
		return (execute_single_command(terminal, terminal->command_nodes), 1);
	if (!allocate_pipeline_resources(vars.cmd_count,
			&vars.pids, &vars.heredoc_fds))
		return (0);
	setup_pipeline_vars(&vars, terminal->command_nodes, vars.pids);
	execute_pipeline_loop(terminal, &vars);
	wait_and_set_exit_status(vars.pids, &vars);
	pipeline_cleanup(vars.pids, vars.heredoc_fds);
	return (1);
}
