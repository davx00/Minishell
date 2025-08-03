/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:09:54 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/03 02:36:12 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

int	check_heredoc_line(char *line, char *delimiter, size_t delimiter_len)
{
	char	*trimmed_line;
	int		result;

	if (!line)
		return (0);
	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
	{
		free(line);
		return (0);
	}
	result = (ft_strlen(trimmed_line) == delimiter_len
			&& ft_strncmp(trimmed_line, delimiter, delimiter_len) == 0);
	free(trimmed_line);
	if (result)
	{
		free(line);
		line = NULL;
		return (1);
	}
	return (0);
}

static void	get_out_heredoc(int signal)
{
	char	c;

	c = '\n';
	(void) signal;
	g_exit_code = 130;
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(STDOUT_FILENO, "\n", 1);
}

static int	handle_heredoc_cleanup(int pipe_fd[2],
	void (*old_handler)(int), int sigint_received)
{
	close(pipe_fd[WRITE_END]);
	signal(SIGINT, old_handler);
	if (sigint_received)
	{
		close(pipe_fd[READ_END]);
		g_exit_code = 130;
		return (-1);
	}
	return (pipe_fd[READ_END]);
}

int	loop_heredoc_lines(int pipe_fd[2], char *delimiter,
	size_t delimiter_len, char *prompt)
{
	char	*line;
	void	(*old_handler)(int);
	int		sigint_received;

	(void)prompt;
	sigint_received = 0;
	rl_done = 0;
	old_handler = signal(SIGINT, get_out_heredoc);
	while (1)
	{
		line = handle_readline_input(&sigint_received);
		if (sigint_received)
			break ;
		if (should_exit_heredoc(line, delimiter, delimiter_len))
			break ;
		write_line_to_pipe(pipe_fd, line);
	}
	return (handle_heredoc_cleanup(pipe_fd, old_handler, sigint_received));
}
