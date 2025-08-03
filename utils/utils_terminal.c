/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:35 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 19:46:27 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

void	set_father_pid(t_console *terminal)
{
	terminal->pid = fork();
	if (terminal->pid < 0)
		print_error_exit(3, NULL, 1);
	if (terminal->pid == 0)
	{
		ft_free_matrix(&terminal->envp);
		free(terminal);
		terminal = NULL;
		exit(1);
	}
	waitpid(terminal->pid, NULL, 0);
	terminal->pid = terminal->pid - 1;
}
