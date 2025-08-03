/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:04:47 by despanol          #+#    #+#             */
/*   Updated: 2025/07/24 00:55:47 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static void	arg_count_when_is_one(t_console *terminal)
{
	printf("exit\n");
	free_all_console(terminal);
	exit(g_exit_code);
}

static void	print_exit_error(t_console *terminal, char **args)
{
	write(2, "minishell: exit: ", 17);
	write(2, args[1], strlen(args[1]));
	write(2, ": numeric argument required\n", 28);
	printf("exit\n");
	free_all_console(terminal);
	exit(2);
}

static int	print_exit_error_multiple_args(void)
{
	write(2, "minishell: exit: too many arguments\n", 37);
	g_exit_code = 1;
	return (1);
}

int	exec_built_exit(t_console *terminal)
{
	char	**args;
	int		arg_count;
	int		exit_status;
	char	*endptr;

	rl_clear_history();
	args = terminal->command_nodes->command->splitted_command;
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count == 1)
		arg_count_when_is_one(terminal);
	if (arg_count == 2)
	{
		exit_status = (int)strtol(args[1], &endptr, 10);
		if (*endptr != '\0' || endptr == args[1])
			print_exit_error(terminal, args);
		printf("exit\n");
		free_all_console(terminal);
		exit(exit_status % 256);
	}
	if (arg_count > 2)
		print_exit_error_multiple_args();
	return (1);
}
