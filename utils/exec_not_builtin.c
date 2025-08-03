/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 01:59:11 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 10:59:23 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	wait_and_set_exit(int status)
{
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = WTERMSIG(status) + 128;
}

static char	*get_path(char *command, t_console *terminal)
{
	char	*path_env;
	char	**whole_path_no_colon;

	if (command[0] == '/')
	{
		if (access(command, F_OK) == -1)
			return (NULL);
		if (access(command, X_OK) == -1)
			return (NULL);
		return (ft_strdup(command));
	}
	path_env = mini_getenv("PATH", terminal, 4);
	if (!path_env || !*path_env)
		return (get_path_no_env(command));
	whole_path_no_colon = ft_split(path_env, ':');
	free(path_env);
	path_env = NULL;
	return (get_path_env(command, whole_path_no_colon));
}

static void	handle_execve_error(char *command,
	t_console *terminal, t_pipeline_vars *vars)
{
	cmd_not_found(command);
	g_exit_code = 127;
	free_all_console_child(terminal);
	if (vars->heredoc_fds)
	{
		free(vars->heredoc_fds);
		vars->heredoc_fds = NULL;
	}
	if (vars->pids)
	{
		free(vars->pids);
		vars->pids = NULL;
	}
	exit(127);
}

int	exec_not_builtin(t_console *terminal,
	t_command_nodes *node, t_pipeline_vars *vars)
{
	char	*executable_path;
	char	*command;

	if (!node || !node->command || !node->command->splitted_command[0])
	{
		g_exit_code = 127;
		free_all_console(terminal);
		exit(127);
	}
	command = node->command->splitted_command[0];
	executable_path = get_path(command, terminal);
	if (!executable_path)
		handle_execve_error(command, terminal, vars);
	if (execve(executable_path, node->command->splitted_command,
			terminal->envp) == -1)
		execve_error(command, executable_path, terminal);
	free(executable_path);
	executable_path = NULL;
	return (g_exit_code);
}

int	exec_not_builtin_standalone(t_command_nodes *node, t_console *terminal)
{
	t_signal_data	*signal_data;
	char			*command;
	char			*executable_path;
	int				result;

	if (!node || !node->command || !node->command->splitted_command)
		return (-1);
	command = node->command->splitted_command[0];
	signal_data = get_signal_data();
	handle_signal_data(signal_data, command);
	executable_path = get_path(command, terminal);
	if (!executable_path)
		return (handle_path_error(command, signal_data));
	result = handle_fork_process(executable_path, node, terminal);
	free(executable_path);
	if (signal_data)
		signal_data->is_blocking_command = 0;
	return (result);
}
