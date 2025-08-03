/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:30:00 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/02 21:20:56 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	validate_single_command(t_console *terminal,
	t_command_nodes *current_node)
{
	if (!current_node || !current_node->command
		|| !current_node->command->splitted_command
		|| !current_node->command->splitted_command[0])
		return (0);
	if (count_commands_in_pipeline(terminal->command_nodes) > 1)
		return (0);
	return (1);
}

int	handle_output_files(t_command_nodes *current_node,
	t_console *terminal, int *stdin_backup, int *stdout_backup)
{
	int	original_exit_code;

	original_exit_code = g_exit_code;
	create_all_output_files(current_node->command, terminal);
	if (g_exit_code != original_exit_code)
	{
		restore_redirections(*stdin_backup, *stdout_backup);
		return (0);
	}
	return (1);
}

int	handle_redirections(t_command_nodes *current_node,
	int *stdin_backup, int *stdout_backup)
{
	int	original_exit_code;

	original_exit_code = g_exit_code;
	setup_input_redirection(current_node, stdin_backup);
	if (g_exit_code != original_exit_code)
	{
		restore_redirections(*stdin_backup, *stdout_backup);
		return (0);
	}
	setup_output_redirection(current_node, stdout_backup);
	if (g_exit_code != original_exit_code)
	{
		restore_redirections(*stdin_backup, *stdout_backup);
		return (0);
	}
	return (1);
}
