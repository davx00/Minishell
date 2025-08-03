/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:06:59 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 03:08:54 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	error_usage(t_console *terminal, char **argv)
{
	printf("Usage: %s\n", argv[0]);
	printf("This shell does not accept arguments\n");
	free_all_console(terminal);
	exit(1);
}

void	init_signals(t_console *terminal, t_signal_data *signal_data)
{
	signal(SIGINT, function_handler);
	signal(SIGQUIT, SIG_IGN);
	set_command_line_decor(terminal);
	signal_data->is_waiting_for_input = 1;
	terminal->out = readline(terminal->command_line_decor);
}

void	ft_count_words_aux(void)
{
	write(2, "Error: unmatched quote\n", 23);
	g_exit_code = 1;
}

void	free_clean(t_console *terminal)
{
	free_all_console(terminal);
	exit(g_exit_code);
}

void	start_terminal_set_pid(char **argv, char **envp, t_console *terminal)
{
	g_exit_code = 0;
	start_terminal(argv, envp, terminal);
	set_father_pid(terminal);
}
