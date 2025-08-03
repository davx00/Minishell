/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_integration_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:14:57 by despanol          #+#    #+#             */
/*   Updated: 2025/07/27 00:47:39 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

int	get_output_flags(t_command *cmd)
{
	if (cmd->redirect_append)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_WRONLY | O_CREAT | O_TRUNC);
}

int	open_output_file(t_command *cmd, t_console *terminal,
	t_pipeline_vars *vars)
{
	int	flags;
	int	fd;

	flags = get_output_flags(cmd);
	fd = open(cmd->output_file, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->output_file);
		free_all_console(terminal);
		free(vars->pids);
		vars->pids = NULL;
		free(vars->heredoc_fds);
		vars->heredoc_fds = NULL;
		exit(1);
	}
	return (fd);
}

void	handle_heredoc_input(t_pipeline_vars *vars)
{
	if (vars->prev_fd != STDIN_FILENO)
		close(vars->prev_fd);
	vars->prev_fd = vars->heredoc_fds[vars->i];
}

void	handle_file_input(t_command_nodes *cmd_node, t_console *terminal,
	t_pipeline_vars *vars)
{
	int	redirect_in_fd;

	redirect_in_fd = open(cmd_node->command->input_file, O_RDONLY);
	if (redirect_in_fd < 0)
	{
		perror(cmd_node->command->input_file);
		free_all_console(terminal);
		free(vars->pids);
		vars->pids = NULL;
		free(vars->heredoc_fds);
		vars->heredoc_fds = NULL;
		exit(1);
	}
	if (vars->prev_fd != STDIN_FILENO)
		close(vars->prev_fd);
	vars->prev_fd = redirect_in_fd;
}
