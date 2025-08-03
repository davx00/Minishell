/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution_utils_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:24 by despanol          #+#    #+#             */
/*   Updated: 2025/07/29 17:35:31 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	restore_pipe_redirections(int backup_fds)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = backup_fds >> 16;
	stdout_backup = backup_fds & 0xFFFF;
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

int	setup_pipe_redirections(int input_fd, int output_fd)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = -1;
	stdout_backup = -1;
	if (input_fd != STDIN_FILENO)
	{
		stdin_backup = dup(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
	}
	if (output_fd != STDOUT_FILENO)
	{
		stdout_backup = dup(STDOUT_FILENO);
		dup2(output_fd, STDOUT_FILENO);
	}
	return ((stdin_backup << 16) | (stdout_backup & 0xFFFF));
}

void	exec_execute_command(char *command, t_console *terminal)
{
	if (ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		exec_built_cd(terminal);
	else if (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		exec_built_export(terminal);
	else if (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		exec_built_unset(terminal);
	else if (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		exec_built_pwd();
	else if (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		exec_built_echo(terminal);
	else if (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		exec_built_env(terminal);
}

int	count_commands_in_pipeline(t_command_nodes *commands)
{
	t_command_nodes	*current;
	int				count;

	count = 0;
	current = commands;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	is_builtin_command(char *command)
{
	if (!command)
		return (0);
	if ((ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		|| (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		|| (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		|| (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		|| (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		|| (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		|| (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		|| (ft_strncmp(command, "true", 4) == 0 && ft_strlen(command) == 4))
		return (1);
	return (0);
}
