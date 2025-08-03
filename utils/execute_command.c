/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:12 by despanol          #+#    #+#             */
/*   Updated: 2025/07/27 00:49:07 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static int	handle_fork(int *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
	return (pid);
}

static void	cleanup_command_output(t_console *terminal, int fd)
{
	char	**aux;
	char	*info[2];

	aux = NULL;
	info[0] = get_next_line(fd);
	while (info[0] && info[0][0])
	{
		info[1] = ft_strtrim(info[0], "\n");
		free(info[0]);
		info[0] = NULL;
		aux = ft_extend_array(aux, info[1]);
		free(info[1]);
		info[1] = NULL;
		info[0] = get_next_line(fd);
	}
	if (info[0])
	{
		free(info[0]);
		info[0] = NULL;
	}
	ft_free_matrix(&(terminal->command_result));
	terminal->command_result = aux;
}

void	execute_command(t_console *terminal, char *executable_path,
						char *executable_args)
{
	char	**matrix;
	int		pid;
	int		fd[2];

	if (!terminal || !executable_path || pipe(fd) == -1)
		return ;
	pid = handle_fork(fd);
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fd[READ_END]);
		matrix = ft_split(executable_args, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (access(executable_path, F_OK) == 0
			&& access(executable_path, X_OK) == 0)
			execve(executable_path, matrix, terminal->envp);
		ft_free_matrix(&matrix);
		exit(127);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	cleanup_command_output(terminal, fd[READ_END]);
	close(fd[READ_END]);
}
