/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_decor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:05:04 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 18:34:59 by despanol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

static char	*get_user(t_console *terminal)
{
	char	*user;

	execute_command(terminal, "/usr/bin/whoami", "whoami");
	if (!terminal->command_result || !*terminal->command_result)
	{
		user = (char *)malloc(sizeof(char) * 2);
		if (!user)
			return (NULL);
		user = ft_strdup("unkown@mini");
	}
	else
	{
		user = ft_strjoin(terminal->command_result[0], "@mini");
		ft_free_matrix(&terminal->command_result);
	}
	return (user);
}

void	set_command_line_decor(t_console *terminal)
{
	char	*user;
	char	**cwd;
	char	*final_formatted;

	user = get_user(terminal);
	cwd = (char **)malloc(sizeof(char *) * 3);
	cwd[0] = mini_getenv("PWD", terminal, 0);
	cwd[1] = ft_strjoin(cwd[0], " > ");
	final_formatted = ft_strjoin(user, cwd[1]);
	free(user);
	user = NULL;
	if (terminal->command_line_decor)
	{
		free(terminal->command_line_decor);
		terminal->command_line_decor = NULL;
	}
	terminal->command_line_decor = final_formatted;
	free(cwd[0]);
	cwd[0] = NULL;
	free(cwd[1]);
	cwd[1] = NULL;
	free(cwd);
	cwd = NULL;
}
