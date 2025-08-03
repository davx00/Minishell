/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_help_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:23:01 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:11 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

char	*handle_readline_input(int *sigint_received)
{
	char	*line;
	int		saved_exit;

	saved_exit = g_exit_code;
	g_exit_code = 0;
	line = readline("> ");
	if (g_exit_code == 130)
	{
		*sigint_received = 1;
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	g_exit_code = saved_exit;
	return (line);
}

int	should_exit_heredoc(char *line, char *delimiter, size_t delimiter_len)
{
	if (line == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (check_heredoc_line(line, delimiter, delimiter_len))
		return (1);
	return (0);
}

void	write_line_to_pipe(int pipe_fd[2], char *line)
{
	write(pipe_fd[WRITE_END], line, ft_strlen(line));
	write(pipe_fd[WRITE_END], "\n", 1);
	free(line);
	line = NULL;
}
