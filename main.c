/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:09:06 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 05:34:15 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heads/mini.h"

int	g_exit_code;

static t_signal_data	**get_signal_data_ptr(void)
{
	static t_signal_data	*signal_data_ptr = NULL;

	return (&signal_data_ptr);
}

static void	set_signal_data_ptr(t_signal_data *ptr)
{
	*get_signal_data_ptr() = ptr;
}

t_signal_data	*get_signal_data(void)
{
	return (*get_signal_data_ptr());
}

int	main(int argc, char **argv, char **envp)
{
	t_console		*terminal;
	t_signal_data	signal_data;

	set_signal_data_ptr(&signal_data);
	terminal = (t_console *)malloc(sizeof(t_console));
	signal_data = (t_signal_data){0};
	if (argc != 1)
		error_usage(terminal, argv);
	start_terminal_set_pid(argv, envp, terminal);
	while (argc && argv)
	{
		init_signals(terminal, &signal_data);
		if (terminal->out && *terminal->out)
			add_history(terminal->out);
		if (ft_count_words_and_quotes_main(terminal->out, " \t") == -1)
		{
			ft_count_words_aux();
			continue ;
		}
		while_continue(terminal, signal_data);
	}
	set_signal_data_ptr(NULL);
	exit(g_exit_code);
}
