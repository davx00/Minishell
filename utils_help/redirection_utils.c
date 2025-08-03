/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamal-b <akamal-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 21:43:12 by despanol          #+#    #+#             */
/*   Updated: 2025/08/02 22:56:00 by akamal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heads/mini.h"

extern int	g_exit_code;

void	add_output_file(t_command *cmd, char *filename, int is_append)
{
	t_list	*new_node;
	char	*file_copy;

	if (!cmd || !filename || !*filename)
	{
		return ;
	}
	file_copy = ft_strdup(filename);
	if (!file_copy)
	{
		return ;
	}
	new_node = ft_lstnew(file_copy);
	if (!new_node)
	{
		free(file_copy);
		return ;
	}
	if (is_append)
		ft_lstadd_back(&cmd->append_files, new_node);
	else
		ft_lstadd_back(&cmd->output_files, new_node);
}

static int	create_file(char *filename, int flags)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		g_exit_code = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

static void	create_files_from_list(t_list *files, int flags)
{
	while (files)
	{
		if (files->content)
		{
			if (create_file((char *)files->content, flags) == -1)
				return ;
		}
		files = files->next;
	}
}

void	create_all_output_files(t_command *cmd, t_console *terminal)
{
	(void) terminal;
	if (!cmd)
		return ;
	create_files_from_list(cmd->output_files, O_WRONLY | O_CREAT | O_TRUNC);
	create_files_from_list(cmd->append_files, O_WRONLY | O_CREAT | O_APPEND);
}
