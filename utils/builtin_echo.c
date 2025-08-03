/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:04:40 by despanol          #+#    #+#             */
/*   Updated: 2025/07/24 00:16:48 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

static int	count_char(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static void	print_echo_arg(int *flag, char *arg, int has_next)
{
	*flag = 1;
	ft_putstr_fd(arg, 1);
	if (has_next)
		ft_putchar_fd(' ', 1);
}

int	exec_built_echo(t_console *terminal)
{
	int		newline;
	int		i[2];
	char	**argv;

	if (!terminal || !terminal->command_nodes
		|| !terminal->command_nodes->command
		|| !terminal->command_nodes->command->splitted_command)
		return (1);
	i[0] = 0;
	i[1] = 0;
	newline = 1;
	argv = terminal->command_nodes->command->splitted_command;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && argv[i[0]][0] == '-' && argv[i[0]][1] == 'n' &&
			count_char(argv[i[0]] + 1, 'n') == (int)ft_strlen(argv[i[0]] + 1))
			newline = 0;
		else
			print_echo_arg(&i[1], argv[i[0]], argv[i[0] + 1] != NULL);
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	g_exit_code = 0;
	return (0);
}
