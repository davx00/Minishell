/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_integration_utils_3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:14:57 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 21:31:05 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	init_heredoc_fds(t_command_nodes *head,
	t_pipeline_vars *vars, pid_t *pids)
{
	t_command_nodes	*current;

	current = head;
	vars->i = 0;
	while (current && vars->i < vars->cmd_count)
	{
		if (current->command->redirect_heredoc
			&& current->command->heredoc_delimiter)
		{
			vars->heredoc_fds[vars->i] = setup_heredoc(current->command);
			if (vars->heredoc_fds[vars->i] < 0)
			{
				free(pids);
				pids = NULL;
				free(vars->heredoc_fds);
				vars->heredoc_fds = NULL;
				exit(1);
			}
		}
		else
			vars->heredoc_fds[vars->i] = -1;
		current = current->next;
		vars->i++;
	}
}

void	wait_and_set_exit_status(pid_t *pids, t_pipeline_vars *vars)
{
	int	exit_status;

	vars->i = 0;
	while (vars->i < vars->cmd_count)
	{
		if (waitpid(pids[vars->i], &vars->temp_status, 0) == -1)
		{
			perror("waitpid failed");
			vars->i++;
			continue ;
		}
		if (WIFEXITED(vars->temp_status))
			exit_status = WEXITSTATUS(vars->temp_status);
		else if (WIFSIGNALED(vars->temp_status))
			exit_status = WTERMSIG(vars->temp_status) + 128;
		else
			exit_status = 1;
		if (vars->i == vars->cmd_count - 1)
			g_exit_code = exit_status;
		vars->i++;
	}
}

void	fork_and_exec_child(t_command_nodes *current,
	t_console *terminal, t_pipeline_vars *vars)
{
	vars->is_last = (vars->i == vars->cmd_count - 1);
	if (vars->is_last)
		vars->output_fd = STDOUT_FILENO;
	else
		vars->output_fd = vars->pipe_fd[WRITE_END];
	if (!vars->is_last)
		close(vars->pipe_fd[READ_END]);
	exec_child(current, terminal, *vars);
}

void	close_fds_after_child(t_pipeline_vars *vars, int *pipe_fd)
{
	if (vars->heredoc_fds[vars->i] != -1)
		close(vars->heredoc_fds[vars->i]);
	if (vars->prev_fd != STDIN_FILENO)
		close(vars->prev_fd);
	if (vars->i < vars->cmd_count - 1)
	{
		close(pipe_fd[WRITE_END]);
		vars->prev_fd = pipe_fd[READ_END];
	}
}
