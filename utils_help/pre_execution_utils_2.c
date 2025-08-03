/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:16:00 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:11 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static void	setup_stdin_redirection(int fd, int *stdin_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	setup_input_redirection(t_command_nodes *current_node,
	int *stdin_backup)
{
	int	fd;

	fd = -1;
	if (current_node->command->redirect_heredoc
		&& current_node->command->heredoc_delimiter)
	{
		fd = setup_heredoc(current_node->command);
		if (fd < 0 || g_exit_code == 130)
			return ;
		setup_stdin_redirection(fd, stdin_backup);
	}
	else if (current_node->command->redirect_input
		&& current_node->command->input_file)
	{
		fd = open(current_node->command->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror(current_node->command->input_file);
			g_exit_code = 1;
			return ;
		}
		setup_stdin_redirection(fd, stdin_backup);
	}
}

void	setup_output_redirection(t_command_nodes *current_node,
	int *stdout_backup)
{
	int	flags;
	int	redirect_out_fd;

	if ((current_node->command->redirect_output
			|| current_node->command->redirect_append)
		&& current_node->command->output_file)
	{
		if (current_node->command->redirect_append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		redirect_out_fd = open(current_node->command->output_file, flags, 0644);
		if (redirect_out_fd < 0)
		{
			perror("error: redirect");
			g_exit_code = 1;
			return ;
		}
		*stdout_backup = dup(STDOUT_FILENO);
		dup2(redirect_out_fd, STDOUT_FILENO);
		close(redirect_out_fd);
	}
}

void	execute_command_dispatch(char *command, t_console *terminal,
	t_command_nodes *current_node)
{
	if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		exec_built_exit(terminal);
	else if (ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		exec_built_cd(terminal);
	else if (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		exec_built_export(terminal);
	else if (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		exec_built_unset(terminal);
	else if (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		exec_built_pwd();
	else if (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		exec_built_echo(terminal);
	else if (ft_strncmp(command, "true", 4) == 0 && ft_strlen(command) == 4)
		exec_built_true();
	else if (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		exec_built_env(terminal);
	else
		exec_not_builtin_standalone(current_node, terminal);
}

void	restore_redirections(int stdin_backup, int stdout_backup)
{
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
