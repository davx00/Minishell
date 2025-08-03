/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:43:23 by akamal-b          #+#    #+#             */
/*   Updated: 2025/08/02 21:13:43 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	free_command_nodes(t_command_nodes *cmds)
{
	t_command_nodes	*current;
	t_command_nodes	*next;

	current = cmds;
	while (current)
	{
		next = current->next;
		free_command(current->command);
		free(current);
		current = NULL;
		current = next;
	}
}

void	free_all_console(t_console *terminal)
{
	if (!terminal)
		return ;
	if (terminal->command_nodes)
	{
		free_command_nodes(terminal->command_nodes);
		terminal->command_nodes = NULL;
	}
	free_console_strings(terminal);
	free_console_matrices(terminal);
	free(terminal);
	terminal = NULL;
}

void	free_all_console_child(t_console *terminal)
{
	if (!terminal)
		return ;
	if (terminal->command_nodes)
	{
		free_command_nodes(terminal->command_nodes);
		terminal->command_nodes = NULL;
	}
	if (terminal->command_line_decor)
	{
		free(terminal->command_line_decor);
		terminal->command_line_decor = NULL;
	}
	free_console_matrices(terminal);
	free(terminal);
}

void	free_all_console_2(t_console *terminal)
{
	if (!terminal)
		return ;
	if (terminal->command_nodes)
	{
		free_command_nodes(terminal->command_nodes);
		terminal->command_nodes = NULL;
	}
	free_console_strings_2(terminal);
	free_console_matrices(terminal);
	free(terminal);
	terminal = NULL;
}
