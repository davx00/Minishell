/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_integration_utils_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:14:57 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:29:24 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static	void	is_builtin(char *command,
						t_console *terminal, t_command_nodes *cmd_node)
{
	char			**original_argv;
	t_command_nodes	*original_cmd_nodes;

	original_argv = terminal->argv;
	original_cmd_nodes = terminal->command_nodes;
	terminal->argv = cmd_node->command->splitted_command;
	terminal->command_nodes = cmd_node;
	if (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		exec_built_pwd();
	else if (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		exec_built_echo(terminal);
	else if (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		exec_built_env(terminal);
	else if (ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		exec_built_cd(terminal);
	else if (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		exec_built_export(terminal);
	else if (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		exec_built_unset(terminal);
	terminal->argv = original_argv;
	terminal->command_nodes = original_cmd_nodes;
}

void	handle_input_redirection(t_command_nodes *cmd_node,
	t_console *terminal, t_pipeline_vars *vars)
{
	if (vars->heredoc_fds[vars->i] != -1)
		handle_heredoc_input(vars);
	else if (cmd_node->command->redirect_input && cmd_node->command->input_file)
		handle_file_input(cmd_node, terminal, vars);
	if (vars->prev_fd != STDIN_FILENO)
	{
		dup2(vars->prev_fd, STDIN_FILENO);
		close(vars->prev_fd);
	}
}

void	handle_output_redirection(t_command_nodes *cmd_node,
	t_console *terminal, t_pipeline_vars *vars)
{
	if (vars->is_last_command
		&& (cmd_node->command->redirect_output
			|| cmd_node->command->redirect_append)
		&& cmd_node->command->output_file)
	{
		vars->output_fd = open_output_file(cmd_node->command,
				terminal, vars);
	}
	if (vars->output_fd != STDOUT_FILENO)
	{
		dup2(vars->output_fd, STDOUT_FILENO);
		close(vars->output_fd);
	}
}

void	execute_command_child(t_command_nodes *cmd_node, t_console *terminal,
	t_pipeline_vars *vars)
{
	create_all_output_files(cmd_node->command, terminal);
	if (is_builtin_command(vars->command))
	{
		is_builtin(vars->command, terminal, cmd_node);
		free_all_console_2(terminal);
		free(vars->pids);
		vars->pids = NULL;
		free(vars->heredoc_fds);
		vars->heredoc_fds = NULL;
		exit(0);
	}
	else
	{
		exec_not_builtin(terminal, cmd_node, vars);
		free_all_console_child(terminal);
		free(vars->pids);
		vars->pids = NULL;
		free(vars->heredoc_fds);
		vars->heredoc_fds = NULL;
		exit(g_exit_code);
	}
}

void	mini_error(char *msg, t_console *terminal)
{
	perror(msg);
	free_all_console(terminal);
	exit(EXIT_FAILURE);
}
