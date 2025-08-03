/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_main_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:34:03 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:06:44 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	while_aux(t_console *terminal)
{
	if (terminal->out && *terminal->out)
	{
		work_with_args(terminal);
		if (terminal->command_nodes)
		{
			free_command_nodes(terminal->command_nodes);
			terminal->command_nodes = NULL;
		}
	}
}

void	while_continue(t_console *terminal, t_signal_data signal_data)
{
	signal_data.is_waiting_for_input = 0;
	(void)signal_data;
	if (!terminal->out)
		free_clean(terminal);
	while_aux(terminal);
	free(terminal->command_line_decor);
	terminal->command_line_decor = NULL;
}
