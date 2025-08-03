/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_with_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:40 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 11:00:45 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static void	cleanup_previous_commands(t_console *terminal)
{
	if (terminal->command_nodes)
	{
		free_command_nodes(terminal->command_nodes);
		terminal->command_nodes = NULL;
	}
}

static char	*expand_and_validate_command(t_console *terminal)
{
	char	*expanded_command;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	expanded_command = expand_string(terminal->out, -1, quotes, terminal);
	if (validate_syntax(expanded_command))
	{
		if (expanded_command)
			free(expanded_command);
		return (NULL);
	}
	return (expanded_command);
}

static void	cleanup_expanded_command(char **expanded_command,
	t_console *terminal)
{
	if (*expanded_command && **expanded_command != '\0')
	{
		free(*expanded_command);
		*expanded_command = NULL;
		terminal->out = NULL;
	}
}

int	work_with_args(t_console *terminal)
{
	char	**command_matrix;
	char	*expanded_command;

	cleanup_previous_commands(terminal);
	expanded_command = expand_and_validate_command(terminal);
	if (!expanded_command)
		return (0);
	command_matrix = split_by_pipes_preserve_quotes(
			(const char *)expanded_command);
	cleanup_expanded_command(&expanded_command, terminal);
	process_command_matrix(command_matrix, terminal);
	if (command_matrix)
	{
		ft_free_matrix(&command_matrix);
		command_matrix = NULL;
	}
	basic_builtin_exec(terminal);
	return (1);
}
