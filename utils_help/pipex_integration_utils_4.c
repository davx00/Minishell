/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_integration_utils_4.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:27:57 by akamal-b          #+#    #+#             */
/*   Updated: 2025/07/27 00:46:44 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

int	allocate_pipeline_resources(int cmd_count, pid_t **pids, int **heredoc_fds)
{
	*pids = malloc(sizeof(pid_t) * cmd_count);
	*heredoc_fds = malloc(sizeof(int) * cmd_count);
	if (!(*pids) || !(*heredoc_fds))
	{
		if (*pids)
		{
			free(*pids);
			*pids = NULL;
		}
		if (*heredoc_fds)
		{
			free(*heredoc_fds);
			*heredoc_fds = NULL;
		}
		return (0);
	}
	return (1);
}

void	pipeline_cleanup(pid_t *pids, int *heredoc_fds)
{
	free(pids);
	pids = NULL;
	free(heredoc_fds);
	heredoc_fds = NULL;
}

void	setup_pipeline_vars(t_pipeline_vars *vars,
	t_command_nodes *command_nodes, pid_t *pids)
{
	init_heredoc_fds(command_nodes, vars, pids);
	vars->prev_fd = STDIN_FILENO;
	vars->i = 0;
}

void	execute_pipeline_loop(t_console *terminal,
	t_pipeline_vars *vars)
{
	t_command_nodes	*current;

	current = terminal->command_nodes;
	while (current && vars->i < vars->cmd_count)
	{
		if (vars->i < vars->cmd_count - 1)
		{
			if (pipe(vars->pipe_fd) < 0)
			{
				pipeline_cleanup(vars->pids, vars->heredoc_fds);
				mini_error("pipe failed", terminal);
			}
		}
		vars->pids[vars->i] = fork();
		if (vars->pids[vars->i] < 0)
		{
			pipeline_cleanup(vars->pids, vars->heredoc_fds);
			mini_error("fork failed", terminal);
		}
		if (vars->pids[vars->i] == 0)
			fork_and_exec_child(current, terminal, vars);
		close_fds_after_child(vars, vars->pipe_fd);
		current = current->next;
		vars->i++;
	}
}
