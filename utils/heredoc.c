/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:17 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:12 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static int	write_heredoc_lines(int pipe_fd[2], char *delimiter,
									size_t delimiter_len, char *prompt)
{
	int	ret;

	g_exit_code = 0;
	ret = loop_heredoc_lines(pipe_fd, delimiter, delimiter_len, prompt);
	close(pipe_fd[WRITE_END]);
	if (ret == -1)
		return (-1);
	return (pipe_fd[READ_END]);
}

static int	create_heredoc_pipe(char *delimiter)
{
	int		pipe_fd[2];
	int		result_fd;
	size_t	delimiter_len;
	char	*prompt;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	prompt = "";
	delimiter_len = ft_strlen(delimiter);
	result_fd = write_heredoc_lines(pipe_fd, delimiter, delimiter_len, prompt);
	if (!delimiter || *delimiter == '\0')
	{
		write(STDERR_FILENO, "Error: heredoc delimiter is empty\n", 34);
		return (-1);
	}
	return (result_fd);
}

int	setup_heredoc(t_command *cmd)
{
	if (!cmd->redirect_heredoc || !cmd->heredoc_delimiter)
		return (-1);
	return (create_heredoc_pipe(cmd->heredoc_delimiter));
}

int	setup_heredoc_single(t_command *cmd)
{
	if (!cmd->redirect_heredoc || !cmd->heredoc_delimiter)
		return (-1);
	return (create_heredoc_pipe(cmd->heredoc_delimiter));
}
