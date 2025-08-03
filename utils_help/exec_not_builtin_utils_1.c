/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_not_builtin_utils_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:30:00 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/01 01:23:34 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	dir_error(const char *command)
{
	fprintf(stderr, "minishell: %s: Is a directory\n", command);
	g_exit_code = 126;
}

void	perm_error(const char *command)
{
	fprintf(stderr, "minishell: %s: Permission denied\n", command);
	g_exit_code = 126;
}

void	cmd_not_found(const char *command)
{
	fprintf(stderr, "minishell: %s: command not found\n", command);
	g_exit_code = 127;
}

void	execve_error(char *command, char *executable_path, t_console *terminal)
{
	fprintf(stderr, "minishell: %s: execution failed\n", command);
	free(executable_path);
	executable_path = NULL;
	g_exit_code = 127;
	free_all_console(terminal);
	exit(127);
}

void	execve_child(char *executable_path, t_command_nodes *node,
						t_console *terminal)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(executable_path, node->command->splitted_command,
			terminal->envp) == -1)
	{
		fprintf(stderr, "minishell: %s: execution failed\n",
			node->command->splitted_command[0]);
		exit(127);
	}
}
