/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_signal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:39:53 by despanol          #+#    #+#             */
/*   Updated: 2025/08/03 10:44:49 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	start_terminal(char **argv, char **envp, t_console *terminal)
{
	terminal->pid = 0;
	terminal->out = NULL;
	terminal->argv = NULL;
	terminal->command_nodes = NULL;
	terminal->command_line_decor = NULL;
	terminal->command_result = NULL;
	terminal->envp = matrix_dup(envp);
	init_terminal_env_vars(terminal, argv);
}

void	init_terminal_env_vars(t_console *terminal, char **argv)
{
	char	*aux;

	(void)argv;
	set_cwd(terminal, &aux);
	set_shlvl(terminal, &aux);
	set_path(terminal, &aux);
	set_underscore(terminal, &aux, argv[0]);
}

void	simulate_enter(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	function_handler(int signal)
{
	t_signal_data	*signal_data;

	signal_data = get_signal_data();
	if (signal == SIGINT)
	{
		if (signal_data && signal_data->is_blocking_command)
		{
			printf("\n");
			signal_data->is_blocking_command = 0;
		}
		else if (signal_data && signal_data->is_waiting_for_input)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			printf("\n");
		}
		g_exit_code = 130;
	}
}

int	is_blocking_command(char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, "cat") == 0
		|| ft_strcmp(command, "grep") == 0
		|| ft_strcmp(command, "less") == 0
		|| ft_strcmp(command, "more") == 0
		|| ft_strcmp(command, "head") == 0
		|| ft_strcmp(command, "tail") == 0
		|| ft_strcmp(command, "wc") == 0
		|| ft_strcmp(command, "sed") == 0
		|| ft_strcmp(command, "awk") == 0
		|| ft_strcmp(command, "tee") == 0
		|| ft_strcmp(command, "sort") == 0
		|| ft_strcmp(command, "uniq") == 0
		|| ft_strcmp(command, "tr") == 0
		|| ft_strcmp(command, "read") == 0
		|| ft_strcmp(command, "vi") == 0
		|| ft_strcmp(command, "vim") == 0
		|| ft_strcmp(command, "nano") == 0
		|| ft_strcmp(command, "emacs") == 0
		|| ft_strcmp(command, "ssh") == 0
		|| ft_strcmp(command, "find") == 0)
		return (1);
	return (0);
}
